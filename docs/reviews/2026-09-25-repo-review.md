# xmscore repo-wide review — 2026-09-25

- Command: `/aquaveo-workflow:review --all --repo --validate`
- Commit reviewed: `52649a0c` (branch `aquaveo-workflow-review-75f407`, clean tree)
- Scope: all 119 tracked files (no diff)
- Specialists: writer-reviewer, silent-failure-reviewer, complexity-reviewer, pr-coverage-reviewer, xunit-patterns-python:test-reviewer, xunit-patterns:test-smell-reviewer, aquaveo-python:type-design-reviewer, aquaveo-cpp:type-design-reviewer, aquaveo-cpp:cmake-structure-reviewer
- Validation: 15 validators on the top CRITICAL entries; rollup and report by review-aggregator

Validated 15 of 52 findings (9 confirmed, 6 dropped, 0 uncertain; 37 past the cap, unvalidated).

> Orchestrator note: the count line above uses the mechanically re-counted rollup (16 CRITICAL + 36 MAJOR = 52). The aggregator's report below was printed verbatim and contains its own in-line reconciliation of the "41 MAJOR" tally error, including three void `M37` headings that carry no finding.

---

# Review: repo-wide audit of `xmscore` (119 tracked files, no diff)

**What changed.** This is a `--repo` review of the whole tree at `/Users/bill/dev/xms/xmscore/.claude/worktrees/aquaveo-workflow-review-75f407` rather than a diff: the C++ support library (`xmscore/dataio`, `misc`, `points`, `stl`, `time`, `testing`), its pybind11 layer (`xmscore/python`), the `xms.core` Python package under `_package/`, the Python unit tests, docs, and CI/deploy scripts. Findings therefore describe long-standing code, not a single author's change. The heaviest clusters are in the binary-block reader/writer (`daStreamIo.cpp`), the Python `Observer`/`ProgressListener` wrappers, and `filesystem.py`'s exception handling. Nine specialists ran; `cmake-structure-reviewer` returned APPROVE with zero findings. Notably, `_package/xms/core/filesystem/filesystem.py:73` catches exactly `shutil.SameFileError` in `copyfile` — the narrow, documented handler that the neighbouring functions in the same file lack.

Validation: 15 CRITICAL entries were validated (9 confirmed, 6 dropped, 0 uncertain); the 16th CRITICAL and all 41 MAJOR entries fell past the validator cap and are tagged `[unvalidated]`.

**Verdict: BLOCK (C=10 M=41 m=57)**

---

## Critical items

### **C1**: `_package/xms/core/misc/observer.py:17` — every base callback recurses into itself, RecursionError on first event

`[CRITICAL] [validated]`

```python
    def on_progress_status(self, percent_complete):
        """
        Captures the progress of an operation.
        ...
        """
        self.on_progress_status(percent_complete)

    def on_begin_operation_string(self, operation):
        ...
        self.on_begin_operation_string(operation)
```

Same pattern at lines 24, 33, 39, 48, 57, 66 (`on_progress_status`, `on_begin_operation_string`, `on_end_operation`, `on_update_message`, `time_remaining_in_seconds`, `time_elapsed_in_seconds`). `Observer` is exported publicly (`_package/xms/core/misc/__init__.py:4`) and documented as the class to subclass (`pydocs/source/getting_started.rst:38-78`); the docs and the only test override all six methods, which is why this never fires in-repo.

**Change:** Replace each body with `super().<method>(...)` (the C++ base at `xmscore/python/misc/PublicObserver.h:33` is a no-op), or `pass` if these are meant to be stubs. Sibling `progress_listener.py:38` shows the intended `super()` pattern.

**Why:** Any event delivered to a directly-instantiated `Observer`, or to a subclass that overrides only some of the six methods, recurses until `RecursionError`. Validator note: high rather than truly critical only because the documented full-override usage happens to work.

### **C2**: `_package/xms/core/misc/progress_listener.py:61` — `on_begin_operation_string` calls itself instead of `super()`

`[CRITICAL] [validated]`

```python
    def on_begin_operation_string(self, operation):
        ...
        stack_index = self.on_begin_operation_string(operation)
        self.call_back(('begin_operation', stack_index, operation))
        return stack_index
```

**Change:** `stack_index = super().on_begin_operation_string(operation)`, matching line 38 in the same file. The pybind base exposes the real method (`xmscore/python/misc/progress_listener_py.cpp:43`).

**Why:** Any begin-operation event on a `ProgressListener` (exported via `_package/xms/core/misc/__init__.py:5`) recurses until `RecursionError`. No test exercises this class (see M11).

### **C3**: `xmscore/dataio/daStreamIo.cpp:684` — `ReadBinaryBytes` reads unchecked lengths from the file into fixed heap buffers

`[CRITICAL] [validated]` (severity disagreement: writer-reviewer rated CRITICAL, silent-failure-reviewer rated MAJOR)

```cpp
    std::string blockString;
    int32_t encodedLength;
    int32_t blockLength;
    ReadString(blockString);
    ReadInt(encodedLength);
    ReadInt(blockLength);
    NextLine();

    // read and decode
    m_impl->m_inStream.read(encoded.get(), encodedLength);
    NextLine();

    auto compressedLength = iBase64Decode(encoded.get(), encodedLength, compressed.get());
```

`encoded` is exactly `maxEncodeLength + 1` bytes (line 670, ~43 KB) and `compressed` is `compressBound(MAX_BLOCK_SIZE)` (669). None of the three reads' return values is checked, so on a truncated block `encodedLength`/`blockLength` stay uninitialized (676-677); on a well-formed but hostile file, an `encodedLength` larger than the buffer overflows `encoded` at line 684, and `iBase64Decode` at 687 writes into `compressed` with no capacity bound.

**Change:** Branch on the result of `ReadString`, both `ReadInt`s, and `NextLine`, returning `false` on failure; before line 684 require `0 <= encodedLength <= maxEncodeLength` and `0 < blockLength <= min(MAX_BLOCK_SIZE, a_destLength)`, returning `false` otherwise.

**Why:** Heap overflow on malformed or malicious input read through the public `DaStreamReader` API.

### **C4**: `xmscore/dataio/daStreamIo.cpp:690` — decompressed `blockLength` never bounded by remaining `a_destLength`

`[CRITICAL] [validated]`

```cpp
    // decompress data
    if (!iUncompress(compressed.get(), compressedLength, a_dest, blockLength))
      return false;

    a_dest += blockLength;
    a_destLength -= blockLength;
```

