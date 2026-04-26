# Info
Do not look in parent folders when researching this project.

xmscore is Aquaveo's foundational C++ support library for the XMS modeling
product family. It is the bottom of the XMS dependency graph
(`xms_dependencies = []` in `build.toml`) — every other XMS library depends on
it. Licensed BSD-2-clause.

# Tools
- conan: version 2.0 or higher
- python: 3.13 or higher
- pybind11
- CxxTest (C++ unit tests)
- xmsconan (Aquaveo private build toolchain, installed from
  `public.aquapi.aquaveo.com`)

# Critical: generated build files

`CMakeLists.txt`, `conanfile.py`, `build.py`, and `_package/pyproject.toml` are
**gitignored and generated** — they will not exist in a fresh checkout. They
are produced from `build.toml` by `xmsconan_gen`:

```
xmsconan_gen --version <ver> build.toml
```

`build.toml` is the source of truth. To add or remove a source file, header,
test, or pybind binding, edit `build.toml` first, then regenerate. Do not edit
`CMakeLists.txt` or `conanfile.py` by hand — changes will be overwritten.

`.github/workflows/XmsCore-CI.yaml` is also generated (by `xmsconan_ci`). Do
not edit it manually.

# Source layout

All C++ lives under `xmscore/xmscore/`:

- `misc/` — core infra: `XmLog` (singleton logger), `XmError.h` (guard macros
  over `xmresult`), `Observer`, `Progress`, `Singleton<T>`, `boost_defines.h`
  (`BSHP`/`BSCP`/`BWP` aliases), `StringUtil`, `DynBitset`, `XmConst`
- `points/` — `Pt2<T>`/`Pt3<T>`/`Pt4<T>` templates + tolerance-aware
  comparison functors
- `math/` — header-only inline math (`Round`, `Mmax`, `EQ_TOL`/`LT_TOL`)
- `stl/` — `VecDbl`, `VecInt`, `VecPt3d` and 2D/3D variants used everywhere
- `dataio/` — `DaStreamReader`/`DaStreamWriter` for named-field text + binary
  (zlib) serialization
- `time/` — `tmCalendarToJulian` / `tmJulianToCalendar`
- `testing/` — CxxTest helper macros (`TS_ASSERT_DELTA_VEC`, etc.)
- `python/` — pybind11 bindings

Other top-level dirs: `_package/` (Python wheel sources + tests), `dev/`
(developer profiles — note: stale, target VS 16 / Conan 1 syntax), `Doxygen/`
(C++ docs), `pydocs/` (Sphinx Python docs).

# C++ conventions

- `#pragma once` everywhere — no `#ifndef` guards
- Numbered include-block comments: `// 3. Standard Library Headers`,
  `// 4. External Library Headers`, `// 5. Shared Headers`,
  `// 6. Non-shared Headers`
- Parameter prefix `a_` (e.g., `a_outStream`); member prefix `m_`
- Free-function module prefixes: `da` (dataio), `st` (string), `tm` (time)
- Pimpl is standard; older modules use `BSHP<impl>`, newer use
  `std::unique_ptr<Impl>`
- `XM_DISALLOW_COPY_AND_ASSIGN` macro instead of `= delete` on copy ops
- Smart pointers go through Boost aliases (`BSHP` = `boost::shared_ptr`,
  `BSCP` = `boost::scoped_ptr`, `BWP` = `boost::weak_ptr`,
  `BDPC`/`BSPC` = dynamic/static cast). There is an active migration toward
  modern `Ptr<T>` but `BSHP` is still the project standard.

# C++ style

`_clang-format` (note: no leading dot) — Google base with overrides:
- `ColumnLimit: 100`
- Allman braces for class/function/namespace (`AfterClass`, `AfterFunction`,
  `AfterNamespace: true`)
- `IndentWidth: 2`
- `PointerAlignment: Left`
- `SortIncludes: false`
- `BinPackParameters: false`

Run `clang-format` via the `aquaveo-cpp:format` skill.

# Tests

**C++ — CxxTest.** Test fixtures are `.t.h` headers co-located with the
source they test (e.g., `xmscore/misc/XmLog.t.h`). Implementation test code
lives in `.cpp` files behind `#if CXX_TEST` / `#ifdef CXX_TEST`. Custom
assertion macros are in `xmscore/testing/TestTools.h`.

**Python — `unittest.TestCase`.** Tests live in `_package/tests/unit_tests/`
named `*_pyt.py` (note: not `test_*.py`). They import the public API
(`xms.core.misc`, `xms.core.time`), not `_xmscore` directly. There is no
pytest config or `conftest.py`.

# Python bindings

- Compiled extension is `_xmscore`, registered under namespace package
  `xms.core` → full path `xms.core._xmscore`
- Submodules: `_xmscore.misc` (`Observer`, `ProgressListener`),
  `_xmscore.time` (Julian conversions)
- **Holder type is `boost::shared_ptr<T>`** — each binding `.cpp` independently
  declares `PYBIND11_DECLARE_HOLDER_TYPE(T, boost::shared_ptr<T>)`
- **Two-level trampoline pattern** for classes with virtual callbacks:
  real C++ class → `PublicXxx` (re-exposes protected virtuals as public) →
  `PyXxx` (pybind11 trampoline using `PYBIND11_OVERLOAD`).
  `py::class_<Public, Py, BSHP<Public>>`.
- **No `pybind11/stl.h`.** `xmscore/python/misc/PyUtils.cpp/.h` provides manual
  converters for `VecPt3d`, `VecPt2d`, `VecInt`, `VecDbl`, `VecFlt`,
  `DynBitset`, etc. Point arrays return as `py::array_t<double>` (NumPy).
- No `.pyi` stubs exist. Sphinx mocks `_xmscore` with `MagicMock` for autodoc.
- `__version__` is read from the `XMS_VERSION` preprocessor define injected at
  build time (defaults to `"99.99.99"`).

# Python style

flake8 args are inlined in CI (`XmsCore-CI.yaml`, the `flake` job) — there is
no `setup.cfg` or `.flake8` file:
- `--max-line-length=120`
- `--docstring-convention google`
- `--import-order-style=appnexus`
- `--application-import-names=xms.core --application-package-names=xms`
- ignored: `D200`, `D212`

# CI

GitHub Actions only. `flake` (lint), `mac` (macos-15), `linux` (container
`ghcr.io/aquaveo/conan-gcc13-py3.13`), `windows` (windows-2022). Each native
job builds Release and Debug. Triggers on every push and PR.

Pipeline: install xmsconan → `xmsconan_conan_setup` → `xmsconan_gen` →
`python build.py --wheel-dir wheelhouse --artifacts-dir test_artifacts`.
Test artifacts are uploaded on every run (success or failure). Wheel deploy
and Conan upload happen only on tagged releases.

# Versioning

No checked-in VERSION file. `XMS_VERSION` defaults to `0.0.0` and is
overridden to the git tag at release time. The version flows into both the
generated CMake/Conan recipe and the Python module's `__version__`.

# Other notes

- `.gitattributes` enforces LF line endings on all files
- `condabuildinfo.cmake` and `emscriptenbuildinfo.cmake` exist for Conda and
  WebAssembly build paths but are not exercised by the active CI
- `generateDocumentationAndDeploy.sh` is orphaned Travis-era infrastructure
- Boost is pervasive but actively shrinking (`boost::log` was recently
  replaced with `std::mutex` + `std::ofstream` + C stdio)
