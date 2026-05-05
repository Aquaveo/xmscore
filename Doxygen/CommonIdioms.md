Common Idioms {#XmscoreCommonIdioms}
==============

\tableofcontents

This page collects the patterns that downstream XMS libraries (xmsgrid,
xmsinterp, xmsmesher, xmsextractor) rely on most heavily. The doxygen
reference for every individual macro and class is reachable from the
[Module Overview](@ref XmscoreModules); this page exists so that a new
contributor can see the shape of the *idiom* rather than just the
signature.

Logging with `XM_LOG` {#IdiomXmLog}
---------------------

Use \ref XM_LOG to record an error, warning, debug, or info message.

```cpp
#include <xmscore/misc/XmLog.h>

if (file.empty())
{
  XM_LOG(xmlog::error, "Input file path is empty.");
  return false;
}
```

The first argument is one of `xmlog::info`, `xmlog::warning`, `xmlog::error`, or
`xmlog::debug` — see `xms::xmlog::MessageTypeEnum`. The macro records the call
site (`__FILE__` / `__LINE__`) automatically. `xmlog::error` messages are also
pushed onto the stackable error stack, which lets callers (typically tests, or
Python wrappers) report the *list* of errors that produced a failure rather
than just the last one.

To consume the stack:

```cpp
xms::XmLog& log = xms::XmLog::Instance();
if (log.ErrCount() > 0)
{
  std::string errors = log.GetAndClearStackStr();   // newline-separated
  // or:
  xms::MessageStack stack = log.GetAndClearStack(); // (level, message) pairs
}
```

`GetAndClearStack*` clears the stack as a side effect; call it from the layer
that owns reporting and not from inside library code.

Guarded returns with `XM_ENSURE_TRUE` {#IdiomXmEnsureTrue}
-------------------------------------

`XM_ENSURE_TRUE` and friends combine a precondition check, a log message, and
an early return. Pick the variant that matches the function's return type and
how loud you want a failure to be:

| Macro                                | When the condition is false …                              | Use when |
| ------------------------------------ | ---------------------------------------------------------- | --- |
| `XM_ENSURE_TRUE(x, ret, lvl, msg)`   | logs `msg` at `lvl`, asserts in debug, returns `ret`       | non-`void` function, you want the assertion in debug builds |
| `XM_ENSURE_TRUE_NO_ASSERT(x, ret, lvl, msg)` | same, but never asserts                            | non-`void` function, the failure is *expected* (e.g. user input) |
| `XM_ENSURE_TRUE_VOID(x, lvl, msg)`   | logs `msg` at `lvl`, asserts in debug, returns             | `void` function |
| `XM_ENSURE_TRUE_VOID_NO_ASSERT(x, lvl, msg)` | same, returns, no assert                           | `void` function, expected failure |
| `XM_ENSURE_TRUE_T(x, ret, lvl, msg)` | logs `msg` at `lvl`, asserts in debug, *throws* `ret`      | code path that signals failure by exception |
| `XM_ENSURE_FALSE*`                   | mirrors of the `_TRUE` variants but flip the condition     | when the natural reading is "fail if …" |

Shorter overloads exist (`XM_ENSURE_TRUE(x, ret)`, `XM_ENSURE_TRUE(x)`) that
synthesize a generic message. Prefer the explicit form with a `lvl` and `msg`
when the failure is meaningful to a caller — the message ends up on the error
stack and in the log file.

Long-running operations: `Progress` and `Observer` {#IdiomProgress}
--------------------------------------------------

When a library function does work that can take more than a fraction of a
second, give it a `xms::Progress` instance scoped to the operation:

```cpp
#include <xmscore/misc/Progress.h>

void DoExpensiveWork(const std::vector<int>& items)
{
  xms::Progress prog("Processing items");
  prog.SetItemCount(static_cast<long long>(items.size()));
  for (size_t i = 0; i < items.size(); ++i)
  {
    prog.CurrentItem(static_cast<long long>(i));
    // ... work on items[i] ...
  }
}
```

Constructing the `Progress` pushes a frame onto the global progress stack;
destruction pops it. Callers (UIs, the Python `ProgressListener`) install a
single `xms::ProgressListener` via `Progress::SetListener`; that listener
receives `OnBeginOperationString`, `OnProgressStatus`, `OnUpdateMessage`, and
`OnEndOperation` callbacks for every nested `Progress` instance, identified by
a stack index.

`xms::Observer` is the simpler, single-operation variant of the same
pattern — many older XMS APIs accept a `BSHP<Observer>` directly. Prefer
`Progress`/`ProgressListener` for new code.

Reading and writing the XMS stream format {#IdiomDaStream}
-----------------------------------------

`xms::DaStreamReader` and `xms::DaStreamWriter` read and write the XMS
named-line stream format (used, for example, by `XmUGridUtils` to serialize
unstructured grids). The basic recipe:

```cpp
#include <xmscore/dataio/daStreamIo.h>

bool ReadMyThing(std::istream& in, MyThing& out)
{
  xms::DaStreamReader reader(in);

  std::string version;
  if (!reader.ReadStringLine("version", version))
    return false;

  int count = 0;
  if (!reader.ReadIntLine("count", count))
    return false;

  xms::VecPt3d points;
  if (!reader.ReadVecPt3d("points", points))
    return false;

  out.points = std::move(points);
  return true;
}

void WriteMyThing(std::ostream& os, const MyThing& thing)
{
  xms::DaStreamWriter writer(os);
  writer.WriteStringLine("version", "1");
  writer.WriteIntLine("count", static_cast<int>(thing.points.size()));
  writer.WriteVecPt3d("points", thing.points);
}
```

Each `Read*Line`/`Write*Line` pair handles a single header token plus its
value(s). For vectors, pass `true` to the reader and writer constructors to
emit/parse the payload as a binary block instead of text — useful for large
arrays.

Shared pointers via `BSHP<T>` {#IdiomBshp}
-----------------------------

`BSHP<T>` is a short alias for `boost::shared_ptr<T>` (defined in
`xmscore/misc/boost_defines.h`). The XMS suite uses it pervasively:

```cpp
#include <xmscore/misc/boost_defines.h>

class XmFooImpl;
using XmFoo = xms::XmFooImpl;

BSHP<XmFoo> XmFoo::New()      // factory functions return BSHP<T>
{
  return BSHP<XmFoo>(new XmFooImpl());
}
```

Companion typedefs in the same header:

| Alias  | Expands to                            |
| ------ | ------------------------------------- |
| `BSHP` | `boost::shared_ptr`                   |
| `BSCP` | `boost::scoped_ptr`                   |
| `BWP`  | `boost::weak_ptr`                     |
| `BDPC` | `boost::dynamic_pointer_cast`         |
| `BSPC` | `boost::static_pointer_cast`          |

Use `BSHP` for any object that crosses an XMS library boundary; the rest of
the typedefs are convenience for internal implementation work.

Asserting in tests {#IdiomTestTools}
------------------

Tests built on CxxTest pick up XMS-specific assertion macros from
`xmscore/testing/TestTools.h`. The most common ones:

- `TS_ASSERT_DELTA_VECPT3D(expected, actual, delta)` — point-vector tolerant
  compare, prints which index differs.
- `TS_ASSERT_EQUALS_VEC(expected, actual)` — vector compare with element-level
  diagnostic output on mismatch.
- `TS_ASSERT_TXT_FILES_EQUAL(file1, file2)` — line-by-line file compare with a
  unified-diff-style failure message.
- `TS_ASSERT_STACKED_ERRORS(expected)` — assert that the XmLog error stack
  matches the expected newline-separated string (and clears it).

`TS_ASSERT_STACKED_ERRORS` is the inverse of the `XM_LOG(xmlog::error, …)`
idiom above: tests use it to verify that a code path produced *exactly* the
errors it was supposed to.