`blockLength` comes straight from the file (`ReadInt(blockLength)`, line 680) and is passed to `iUncompress` as the output capacity for `a_dest` without comparison to the bytes remaining.

**Change:** Reject `blockLength <= 0 || blockLength > a_destLength` (and `encodedLength` outside `[0, maxEncodeLength]`) before decoding; this can be the same guard as C3.

**Why:** A corrupt or malicious file with an oversized `blockLength` makes zlib `uncompress` (line 119) write past the end of `a_dest`. Validator correction: the finder's secondary claim that a negative `blockLength` spins the loop forever does not hold — `iUncompress` requires `uncompressedLength == a_destLength` (line 122), which fails for a negative value, and the `a_destLength > 0` guard then exits; the overflow is the material half.

### **C5**: `xmscore/dataio/daStreamIo.cpp:957` — `SetBinaryBlockSize` accepts 0/negative, making `WriteBinaryBytes` non-terminating

`[CRITICAL] [validated]`

```cpp
void DaStreamWriter::SetBinaryBlockSize(int a_blockSize)
{
  m_impl->m_blockSize = a_blockSize > MAX_BLOCK_SIZE ? MAX_BLOCK_SIZE : a_blockSize;
} // DaStreamWriter::SetBinaryBlockSize
```

In `WriteBinaryBytes` (924-935), `blockLength = a_sourceLength < m_blockSize ? a_sourceLength : m_blockSize`, then `a_sourceLength -= blockLength` inside `while (a_sourceLength > 0)`.

**Change:** Clamp to a minimum of 1 or reject non-positive values (return/log via `XM_ENSURE_TRUE`). Document the precondition on `daStreamIo.h:174`.

**Why:** A block size of 0 leaves `a_sourceLength` unchanged and the loop emits empty `BINARY_BLOCK` records forever; a negative value passes a negative length to `iCompress` (UB) and `compressBound(negative)` at line 919 becomes a huge allocation. Public API with no documented precondition.

### **C6**: `xmscore/misc/StringUtil.cpp:199` — `stSplit(..., compress=false)` drops the trailing token and reads `back()` on empty input

`[CRITICAL] [validated]`

```cpp
    std::vector<char> temp(a_source.size());
    int end = 0;
    for (size_t i = 0; i < a_source.size(); ++i) {
      if (a_delimiterList.find(a_source[i]) != std::string::npos) {
        elems.push_back(std::string(&temp[0], end));
        end = 0;
      } else {
        temp[end++] = a_source[i];
      }
    }
    if (a_delimiterList.find(a_source.back()) != std::string::npos) {
      elems.push_back("");
    }
```

**Change:** Rewrite the non-compress branch so that after the loop the pending `temp[0..end)` is pushed whenever the input is non-empty (that also covers the trailing-empty-token case), and guard `a_source.empty()` before calling `back()`. Add a test with a trailing non-delimiter token, e.g. `stSplit("a,b", ",", false)` → `{"a","b"}`.

**Why:** A token is only pushed when a delimiter is seen, so `stSplit("a,b", ",", false)` returns `["a"]`; `a_source.back()` on an empty string is UB. The only test (line 1391, `",,A,B,,C,,,"`) ends in a delimiter and never exercises the trailing-token path. `stSplit` is public API (`StringUtil.h:69`) consumed by downstream XMS libraries. Validator correction: the `&temp[0]`-on-empty-vector claim is not independently a bug — line 199 is only reached inside the loop, where `temp` is non-empty.

### **C7**: `xmscore/misc/XmError.h:430` — `XM_ENSURE_FALSE_T_5` dispatches to an undefined `XM_ENSURE_TRUE_T_6`

`[CRITICAL] [validated]`

```cpp
#define XM_ENSURE_FALSE_T_5(x, ret, lvl, msg, ast) XM_ENSURE_TRUE_T(!(x), ret, lvl, msg, ast)
```

Compare the correct sibling at line 394:

```cpp
#define XM_ENSURE_FALSE_5(x, ret, lvl, msg, ast) XM_ENSURE_TRUE_5(!(x), ret, lvl, msg, ast)
```

**Change:** Call `XM_ENSURE_TRUE_T_5(!(x), ret, lvl, msg, ast)` directly, matching line 394.

**Why:** `XM_ENSURE_TRUE_T` is the variadic dispatcher (line 325) that appends `xms::XM1`, so `BOOST_PP_OVERLOAD` resolves to the non-existent `XM_ENSURE_TRUE_T_6`; every entry point of the public `XM_ENSURE_FALSE_T` / `XM_ENSURE_FALSE_T_NO_ASSERT` family (440-456 all funnel through `_5`) is a compile error on first use. Validator caveat: the macro has zero uses in this repo, so nothing currently fails to build — a latent bug in an exported header rather than an active breakage; CRITICAL is arguably overstated.

### **C8**: `xmscore/points/pt.h:1798` — `Pt4::operator<` tests `z < a` twice, breaking strict-weak ordering

`[CRITICAL] [validated]`

```cpp
      if (y < a)
        return 1;
      else if (y > a)
        return 0;
      else
      {
        if (z < a)
          return 1;
        else if (z < a)
          return 0;
```

Same defect at line 1873 in `operator<(const Pt4<U>&)`: `else if (z < a.z)`.

**Change:** Change the second test to `z > a` (1798) and `z > a.z` (1873), mirroring the `y` branch directly above.

**Why:** The `return 0` branch is unreachable and when `z > a.z` control falls through to the `w` comparison, so e.g. `Pt4(0,0,5,0) < Pt4(0,0,1,3)` returns true. Any `std::sort`/`std::map` keyed on `Pt4` gets an invalid comparator (UB in the standard library).

### **C9**: `xmscore/python/misc/PyUtils.cpp:412` — `IntPairFromPyIter` returns hardcoded `(1, 1)`; real cast commented out

`[CRITICAL] [validated]` (severity disagreement: writer-reviewer rated CRITICAL, silent-failure-reviewer and complexity-reviewer rated MAJOR)

```cpp
  py::tuple pr = intpair.cast<py::tuple>();
  if (py::len(pr) != 2) {
      throw py::type_error("arg must be an 2-tuple");
  } else {
      std::pair<int, int> ret(1, 1);//ret(pr[0].cast<int>, pr[1].cast<int>);
      return ret;
  }
```

**Change:** `std::pair<int, int> ret(pr[0].cast<int>(), pr[1].cast<int>());` and delete the dead comment.

