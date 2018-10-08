#pragma once
//------------------------------------------------------------------------------
/// \file
/// \ingroup core_testing
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 3. Standard library headers
#include <sstream> // for sstream
#include <vector>

// 4. External library headers
//#ifdef CXX_TEST
#include <cxxtest/TestSuite.h>
//#endif // ifdef CXX_TEST

// 5. Shared code headers
#include <xmscore/stl/utility.h>

namespace xms
{
//------------------------------------------------------------------------------
/// \brief Tests if array and vector are equal and gives useful output.
//------------------------------------------------------------------------------
#define _TS_ASSERT_EQUALS_AVEC(f, l, expected, length, actual) \
  xms::ttAssertEqualsAVec(f, l, expected, length, actual)
//------------------------------------------------------------------------------
/// \brief Tests if array and vector are equal and gives useful output.
//------------------------------------------------------------------------------
#define TS_ASSERT_EQUALS_AVEC(expected, length, actual) \
  _TS_ASSERT_EQUALS_AVEC(__FILE__, __LINE__, expected, length, actual)

//------------------------------------------------------------------------------
/// \brief Tests if two vectors are equal and gives useful output.
//------------------------------------------------------------------------------
#define _TS_ASSERT_DELTA_VEC(f, l, a, b, delta) xms::ttAssertDeltaVec((f), (l), (a), (b), (delta))
//------------------------------------------------------------------------------
/// \brief Tests if two vectors are equal and gives useful output.
//------------------------------------------------------------------------------
#define TS_ASSERT_DELTA_VEC(a, b, delta) _TS_ASSERT_DELTA_VEC(__FILE__, __LINE__, a, b, delta)

//------------------------------------------------------------------------------
/// \brief Tests if two 2D vectors are equal within delta and gives useful output.
//------------------------------------------------------------------------------
#define _TS_ASSERT_DELTA_VEC2D(f, l, a, b, delta) \
  xms::ttAssertDeltaVec2D((f), (l), (a), (b), (delta))
//------------------------------------------------------------------------------
/// \brief Tests if two 2D vectors are equal within delta and gives useful output.
//------------------------------------------------------------------------------
#define TS_ASSERT_DELTA_VEC2D(a, b, delta) _TS_ASSERT_DELTA_VEC2D(__FILE__, __LINE__, a, b, delta)

//------------------------------------------------------------------------------
/// \brief Tests if two 2D vectors are equal and gives useful output.
//------------------------------------------------------------------------------
#define _TS_ASSERT_EQUALS_VEC2D(f, l, expected, actual) \
  xms::ttAssertEqualsVec2D((f), (l), (expected), (actual))
//------------------------------------------------------------------------------
/// \brief Tests if two 2D vectors are equal and gives useful output.
//------------------------------------------------------------------------------
#define TS_ASSERT_EQUALS_VEC2D(expected, actual) \
  _TS_ASSERT_EQUALS_VEC2D(__FILE__, __LINE__, expected, actual)

//------------------------------------------------------------------------------
/// \brief Tests if two point vectors are equal within delta and gives useful output.
//------------------------------------------------------------------------------
#define _TS_ASSERT_DELTA_VECPT3D(f, l, a, b, delta)                                         \
  {                                                                                         \
    if (a.size() != b.size())                                                               \
    {                                                                                       \
      std::stringstream msg;                                                                \
      msg << "Incorrect size Expecting size: " << a.size() << " Found size: " << b.size();  \
      _TS_FAIL(f, l, msg.str().c_str());                                                    \
    }                                                                                       \
    else                                                                                    \
    {                                                                                       \
      for (size_t i = 0; i < a.size(); ++i)                                                 \
      {                                                                                     \
        if (!::xms::gmEqualPointsXYZ(a.at(i).x, a.at(i).y, a.at(i).z, b.at(i).x, b.at(i).y, \
                                     b.at(i).z, delta))                                     \
        {                                                                                   \
          std::stringstream msg;                                                            \
          msg << "Incorrect value at position : " << i << " Expecting: " << a.at(i)         \
              << " Found: " << b.at(i);                                                     \
          _TS_FAIL(f, l, msg.str().c_str());                                                \
        }                                                                                   \
      }                                                                                     \
    }                                                                                       \
  \
}
//------------------------------------------------------------------------------
/// \brief Tests if two point vectors are equal within delta and gives useful output.
//------------------------------------------------------------------------------
#define TS_ASSERT_DELTA_VECPT3D(a, b, delta) \
  _TS_ASSERT_DELTA_VECPT3D(__FILE__, __LINE__, a, b, delta)
//------------------------------------------------------------------------------
/// \brief Tests if two point vectors are equal within delta and gives useful output.
/// \deprecated
//------------------------------------------------------------------------------
#define TS_ASSERT_DELTA_VEC_MP3(a, b, delta) \
  _TS_ASSERT_DELTA_VECPT3D(__FILE__, __LINE__, a, b, delta)

//------------------------------------------------------------------------------
/// \brief Tests if two point vectors are equal within delta and gives useful output.
//------------------------------------------------------------------------------
#define _TS_ASSERT_DELTA_VECPT2D(f, l, a, b, delta)                                        \
  {                                                                                        \
    if (a.size() != b.size())                                                              \
    {                                                                                      \
      std::stringstream msg;                                                               \
      msg << "Incorrect size Expecting size: " << a.size() << " Found size: " << b.size(); \
      _TS_FAIL(f, l, msg.str().c_str());                                                   \
    }                                                                                      \
    else                                                                                   \
    {                                                                                      \
      for (size_t i1x = 0; i1x < a.size(); ++i1x)                                          \
      {                                                                                    \
        if (!::xms::gmEqualPointsXY(a[i1x].x, a[i1x].y, b[i1x].x, b[i1x].y, delta))        \
        {                                                                                  \
          std::stringstream msg;                                                           \
          msg << "Incorrect value at position : " << i1x << " Expecting: " << a[i1x]       \
              << " Found: " << b[i1x];                                                     \
          _TS_FAIL(f, l, msg.str().c_str());                                               \
          return;                                                                          \
        }                                                                                  \
      }                                                                                    \
    }                                                                                      \
  \
}
//------------------------------------------------------------------------------
/// \brief Tests if two point vectors are equal within delta and gives useful output.
//------------------------------------------------------------------------------
#define TS_ASSERT_DELTA_VECPT2D(a, b, delta) \
  _TS_ASSERT_DELTA_VECPT2D(__FILE__, __LINE__, a, b, delta)
//------------------------------------------------------------------------------
/// \brief Tests if two point vectors are equal within delta and gives useful output.
/// \deprecated
//------------------------------------------------------------------------------
#define TS_ASSERT_DELTA_VEC_MP2(a, b, delta) \
  _TS_ASSERT_DELTA_VECPT2D(__FILE__, __LINE__, a, b, delta)

//------------------------------------------------------------------------------
/// \brief Used to compare two Pt3ds and give useful output information.
///
//  You'll need to include the following wherever you use this:
//  #include <shared1/geometry/geoms.h>     // for gmEqualPointsXYZ
//  #include <shared1/guido/mpts_streams.h> // for << on Pt3d
//------------------------------------------------------------------------------
#define _TS_ASSERT_DELTA_PT3D(f, l, a, b, delta)                               \
  {                                                                            \
    if (!gmEqualPointsXYZ(a, b, delta))                                        \
    {                                                                          \
      std::stringstream msg;                                                   \
      msg << "(" << a << "), != (" << b << ") within delta (" << delta << ")"; \
      _TS_FAIL(f, l, msg.str().c_str());                                       \
    }                                                                          \
  \
}
//------------------------------------------------------------------------------
/// \brief Tests if two points are equal within delta and gives useful output.
//------------------------------------------------------------------------------
#define _TS_ASSERT_DELTA_PT2D(f, l, a, b, delta)                               \
  {                                                                            \
    if (!gmEqualPointsXY(a, b, delta))                                         \
    {                                                                          \
      std::stringstream msg;                                                   \
      msg << "(" << a << "), != (" << b << ") within delta (" << delta << ")"; \
      _TS_FAIL(f, l, msg.str().c_str());                                       \
    }                                                                          \
  \
}
//------------------------------------------------------------------------------
/// \brief Tests if two points are equal within delta and gives useful output.
//------------------------------------------------------------------------------
#define TS_ASSERT_DELTA_PT3D(a, b, delta) _TS_ASSERT_DELTA_PT3D(__FILE__, __LINE__, a, b, delta)
//------------------------------------------------------------------------------
/// \brief Tests if two points are equal within delta and gives useful output.
//------------------------------------------------------------------------------
#define TS_ASSERT_DELTA_PT2D(a, b, delta) _TS_ASSERT_DELTA_PT2D(__FILE__, __LINE__, a, b, delta)

//------------------------------------------------------------------------------
/// \brief Tests if two files are equal and gives useful output.
//------------------------------------------------------------------------------
#define _TS_ASSERT_TXT_FILES_EQUAL(f, l, a, b) xms::ttTextFilesEqual((f), (l), a, b)
//------------------------------------------------------------------------------
/// \brief Tests if two files are equal and gives useful output.
//------------------------------------------------------------------------------
#define TS_ASSERT_TXT_FILES_EQUAL(a, b) _TS_ASSERT_TXT_FILES_EQUAL(__FILE__, __LINE__, a, b)

//------------------------------------------------------------------------------
/// \brief Tests if two streams are equal and gives useful output.
//------------------------------------------------------------------------------
#define _TS_ASSERT_STREAMS_EQUAL(f, l, a, b) xms::ttStreamsEqual((f), (l), a, b)
//------------------------------------------------------------------------------
/// \brief Tests if two streams are equal and gives useful output.
//------------------------------------------------------------------------------
#define TS_ASSERT_STREAMS_EQUAL(a, b) _TS_ASSERT_STREAMS_EQUAL(__FILE__, __LINE__, a, b)

//------------------------------------------------------------------------------
/// \brief Used to compare to vectors and give useful output information
//------------------------------------------------------------------------------
#define _TS_ASSERT_EQUALS_VEC(f, l, a, b)                                                    \
  {                                                                                          \
    if (a.size() != b.size())                                                                \
    {                                                                                        \
      std::stringstream msg;                                                                 \
      msg << "Incorrect size Expecting size: " << a.size() << " Found size: " << b.size();   \
      _TS_FAIL(f, l, msg.str().c_str());                                                     \
    }                                                                                        \
    else                                                                                     \
    {                                                                                        \
      for (size_t iUnique = 0; iUnique < a.size(); ++iUnique)                                \
      {                                                                                      \
        if (a[iUnique] != b[iUnique])                                                        \
        {                                                                                    \
          std::stringstream msg;                                                             \
          msg << "Incorrect value at position : " << iUnique << " Expecting: " << a[iUnique] \
              << " Found: " << b[iUnique];                                                   \
          _TS_FAIL(f, l, msg.str().c_str());                                                 \
        }                                                                                    \
      }                                                                                      \
    }                                                                                        \
  \
}
//------------------------------------------------------------------------------
/// \brief Used to compare to vectors and give useful output information
//------------------------------------------------------------------------------
#define TS_ASSERT_EQUALS_VEC(a, b) _TS_ASSERT_EQUALS_VEC(__FILE__, __LINE__, a, b)

//------------------------------------------------------------------------------
/// \brief Fails if \a pointer is null.
//------------------------------------------------------------------------------
#define _TS_REQUIRE_NOT_NULL(f, l, pointer)     \
  if (pointer == NULL)                          \
  {                                             \
    _TS_FAIL(f, l, "Unexpected NULL pointer."); \
    return;                                     \
  }
//------------------------------------------------------------------------------
/// \brief Fails if \a pointer is null.
//------------------------------------------------------------------------------
#define TS_REQUIRE_NOT_NULL(pointer) _TS_REQUIRE_NOT_NULL(__FILE__, __LINE__, pointer)

//------------------------------------------------------------------------------
/// \see TS_ASSERT_STACKED_ERRORS
//------------------------------------------------------------------------------
#define _TS_ASSERT_STACKED_ERRORS(f, l, expected) ::xms::ttAssertStackedErrors(f, l, expected)
//------------------------------------------------------------------------------
/// \brief Checks that the stackable XM_LOG has the expected errors.
//------------------------------------------------------------------------------
#define TS_ASSERT_STACKED_ERRORS(expected) _TS_ASSERT_STACKED_ERRORS(__FILE__, __LINE__, expected)
//#endif // ifdef CXX_TEST

//----- Structs / Classes ------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// \class ETestMessagingState
class ETestMessagingState
{
public:
  ETestMessagingState();
  void SetDefault(int a_);
  void ClearDefault();
  int GetDefault();
  void SetSkipping(bool a_);
  bool GetSkipping();
  bool DefaultValWasSet();

private:
  bool m_skippingMessages; ///< Are messages being skipped?
  bool m_defaultSet;       ///< Has a default result value been set?
  int m_defaultRetValue;   ///< Default return value
};

//----- Function prototypes ----------------------------------------------------

void ttByPassMessages(int a_defaultChoice);
bool ttSkippingMessages();
int ttByPassDefault();
void ttClearSkippingMessages();
ETestMessagingState& ttTestMessagingState();
void ttCheckXmLogForEachTest(bool a_check);
bool ttCheckXmLogForEachTest();
//------------------------------------------------------------------------------
/// \brief Tolerance function to match CxxTest::delta for older CxxTest. Could
///        be replaced by CxxTest::doAssertDelta when newer CxxTest is used by
///        XMS builds.
/// \param A: lhs.
/// \param B: rhs.
/// \param tolerance: tolerance
/// \return true if fabs(A - B) <= tolerance
//------------------------------------------------------------------------------
template <class _T, class _U, class _V>
bool ttEqualWithinTolerance(_T A, _U B, _V tolerance)
{
  return (fabs((A) - (B)) <= (tolerance));
} // ttEqualWithinTolerance
//#ifdef CXX_TEST
void ttAssertStackedErrors(const char* a_file, int a_line, const std::string& a_expected);
void ttGetTestFilePaths(const std::string& a_path,
                        const std::string& a_fileBase,
                        const std::string& a_extension,
                        std::string& a_baseFilePath,
                        std::string& a_outFilePath);
void ttTextFilesEqual(const std::string& a_srcFile,
                      unsigned line,
                      const std::string& a_file1,
                      const std::string& a_file2);

bool ttTextFilesEqual(const std::string& a_file1,
                      const std::string& a_file2,
                      std::string& a_message);
void ttStreamsEqual(const std::string& a_src,
                    unsigned int a_line,
                    std::istream& a_strm1,
                    std::istream& a_strm2);
//------------------------------------------------------------------------------
/// \brief Template function returning true or false to help debug tests.
/// \param f: file.
/// \param l: line.
/// \param a: Vector 1.
/// \param b: Vector 2.
/// \param delta: A delta.
/// \return true if a and b are equal within delta.
//------------------------------------------------------------------------------
template <typename T, typename U>
bool ttAssertDeltaVec(const char* f,
                      unsigned l,
                      const std::vector<T>& a,
                      const std::vector<T>& b,
                      U delta)
{
  bool ok = true;
  if (a.size() != b.size())
  {
    std::stringstream msg;
    msg << "Incorrect size (" << a.size() << " != " << b.size() << ")";
    _TS_FAIL(f, l, msg.str().c_str());
    ok = false;
  }
  else
  {
    for (size_t i = 0; i < a.size(); ++i)
    {
      if (!ttEqualWithinTolerance(a.at(i), b.at(i), delta))
      {
        std::stringstream msg;
        msg << "Incorrect value at position (" << i << "). "
            << "(" << a.at(i) << " != " << b.at(i) << ")"
            << " within delta (" << delta << ")";
        _TS_FAIL(f, l, msg.str().c_str());
        ok = false;
      }
    }
  }
  return ok;
} // ttAssertDeltaVec
//------------------------------------------------------------------------------
/// \brief Template function returning true or false to help debug tests.
/// \param f: file.
/// \param l: line.
/// \param a: Vector 1.
/// \param b: Vector 2.
/// \param delta: A delta.
/// \return true if a and b are equal within delta.
//------------------------------------------------------------------------------
template <typename T, typename U>
bool ttAssertDeltaVec2D(const char* f,
                        unsigned l,
                        const std::vector<std::vector<T> >& a,
                        const std::vector<std::vector<T> >& b,
                        U delta)
{
  bool ok = true;
  if (a.size() != b.size())
  {
    std::stringstream msg;
    msg << "Incorrect size (" << a.size() << " != " << b.size() << ")";
    _TS_FAIL(f, l, msg.str().c_str());
    ok = false;
  }
  else
  {
    for (size_t i = 0; i < a.size(); ++i)
    {
      if (a.at(i).size() != b.at(i).size())
      {
        std::stringstream msg;
        msg << "Incorrect size (" << a.at(i).size() << " != " << b.at(i).size() << ")";
        _TS_FAIL(f, l, msg.str().c_str());
        ok = false;
      }
      else
      {
        for (size_t j = 0; j < a.at(i).size(); ++j)
        {
          if (!ttEqualWithinTolerance(a.at(i).at(j), b.at(i).at(j), delta))
          {
            std::stringstream msg;
            msg << "Incorrect value at position (" << i << ")(" << j << "). "
                << "(" << a.at(i).at(j) << " != " << b.at(i).at(j) << ")"
                << " within delta (" << delta << ")";
            _TS_FAIL(f, l, msg.str().c_str());
            ok = false;
          }
        }
      }
    }
  }
  return ok;
} // ttAssertDeltaVec2D
//------------------------------------------------------------------------------
/// \brief Function for TS_ASSERT_EQUALS_AVEC
/// \param a_file: file.
/// \param a_line: line.
/// \param a_expected: An array.
/// \param a_expectedLength: Expected length of the vector.
/// \param a_actual: The vector to check.
//------------------------------------------------------------------------------
template <class T>
void ttAssertEqualsAVec(const char* a_file,
                        int a_line,
                        const T* a_expected,
                        size_t a_expectedLength,
                        const std::vector<T>& a_actual)
{
  std::vector<T> expected(a_expected, a_expected + a_expectedLength);
  _TS_ASSERT_EQUALS_VEC(a_file, a_line, expected, a_actual);
}
//------------------------------------------------------------------------------
/// \brief Template function returning true or false to help debug tests.
/// \param f: file.
/// \param l: line.
/// \param a: Vector 1.
/// \param b: Vector 2.
/// \return true if a and b are equal.
//------------------------------------------------------------------------------
template <typename T>
bool ttAssertEqualsVec2D(const char* f,
                         unsigned l,
                         const std::vector<std::vector<T> >& a,
                         const std::vector<std::vector<T> >& b)
{
  bool ok = true;
  if (a.size() != b.size())
  {
    std::stringstream msg;
    msg << "Incorrect size (" << a.size() << " != " << b.size() << ")";
    _TS_FAIL(f, l, msg.str().c_str());
    ok = false;
  }
  else
  {
    for (size_t i = 0; i < a.size(); ++i)
    {
      if (a.at(i).size() != b.at(i).size())
      {
        std::stringstream msg;
        msg << "Incorrect size (" << a.at(i).size() << " != " << b.at(i).size() << ")";
        _TS_FAIL(f, l, msg.str().c_str());
        ok = false;
      }
      else
      {
        for (size_t j = 0; j < a.at(i).size(); ++j)
        {
          if (a.at(i).at(j) != b.at(i).at(j))
          {
            std::stringstream msg;
            msg << "Incorrect value at position (" << i << ")(" << j << "). "
                << "(" << a.at(i).at(j) << " != " << b.at(i).at(j) << ")";
            _TS_FAIL(f, l, msg.str().c_str());
            ok = false;
          }
        }
      }
    }
  }
  return ok;
} // ttAssertEqualsVec2D
//#endif // ifdef CXX_TEST

} // namespace xms