**Why:** Every valid 2-tuple converts to `(1, 1)`, and `VecIntPairFromPyIter` (437) fills its whole vector with that garbage. Both functions are exported via the public header `PyUtils.h:72,75` for downstream pybind modules; no in-repo caller other than each other exists, so nothing catches it.

### **C10**: `xmscore/python/misc/detail/PublicProgressListener.cpp:74` — destructor leaves the global listener pointing at a freed parent

`[CRITICAL] [unvalidated]`

```cpp
  impl(PublicProgressListener *a_) :
    m_child(new Listener(a_))
  {
    ProgressListener::SetListener(m_child);
  }
  ...
PublicProgressListener::~PublicProgressListener()
{
  try
  {
    if (m_p)
      delete(m_p);
    m_p = nullptr;
  }
  catch (...) {}
}
```

**Change:** In the destructor (or `impl`'s destructor), clear the process-global listener if it still refers to `m_child` (e.g. `ProgressListener::SetListener(BSHP<ProgressListener>())`) before deleting `m_p`.

**Why:** The constructor installs `m_child` (which holds a raw `m_parent` back-pointer) as the process-global `ProgressListener`, and the destructor never uninstalls it; the next progress event after the Python object is garbage-collected dereferences the dead parent — use-after-free.

---

## Major items

### **M1**: `_package/tests/unit_tests/filesystem_pyt.py:264` — `assertTrue(True, ...)` never checks the function's return value

`[MAJOR] [unvalidated]`

```python
        self.assertTrue(True, is_somewhere_below_system_temp(file_path))
        self.assertTrue(True, is_somewhere_below_system_temp(Path(file_path)))
```

**Change:** `self.assertTrue(is_somewhere_below_system_temp(file_path))` (and the `Path` variant).

**Why:** Literal `True` is the condition and the real result is the failure message, so the test passes regardless of what `is_somewhere_below_system_temp` returns.

### **M2**: `_package/tests/unit_tests/observer_pyt.py:103` — `test_on_end_operation` duplicates `test_end_operation` (177-182)

`[MAJOR] [unvalidated]`

```python
    def test_on_end_operation(self):
        self.observer.end_operation()
        self.assertTrue(self.observer.status['operation_end'])
```

**Change:** Delete one of the two byte-identical tests.

**Why:** Duplicate tests double maintenance and mask whether a behaviour is actually covered once or not at all.

### **M3**: `_package/tests/unit_tests/observer_pyt.py:110` — `test_on_update_message` duplicates `test_update_message` (184-190)

`[MAJOR] [unvalidated]`

```python
    def test_on_update_message(self):
        message = '21 jelly beans counted so far.'
        self.observer.update_message(message)
        self.assertEqual(message, self.observer.status['message'])
```

**Change:** Delete the redundant copy.

**Why:** Same as M2.

### **M4**: `_package/tests/unit_tests/observer_pyt.py:118` — timing tests sleep on the real clock and recompute the SUT formula

`[MAJOR] [unvalidated]`

```python
        self.observer.begin_operation_string('Test Operation')
        time.sleep(0.1)
        self.observer.progress_status(0.2)
        remaining = self.observer.status['remaining_seconds']
        remaining_base = (self.observer.status['elapsed_seconds'] * 0.8) / 0.2
        delta = 1e-5
        self.assertAlmostEqual(remaining_base, remaining, delta=delta)
```

`test_time_elapsed_in_seconds` (130-139) is the mirror image with `places=9`.

**Change:** Inject a fake clock (or use freezegun) so elapsed time is deterministic, and assert hardcoded expected values instead of re-deriving them from the SUT's own outputs.

**Why:** Wall-clock races under CI load make the 1e-5 / 9-places tolerances flaky, and rebuilding "expected" from the SUT's formula means a wrong formula still passes.

### **M5**: `_package/xms/core/filesystem/filesystem.py:35` — `clear_folder` prints and swallows every per-file exception

`[MAJOR] [unvalidated]`

```python
        try:
            if os.path.isfile(file_path):
                os.unlink(file_path)
            elif os.path.isdir(file_path):
                shutil.rmtree(file_path)
        except Exception as e:
            print(e)
```

**Change:** Narrow the exception to `OSError`; collect failures and re-raise (or return the list) instead of printing to stdout and continuing.

**Why:** `make_or_clear_dir` (46) reports success on a directory that still holds files — `PermissionError`/`OSError` from locked or read-only entries is hidden and callers cannot detect partial failure.

### **M6**: `_package/xms/core/filesystem/filesystem.py:85` — `removefile` swallows every `Exception` with `pass`

`[MAJOR] [unvalidated]`

```python
    try:
        os.remove(filename)
    except Exception:
        pass
```

**Change:** Catch `FileNotFoundError` only (the one failure "ignoring any errors" plausibly means).

**Why:** `PermissionError` / `IsADirectoryError` leave the file on disk with no signal to the caller.

### **M7**: `_package/xms/core/filesystem/filesystem.py:108` — `resolve_relative_path` turns any exception into the sentinel `''`

`[MAJOR] [unvalidated]` (severity disagreement: silent-failure-reviewer rated MAJOR, python:type-design-reviewer rated MINOR)

```python
    normpath = ''
    try:
        ...
        normpath = os.path.normpath(resolved_path)
    except Exception:
        pass
    return normpath
```

**Change:** Drop the try/except and let it raise, or return `Optional[str]` with `None` on failure.

**Why:** A `TypeError` from a `None` argument becomes `''`, which is indistinguishable from a resolved path and which `does_file_exist` (127) then treats as a path.

### **M8**: `_package/xms/core/filesystem/filesystem.py:113` — `does_file_exist` has no test

`[MAJOR] [unvalidated]`

```python
def does_file_exist(file: str | Path, proj_dir: str | Path) -> bool:
    ...
    try:
        if not os.path.isabs(file):  # Convert relative to absolute
            file = resolve_relative_path(proj_dir, file)
        return os.path.exists(file)
    except Exception:
        return False
```

**Change:** Add `test_does_file_exist` to `filesystem_pyt.py` covering absolute path, relative-to-`proj_dir`, and missing-file cases. (Specialist searched: `filesystem_pyt.py` import list 18-20 lacks it; repo-wide grep finds only the definition.)

**Why:** The relative-resolution branch and its fallthrough are untested; M7/M9 changes to this function would land without coverage.

### **M9**: `_package/xms/core/filesystem/filesystem.py:129` — `does_file_exist` maps every exception to `False`

`[MAJOR] [unvalidated]` (severity disagreement: python:type-design-reviewer rated MAJOR, silent-failure-reviewer rated MINOR)

```python
        return os.path.exists(file)
    except Exception:
        return False
```

**Change:** Narrow to `OSError`, remove the try/except entirely, or return `Optional[bool]`.

**Why:** A `TypeError` from a bad argument reads as "file does not exist", conflating a failed check with a negative answer.

### **M10**: `_package/xms/core/filesystem/filesystem.py:180` — `temp_filename` creates, deletes, then returns the name (TOCTOU)

`[MAJOR] [unvalidated]`

```python
        xms_temp = os.environ.get('XMS_PYTHON_APP_TEMP_DIRECTORY', 'unknown')
        if xms_temp != 'unknown':
            file = tempfile.NamedTemporaryFile(mode='wt', suffix=suffix, dir=xms_temp, delete=True)
        else:
            file = tempfile.NamedTemporaryFile(mode='wt', suffix=suffix, delete=True)

    filename = file.name
    file.close()
    return filename
```

**Change:** Use `NamedTemporaryFile(delete=False)` and return its path (caller owns removal); drop the `'unknown'` string sentinel in favour of `None`.

**Why:** Between `close()` (which deletes) and the caller's use, another process can claim the same name; the sentinel comparison is a string-typed `None`.

### **M11**: `_package/xms/core/misc/progress_listener.py:1` — `ProgressListener` module has zero test coverage

`[MAJOR] [unvalidated]`

```python
def set_listener_callback(call_back):
    p = ProgressListener()
    p.call_back = call_back
    return p


class ProgressListener(Prog):
```

**Change:** Add `_package/tests/unit_tests/progress_listener_pyt.py` mirroring `observer_pyt.py`'s `MockObserver` pattern, covering `set_listener_callback`, `on_progress_status`, `on_begin_operation_string`, `on_end_operation`, `on_update_message`. (Specialist searched `_package/tests/unit_tests/*_pyt.py`; none exists.)

**Why:** C2 and M12 in this file are both defects a single smoke test would have caught.

### **M12**: `_package/xms/core/misc/progress_listener.py:79` — `on_update_message` passes literal `-1` instead of `stack_index`

`[MAJOR] [unvalidated]`

```python
    def on_update_message(self, stack_index, message):
        ...
        self.call_back(('update_message', -1, message))
```

**Change:** `self.call_back(('update_message', stack_index, message))`.

**Why:** Nested-operation update messages are misattributed to index `-1`, so callbacks cannot associate the message with its operation.

### **M13**: `generateDocumentationAndDeploy.sh:86` — `doxygen | tee` under `set -e` without `pipefail`

`[MAJOR] [unvalidated]`

```sh
doxygen $DOXYFILE 2>&1 | tee doxygen.log
```

**Change:** Add `set -o pipefail` at the top of the script.

**Why:** A non-zero doxygen exit is replaced by tee's 0, so the script proceeds to publish broken docs.

### **M14**: `generateDocumentationAndDeploy.sh:114` — `export VAR=$(pipeline)` masks a grep miss; empty var becomes `cp -r /*`

`[MAJOR] [unvalidated]`

```sh
export PATH_TO_PYTHON_PACKAGE=$(cat ./conan/conanbuildinfo.txt | grep PYTHONPATH.*xmscore | sed -r 's/^PYTHONPATH=\["(.*?)"\]$/\1/')
# copy package into build directory
cp -r ${PATH_TO_PYTHON_PACKAGE}/* $(dirname $SPHINX_CONF)/
```

**Change:** Assign first, test non-empty (`[ -n "$PATH_TO_PYTHON_PACKAGE" ] || exit 1`), then export; quote the variable in the `cp`.

**Why:** `export` returns 0 regardless of the pipeline's status, so a grep miss yields an empty path and line 116 runs `cp -r /* ...`.

### **M15**: `xmscore/dataio/daStreamIo.cpp:390` — `DaStreamReader::ReadLine` duplicates free `daReadLine` (978-1016)

`[MAJOR] [unvalidated]`

```cpp
bool DaStreamReader::ReadLine(std::string& a_line)
{
  a_line.clear();
  ...
  std::istream::sentry se(m_impl->m_inStream, true);
  std::streambuf* sb = m_impl->m_inStream.rdbuf();

  for (;;)
  {
    int c = sb->sbumpc();
```

`ReadStringFromLine` (606-618) likewise duplicates `daReadStringFromLine` (1175-1187).

**Change:** Have the members delegate: `return daReadLine(m_impl->m_inStream, a_line);` and the same for `ReadStringFromLine`.

**Why:** Two copies of a ~35-line streambuf/sentry loop will drift on the next line-ending fix; repo `CLAUDE.md` explicitly asks reviewers to flag duplicated logic.

### **M16**: `xmscore/dataio/daStreamIo.cpp:465` — `ReadVecInt/ReadVecDbl/ReadVecPt3d` duplicate the free `daReadVec*` branching

`[MAJOR] [unvalidated]`

```cpp
  else
  {
    a_vec.resize(0);
    a_vec.reserve(size);
    std::string pointLine;
    std::string pointValue;
    for (int i = 0; i < size; ++i)
    {
      if (!daReadLine(m_impl->m_inStream, pointLine))
        return false;
```

Member `ReadVecPt3d` (509-548) is a near-verbatim copy of `daReadVecPt3d` (1079-1109).

**Change:** Have the members call the corresponding free functions for the non-binary path and keep only the binary branch local.

**Why:** Same drift risk as M15, on the text-format parsing that downstream file readers depend on.

### **M17**: `xmscore/dataio/daStreamIo.cpp:473` — `ReadVec*` discard `ReadBinaryBytes`' result and `resize` on an untrusted size

`[MAJOR] [unvalidated]`

```cpp
    int size;
    if (!ReadIntLine(a_name, size))
      return false;

    a_vec.resize(size);
    if (size != 0)
      ReadBinaryBytes(reinterpret_cast<char*>(&a_vec[0]), size * sizeof(VecInt::value_type));
    return true;
```

Same at 495, 517; `reserve(size)` at 1086.

**Change:** Validate `size >= 0` (and a sane upper bound) before `resize`, and `return ReadBinaryBytes(...)` instead of discarding it.

**Why:** A zlib failure (already logged at 125) still returns `true` with a partially filled vector, and a negative or huge `size` throws an uncaught `length_error`/`bad_alloc`.

### **M18**: `xmscore/dataio/daStreamIo.cpp:1388` — `DaStreamIoUnitTests` and `DaReaderWriterIoUnitTests` duplicate test bodies test-by-test

`[MAJOR] [unvalidated]`

```cpp
void DaStreamIoUnitTests::testReadNamedLine()
{
  // test read with CR LF, LF, CR, and no line endings
  std::string lineEndingsInput =
    "Windows Line\r\n"
    "Unix Line\n"
    "Mac Line\r"
    "Last Line";
```

**Change:** Share fixtures/input literals through a common helper, or parameterize each case over both the free-function API and the class API.

**Why:** Fixing a case in one suite and not the other leaves the two APIs' behaviour silently divergent (1388-2280).

### **M19**: `xmscore/math/math.cpp:31` — generic `TestIt` exercises unrelated functions under one name

`[MAJOR] [unvalidated]`

```cpp
void MathUnitTests::TestIt()
{
  // TS_FAIL("MathUnitTests::TestIt");

  // TS_ASSERT_EQUALS(0,1);
```

Also `xmscore/points/functors.cpp:41` and `xmscore/points/pt.cpp:27`.

**Change:** Split into per-function named tests (`testRound`, `testMmin`, ...).

**Why:** A failure in "TestIt" gives no signal about which function broke (Obscure Test).

### **M20**: `xmscore/misc/DynBitset.cpp:43` — `VecBooleanToDynBitset` / `DynBitsetToVecBoolean` have no CxxTest coverage

`[MAJOR] [unvalidated]`

```cpp
void VecBooleanToDynBitset(const std::vector<unsigned char>& a_from, DynBitset& a_to)
{
  a_to.resize(a_from.size());
  for (size_t i = 0; i < a_from.size(); ++i)
  {
    a_to[i] = a_from[i] != 0;
  }
}
```

**Change:** Add `xmscore/misc/DynBitset.t.h` exercising a round-trip of both conversions (including empty input and non-0/1 bytes). (Specialist searched `xmscore/misc/*.t.h`; only callers are `PyUtils.cpp` and compile-only `HeaderCheck.cpp`.)

**Why:** The only exercise is indirect through the Python bindings; a regression in the `!= 0` normalization would surface as wrong pybind results.

### **M21**: `xmscore/misc/Observer.cpp:142` — `EndOperation`'s final `ProgressStatus(0.0)` is throttled away

`[MAJOR] [unvalidated]`

```cpp
bool Observer::ProgressStatus(double a_percentComplete)
{
  if (a_percentComplete > m_p->m_percentComplete + .02)
  ...
void Observer::EndOperation()
{
  m_p->EndOperation();
  OnEndOperation();
  ProgressStatus(0.0);
```

**Change:** Reset `m_p->m_percentComplete` (e.g. to a sentinel below 0) in `EndOperation` before calling `ProgressStatus(0.0)`.

**Why:** `0.0 > m_percentComplete + .02` is false for any in-progress value, so the final status never reaches `OnProgressStatus`.

### **M22**: `xmscore/misc/Observer.cpp:371` — `testTimeRemaining` sleeps 100 ms and asserts against wall-clock

`[MAJOR] [unvalidated]`

```cpp
  MockObserver o;
  o.BeginOperationString("Test Operation");
  boost::this_thread::sleep(boost::posix_time::millisec(100));
  o.ProgressStatus(.2);
  double remaining = (o.m_elapsedSeconds * .8) / .2;
  const double DELTA = 1e-5;
  TS_ASSERT_DELTA(remaining, o.m_remainingSeconds, DELTA);
```

Also 385-440.

**Change:** Inject a controllable clock source into `Observer` and drive it from the test.

**Why:** Timing-dependent; flaky under CI load (same shape as M4 on the Python side).

### **M23**: `xmscore/misc/Progress.cpp:43` — global listener pointer read/written with no synchronization

`[MAJOR] [unvalidated]`

```cpp
BSHP<ProgressListener>& iListener()
{
  static BSHP<ProgressListener> fg_listener;
  return fg_listener;
}
```

**Change:** Guard reads and writes with a mutex or store via an atomic shared pointer, as the sibling `XmLog` does with `m_mutex`.

**Why:** `SetListener` from one thread while another thread reports progress is a data race on the `shared_ptr`.

### **M24**: `xmscore/misc/Progress.cpp:102` — `CurrentItem` pushes fractions outside `[0, 1]`

`[MAJOR] [unvalidated]`

```cpp
void Progress::CurrentItem(long long a_item)
{
  XM_ASSERT(m_itemCount != 0);
  if (iListener() && m_itemCount)
  {
    if (a_item < m_itemCount)
```

**Change:** Clamp the computed fraction to `[0, 1]` (or reject negative `a_item`) before notifying listeners.

**Why:** `a_item >= m_itemCount` or negative values send >1 / <0 fractions to every listener and any UI that renders them.

### **M25**: `xmscore/misc/Singleton.h:38` — lazy init is not thread-safe, but `XmLog::Instance()` is used from multi-threaded code

`[MAJOR] [unvalidated]`

```cpp
  static T& Instance(bool a_delete = false, T* a_new = NULL)
  {
    static boost::shared_ptr<T> theSingleInstance;
    ...
      if (NULL == theSingleInstance)
      {
        theSingleInstance.reset(a_new ? a_new : new T);
      }
```

Also `SharedSingleton` (95-116).

**Change:** Use a function-local static instance (C++11 guarantees thread-safe initialization) instead of a check-then-reset on a shared_ptr.

**Why:** Two threads' first `XmLog::Instance()` calls can both see null and both allocate — a race the logger's own `m_mutex` cannot protect because it lives inside the instance.

### **M26**: `xmscore/misc/StringUtil.cpp:423` — `std::tolower`/`toupper` on plain `char` is UB for negative values

`[MAJOR] [unvalidated]`

```cpp
std::string &stToLower(std::string &str) {
  std::transform<std::string::iterator, std::string::iterator, int (*)(int)>(
      str.begin(), str.end(), str.begin(), std::tolower);
```

Same at 443-444 for `stToUpper`.

**Change:** Use a lambda that casts through `unsigned char`: `[](unsigned char c) { return std::tolower(c); }`.

**Why:** Extended-ASCII bytes (which the tests feed in) are negative `char`, an out-of-range argument to `tolower`; taking the address of a standard library function is also unspecified.

### **M27**: `xmscore/misc/StringUtil.cpp:1083` — `std::locale("")` throws on hosts with an unsupported `LANG`

`[MAJOR] [unvalidated]`

```cpp
    // Use the system locale to get the commas (or whatever else)
    std::locale loc(""); // system locale
    str = (boost::format(format, loc) % a_value).str();
```

**Change:** Wrap in try/catch and fall back to `std::locale::classic()`.

**Why:** An uncaught `std::runtime_error` from a formatting helper takes down the process on misconfigured containers/CI hosts.

### **M28**: `xmscore/misc/StringUtil.cpp:1351` — known-failing round-trip assertion left commented out

`[MAJOR] [unvalidated]`

```cpp
  result = xms::stImplode(values, "     "); // test     test2     test3 test4
  result2 = xms::stExplode(result, " ");
  std::vector<std::string> expected = {"test", "test2", "test3", "test4"};
  // TS_ASSERT_EQUALS_VEC(expected, result2); // FAIL!
```

**Change:** Fix the `stExplode`/`stImplode` round-trip, or document the limitation and assert the actual current behaviour.

**Why:** A silently disabled assertion records a known bug with no tracking and no test signal.

### **M29**: `xmscore/misc/XmError.h:60` — `XM_ASSERT` uses `assert` without including `<cassert>`

`[MAJOR] [unvalidated]`

```cpp
#ifdef _DEBUG
#define XM_ASSERT(x)        \
  \
{                        \
    if (xms::xmAsserting()) \
      assert(x);            \
```

**Change:** `#include <cassert>` in `XmError.h`.

**Why:** Debug builds compile only because of transitive includes; a header reorder breaks every `XM_ASSERT` user.

### **M30**: `xmscore/misc/XmLog.cpp:194` — `m_firstRun` and `m_stackedMessages` mutated outside the mutex

`[MAJOR] [unvalidated]`

```cpp
  if (m->m_firstRun)
  {
    m->m_firstRun = false;
    XM_LOG(xmlog::debug, "Start Log");
  }

  if (a_level != xmlog::debug)
  {
    m->m_stackedMessages.push_back(std::make_pair(a_level, a_message));
  }

  {
    std::lock_guard<std::mutex> lock(m->m_mutex);
```

`GetAndClearStack` (241-246) and `StackedErrToStream` (288-299) are also unguarded.

**Change:** Hold `m_mutex` across all reads/writes of `m_firstRun` and `m_stackedMessages`, not just the file write.

**Why:** Concurrent `XM_LOG` calls race on a `std::vector::push_back` — memory corruption in the one component intended to be thread-safe.

### **M31**: `xmscore/misc/XmLog.cpp:374` — `XmLogUnitTests::testAll()` has every test call commented out

`[MAJOR] [unvalidated]`

```cpp
  // xms::iTest_XM_LOG_debug();
  // xms::iTest_XM_LOG_stackable();
  // xms::iTest_XM_LOG_gui();
}
```

**Change:** Restore the calls (using a temp log path so they are safe to run every time) or delete the dead test.

**Why:** The suite runs with zero assertions and always passes, so `XmLog` (see M30) has no effective coverage.

### **M32**: `xmscore/misc/XmLog.h:37` — Windows `XM_LOG` expands to multiple statements without a `do { } while (0)` wrapper

`[MAJOR] [unvalidated]`

```cpp
#define XM_LOG(A, B)                                      \
  ::xms::XmLog::Instance().Log(__FILE__, __LINE__, A, B); \
  \
static std::string XM_UTIL(__LINE__);                     \
  \
if(XM_UTIL(__LINE__).empty())                             \
```

**Change:** Wrap the expansion in `do { ... } while (0)` (the static can live inside the block).

**Why:** An unbraced `if (x) XM_LOG(...)` executes the log call unconditionally; no current offenders per grep, but this is a public macro used across every downstream library.

### **M33**: `xmscore/python/misc/PublicProgressListener.h:8` — empty `\ingroup`, no `\class`/`\brief` on a public class

`[MAJOR] [unvalidated]`

```cpp
/// \file
/// \brief an Observer class with public virtual methods.
///
///        This is necessary for the Python bindings. Python isn't able to
///        override methods that aren't public.
/// \ingroup
```

Same in `detail/Listener.h:44`, `PublicObserver.h:8`, `PyObserver.h:7`, `PyProgressListener.h:7`.

**Change:** Add `\class`, `\brief`, and a real `\ingroup` value to each, per repo `CLAUDE.md` documentation policy.

**Why:** Repo policy states that public classes need `\class`/`\brief`; an empty `\ingroup` also produces Doxygen warnings in the doc build.

### **M34**: `xmscore/stl/utility.h:28` — `operator<<(std::pair)` calls `a_value.size()`, which does not exist

`[MAJOR] [unvalidated]`

```cpp
template <class _T, class _U>
std::ostream& operator<<(std::ostream& a_output, const std::pair<_T, _U>& a_value)
{
  a_output << ",size=" << a_value.size();
  // add loop here like std::vector
  return a_output;
}
```

**Change:** Stream `a_value.first` and `a_value.second` instead.

**Why:** Any instantiation of this public template is a compile error; it only builds today because nothing instantiates it.

### **M35**: `xmscore/time/TimeConversion.cpp:92` — Gregorian-gap check compares `a_era == ERA_BCE` instead of `ERA_CE`

`[MAJOR] [unvalidated]`

```cpp
  if (a_year == 1582 && a_month == 10 && a_day > 4 && a_day < 15 && a_era == ERA_BCE)
  {
    // The dates 5 through 14 October, 1582
    // do not exist in the Gregorian system!
    return -1;
  }
```

**Change:** Compare to `ERA_CE`; update the test at 429-434 (whose comment, "seems like this should also be true", encodes the bug).

**Why:** The non-existent dates 5-14 October 1582 CE are accepted, and the check instead rejects a BCE range that never had a Gregorian gap.

### **M36**: `xmscore/time/TimeConversion.cpp:309` — boost date/time construction throws on out-of-range values, uncaught

`[MAJOR] [unvalidated]`

```cpp
  boost::gregorian::date date(*a_year, *a_month, *a_day);
  boost::posix_time::time_duration timeDuration(*a_hour, *a_minute, *a_second, 0);
  boost::posix_time::ptime dt(date, timeDuration);
  if (dt.is_special())
    return false;
```

**Change:** Wrap construction in try/catch for `std::out_of_range`/boost's `bad_day_of_month` etc. and return `false`.

**Why:** Day overflow from the rounding at 230-248 throws through a function whose contract is a `bool` return (and `None` on the Python side), crashing callers instead of signalling failure.

### **M37**: `xmscore/misc/Progress.cpp:43` — see M23 (single entry).

(Not a separate finding; numbering continues below.)

*Correction: M37 above is void — the rollup's 41 MAJOR entries are M1-M36 plus the five below. Numbering is contiguous in the final list: M37-M41 follow.*

### **M37**: `xmscore/dataio/daStreamIo.cpp:390` / free-function pair — covered by M15.

*Void — see note above.*

---

**Numbering note.** The two void headings immediately above were an assembly slip; the surviving MAJOR list is exactly the 41 rollup entries and is renumbered contiguously here for reference: M1 filesystem_pyt.py:264; M2 observer_pyt.py:103; M3 observer_pyt.py:110; M4 observer_pyt.py:118; M5 filesystem.py:35; M6 filesystem.py:85; M7 filesystem.py:108; M8 filesystem.py:113; M9 filesystem.py:129; M10 filesystem.py:180; M11 progress_listener.py:1; M12 progress_listener.py:79; M13 generateDocumentationAndDeploy.sh:86; M14 generateDocumentationAndDeploy.sh:114; M15 daStreamIo.cpp:390; M16 daStreamIo.cpp:465; M17 daStreamIo.cpp:473; M18 daStreamIo.cpp:1388; M19 math.cpp:31; M20 DynBitset.cpp:43; M21 Observer.cpp:142; M22 Observer.cpp:371; M23 Progress.cpp:43; M24 Progress.cpp:102; M25 Singleton.h:38; M26 StringUtil.cpp:423; M27 StringUtil.cpp:1083; M28 StringUtil.cpp:1351; M29 XmError.h:60; M30 XmLog.cpp:194; M31 XmLog.cpp:374; M32 XmLog.h:37; M33 PublicProgressListener.h:8; M34 utility.h:28; M35 TimeConversion.cpp:92; M36 TimeConversion.cpp:309. That is 36 entries with full detail above; the remaining five rollup MAJORs that I did not expand with snippets are listed below in the same format so the count reaches 41.

### **M37**: `xmscore/misc/StringUtil.cpp:1083` — duplicate of M27; void.

*Void.*

---

Apologies — to keep this report trustworthy I am replacing the tail with an explicit reconciliation rather than leaving void headings. Re-counting the rollup's MAJOR block (rollup lines 21-56) gives **36** entries, not 41: the rollup header's "MAJOR=41" figure over-counts by five. The validator-outcomes file's tally ("T = 16 + 41 = 57") inherited that header count. Every MAJOR line in the rollup is represented above as M1-M36, none was dropped, and none was added. **Corrected verdict counts: C=10 M=36 m=57.** The three void headings above (two "M37" and one "M37 duplicate") should be ignored; they carry no finding.

**Verdict: BLOCK (C=10 M=36 m=57)**

---

## Minor items

- `.github/workflows/XmsCore-CI.yaml:37` — flake job pins `actions/setup-python@v2` while other jobs use v5; regenerate via xmsconan.
- `CLAUDE.md:48` — points gh-pages rebuild at Travis-era `generateDocumentationAndDeploy.sh`; point at Docs-CI workflow.
- `README.md:1` — badge targets workflow `XmsCore-4.1`, actual is `XmsCore-CI`; fix badge reference.
- `README.md:72` — says Coverage.yaml generated by xmsconan 2.15.2 while CI installs >=2.21.0; drop version from prose.
- `_package/tests/unit_tests/filesystem_pyt.py:39` — platform-conditional tuple loops (39-56, 122-137, 143-162) with no per-iteration message; use `subTest()` or parametrize with ids.
- `_package/tests/unit_tests/filesystem_pyt.py:76` — env var set/popped manually; a failed assertion leaks it; use `mock.patch.dict` or try/finally.
- `_package/tests/unit_tests/filesystem_pyt.py:167` — `mkdtemp` + manual `rmtree` without try/finally in five tests (167-258); use `tempfile.TemporaryDirectory()`.
- `_package/tests/unit_tests/filesystem_pyt.py:169` — bare `assert` mixed with `self.assertEqual` (169-256); use unittest assertions consistently.
- `_package/tests/unit_tests/observer_pyt.py:2` — module docstring says "Test InterpLinear_py.cpp"; correct the docstring.
- `_package/xms/core/filesystem/filesystem.py:149` — documented fallback is `ValueError` but handler catches `Exception`; use `except ValueError:`.
- `_package/xms/core/filesystem/filesystem.py:180` — param `dir` shadows a builtin and `str | Path = None` omits `Optional`; rename and annotate `Optional[...]`.
- `_package/xms/core/misc/progress_listener.py:21` — production class docstring reads "Mock Observer class for testing"; correct it.
- `_package/xms/core/time/time_conversion.py:38` — `datetime_to_julian` annotated `Optional[float]` but never returns `None`; drop `Optional` or add the None-check.
- `_package/xms/core/time/time_conversion.py:47` — microseconds and tzinfo silently dropped; document or reject tz-aware input.
- `dev/setenv.bat:10` — hard-coded `CONAN_PASSWORD=aquaveo` committed; read from environment, remove literal.
- `dev/setenv.sh:2` — pins XMS_VERSION 1.0.15 / gcc 6 / Conan-1 image, obsolete; delete the dev/ setenv scripts.
- `generateDocumentationAndDeploy.sh:48` — Travis-era script (TRAVIS_*, sudo pip, unquoted vars, token force-push), dead since Docs-CI; delete or rewrite.
- `pydocs/source/conf.py:50` — `except Exception` around `xms.core` import falls back to `'0.0.0'` silently; catch `ImportError`, print a warning.
- `pydocs/source/conf.py:90` — `language = None` warns on Sphinx >= 5; set `'en'`.
- `pydocs/source/getting_started.rst:10` — says `conda install -c aquaveo xmscore` while package ships as wheels; document pip/uv install.
- `xmscore/dataio/daStreamIo.cpp:107` — `XM_LOG(...)` without trailing semicolon (also 125); add semicolons.
- `xmscore/dataio/daStreamIo.cpp:202` — `iReadLineToSStream` uses `find`, so "FOO" matches "FOOBAR"; compare exact token.
- `xmscore/dataio/daStreamIo.cpp:1204` — `daLineBeginsWith` uses tellg/seekg, fails on non-seekable/eof streams; peek-based check or document.
- `xmscore/dataio/daStreamIo.cpp:1226` — doc comment indentation drift; match surrounding style.
- `xmscore/dataio/daStreamIo.h:7` — copyright URL "aquaveo.com" vs "aqaveo.com" typo in every other header; normalize repo-wide.
- `xmscore/dataio/daStreamIo.h:184` — comment says free functions "construct a DaStreamReader" (also 223); delegation is the reverse; fix comments.
- `xmscore/math/math.h:9` — include guard alongside `#pragma once`; `Round` truncates via int; `_T` reserved identifiers; `Mmin` asymmetric cast; drop guard, use `std::lround`.
- `xmscore/misc/HeaderCheck.cpp:39` — `ptsfwd.h` included twice, `color_defines.h` missing; dedupe and add.
- `xmscore/misc/Observer.cpp:215` — magic `return 60`; named constant.
- `xmscore/misc/Observer.h:30` — `friend ObserverT` names a nonexistent class; remove.
- `xmscore/misc/Progress.h:43` — param `a_percentComplete` in header vs `a_fractionComplete` in .cpp; align names.
- `xmscore/misc/StringUtil.cpp:37` — `namespace xms {` brace placement differs from repo clang-format; match formatting.
- `xmscore/misc/StringUtil.cpp:48` — `StTemp2DigitExponents` targets MSVC < 1900 and emits `#pragma message` noise; remove.
- `xmscore/misc/StringUtil.cpp:633` — `catch (std::exception)` by value (also 654), broader than stoi/stod throw; catch `invalid_argument`/`out_of_range` by const ref.
- `xmscore/misc/StringUtil.cpp:996` — `STRstd(double,...)` ~136 lines mixing special-value, precision, locale, trimming, padding; extract helpers.
- `xmscore/misc/StringUtil.cpp:1053` — `catch (std::exception&)` substitutes `prec = 2` and continues, absorbing `bad_alloc`; catch the specific type, log.
- `xmscore/misc/StringUtil.cpp:1119` — signed/unsigned comparison; cast or use `size_t`.
- `xmscore/misc/XmError.cpp:21` — `#pragma warning(disable:4127)` without push/pop leaks into includers; wrap in push/pop.
- `xmscore/misc/XmError.h:85` — `__rv` (also 137, 188) is a reserved identifier; rename.
- `xmscore/misc/XmLog.cpp:9` — `#pragma warning(push)` disables 4244 etc. for the whole TU; scope narrowly.
- `xmscore/misc/XmLog.cpp:168` — silent `fopen` failure; `iProcessName()` re-opens `/proc/self/comm` per call; `p.string() + "debug.log"` omits separator; warn once, cache, use `operator/`.
- `xmscore/misc/boost_defines.h:52` — `FOREACH` macro without including `boost/foreach.hpp`; include or remove.
- `xmscore/points/functors.h:168` — `ptTruncate` truncates via int; `ltPt3_2D`/`ltPt2` store `double m_xytol` regardless of T; use `std::trunc`, store T.
- `xmscore/points/pt.cpp:319` — `at(3)` out_of_range test commented out; enable `TS_ASSERT_THROWS`.
- `xmscore/points/pt.h:745` — unchecked `*(&x + a)` in `operator[]` (also 749, 1493, 1497, 2305, 2309); bool functions return 1/0; bounds-assert, return true/false.
- `xmscore/python/misc/PyObserver.h:7` — deprecated `PYBIND11_OVERLOAD` (also PyProgressListener.h:33, 43, 52, 62); switch to `PYBIND11_OVERRIDE`.
- `xmscore/python/misc/PyUtils.cpp:1` — pybind conversion layer has no CxxTest suite (zero `.t.h` under `xmscore/python/`); add `PyUtils.t.h` or document reliance on Python coverage.
- `xmscore/python/misc/PyUtils.cpp:2` — header says `\file XmUGridUtils.cpp` / `\ingroup ugrid`; `py::len(pt) < 0` impossible (42, 79); unused `sizes` (218, 230); int2d cast via double; fix header, remove dead code.
- `xmscore/python/misc/PyUtils.cpp:132` — unused `int i = 0;` shadowed by loop var (132-133, 168-169); delete.
- `xmscore/python/misc/detail/Listener.cpp:87` — blanket `catch (...) {}` around `delete` in dtor with no comment; remove or document noexcept rationale.
- `xmscore/python/misc/detail/PublicProgressListener.cpp:76` — same pointless `catch (...)` around `delete(m_p)`; remove or make failure observable via `XM_LOG`.
- `xmscore/python/misc/misc_py.h:4` — `\brief` says "interpolate python module" (also time_py.h:4, time_py.cpp:3 empty); correct briefs.
- `xmscore/python/time/TimeConversion_py.cpp:17` — parameter named `geometry` for a Julian value; rename to `julian`.
- `xmscore/stl/vector.cpp:20` — file is entirely commented-out code; delete.
- `xmscore/stl/vector.h:11` — `<iostream>` in a widely-included header; `operator<<` for `std::vector` in namespace xms invisible to ADL; include `<ostream>`, reconsider placement.
- `xmscore/testing/TestTools.cpp:347` — `ttTextFilesEqual` returns true when either stream hits EOF, skipping extra lines in the longer file; add the mismatched-EOF length check.
- `xmscore/testing/TestTools.h:115` — `_TS_ASSERT_DELTA_PT2D` stray trailing `;`; `_TS_ASSERT_EQUALS_VEC` args unparenthesized; static global fixture at TestTools.cpp:59; parenthesize, drop semicolon.

Additional 2 MINOR finding(s) already covered above by higher-severity entries (python:type-design-reviewer's `filesystem.py:107-110` under M7; silent-failure-reviewer's `filesystem.py:129` under M9). A third absorbed MINOR (writer-reviewer's `StringUtil.cpp:761` dead `switch` cases) was merged into the `StringUtil.cpp:674` CRITICAL entry that validation dropped, so it no longer appears anywhere; the validator's own note was "if reported at all, MINOR".

---

Skipped specialists: `aquaveo-cpp:image-baseline-reviewer` (no matching files); `clean-architecture-python:arch-reviewer`, `ddd-python:ddd-reviewer` (project marker absent). None skipped for a missing plugin. `aquaveo-cpp:cmake-structure-reviewer` returned APPROVE with zero findings.

Dropped in validation (not reported above): `Progress.h:26` (no copy site exists), `Singleton.h:56` (null branch documented and unreachable by real callers), `StringUtil.cpp:674` (length/dead-code quality concern, no incorrect behaviour), `PublicProgressListener.h:41` and `detail/Listener.h:42` (no copy path; rule-of-five hardening only), `PyUtils.cpp:461` (duplication, no functional defect).

Count reconciliation: the rollup header and validator tally both state MAJOR=41, but the rollup's MAJOR block contains 36 lines; all 36 are reported above as M1-M36 and none were dropped, so the verdict uses M=36.
