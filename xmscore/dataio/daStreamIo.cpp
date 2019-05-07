//------------------------------------------------------------------------------
/// \file
/// \ingroup dataio
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 1. Precompiled header

// 2. My header
#include <xmscore/dataio/daStreamIo.h>

// 3. Standard Library Headers
#include <fstream>
#include <regex>
#include <sstream>

// 4. External Library Headers
#include <boost/unordered_map.hpp>

// 5. Shared Headers
#include <xmscore/misc/StringUtil.h>
#include <xmscore/misc/XmError.h>
#include <xmscore/misc/XmLog.h>

//----- Forward declarations ---------------------------------------------------

//----- External globals -------------------------------------------------------

//----- Namespace declaration --------------------------------------------------

namespace xms
{
//----- Constants / Enumerations -----------------------------------------------

//----- Classes / Structs ------------------------------------------------------

//----- Class / Function definitions -------------------------------------------

namespace
{
//------------------------------------------------------------------------------
/// \brief Read line of name (beginning of line) followed with up to 3 expected values.
/// \param a_outStream The stream to write too.
/// \param a_prefix The string to expect before the values.
/// \param a_val1 Optional first value.
/// \param a_val2 Optional second value.
/// \param a_val3 Optional third value.
/// \return true if name was found and all expected values.
//------------------------------------------------------------------------------
template <typename _T1 = int, typename _T2 = int, typename _T3 = int>
bool iReadLine(std::istream& a_inStream,
               const std::string& a_prefix,
               _T1* a_val1 = nullptr,
               _T2* a_val2 = nullptr,
               _T3* a_val3 = nullptr)
{
  // assert that a_prefix is entire line only if all a_val are null
  XM_ASSERT((!a_val1 && !a_val2 && !a_val3) ||
            !std::regex_match(a_prefix, std::regex("[^ \t]+[ \t]+[^ \t]+")));
  std::string line;
  if (!daReadLine(a_inStream, line))
    return false;
  for (int ii = 0; ii < a_prefix.size(); ++ii)
  {
    if (a_prefix[ii] != line[ii])
      return false;
  }

  std::string afterName = line.substr(a_prefix.size());
  std::stringstream ssline(afterName); // remainder of line
  if (a_val1)
  {
    ssline >> *a_val1;
    if (ssline.bad())
      return false;
  }
  if (a_val2)
  {
    ssline >> *a_val2;
    if (ssline.bad())
      return false;
  }
  if (a_val3)
  {
    ssline >> *a_val3;
    if (ssline.bad())
      return false;
  }
  return true;
} // iReadLine
//------------------------------------------------------------------------------
/// \brief Read a line into a std::stringstream.
/// \param a_inStream The stream to read from.
/// \param a_name The expected name before the value.
/// \param a_ss The std::stringstream to write to.
/// \return True on success.
//------------------------------------------------------------------------------
bool iReadLineToSStream(std::istream& a_inStream, const char* a_name, std::stringstream& a_ss)
{
  std::string line;
  if (!daReadLine(a_inStream, line))
    return false;

  auto position = line.find(a_name);
  if (position == std::string::npos)
    return false;
  else
  {
    for (size_t i = 0; i < position; ++i)
    {
      if (!isspace(line[i]))
        return false;
    }
  }

  a_ss.clear();
  std::replace(line.begin(), line.end(), ',', ' ');
  a_ss.str(line.substr(position));
  return !a_ss.fail();
} // iReadLineToSStream
//------------------------------------------------------------------------------
/// \brief Read a single value from a line.
/// \param a_inStream The stream to read from.
/// \param a_val The value to read.
/// \return True on success.
//------------------------------------------------------------------------------
template <typename _T>
bool iReadLineValue(std::istream& a_inStream, _T& a_val)
{
  std::string line;
  if (!daReadLine(a_inStream, line))
    return false;
  std::stringstream ss;
  ss.str(line);
  ss >> a_val;
  return !ss.fail();
} // iReadLineValue
//------------------------------------------------------------------------------
/// \brief Read named vector of values from multiple lines.
/// \param a_inStream The stream to read from.
/// \param a_name The expected name before the value.
/// \param a_vec The vector of values.
/// \return True on success.
//------------------------------------------------------------------------------
template <typename _T>
bool iReadVector(std::istream& a_inStream, const char* a_name, std::vector<_T>& a_vec)
{
  a_vec.clear();
  int size;
  if (!daReadIntLine(a_inStream, a_name, size))
    return false;
  for (int ii = 0; ii < size; ++ii)
  {
    _T val;
    if (!iReadLineValue(a_inStream, val))
      return false;
    a_vec.push_back(val);
  }
  return true;
} // iReadVector
//------------------------------------------------------------------------------
/// \brief Read a named data value from a line.
/// \param a_inStream The stream to read from.
/// \param a_name The expected name before the value.
/// \param a_d1 The data value.
/// \return True on success.
//------------------------------------------------------------------------------
template <typename _T>
bool iReadValue(std::istream& a_inStream, const char* a_name, _T& a_d1)
{
  std::stringstream ss;
  if (!iReadLineToSStream(a_inStream, a_name, ss))
    return false;
  std::string name;
  ss >> name;
  ss >> a_d1;
  return !ss.fail();
} // iReadValue
//------------------------------------------------------------------------------
/// \brief Read a named triplet of data values from a line.
/// \param a_inStream The stream to read from.
/// \param a_name The expected name before the value.
/// \param d1 The first value.
/// \param d2 The second value.
/// \param d3 The third value.
/// \return True on success.
//------------------------------------------------------------------------------
template <typename _T>
bool iRead3Values(std::istream& a_inStream, const char* a_name, _T& d1, _T& d2, _T& d3)
{
  std::stringstream ss;
  if (!iReadLineToSStream(a_inStream, a_name, ss))
    return false;
  std::string name;
  ss >> name;
  ss >> d1;
  ss >> d2;
  ss >> d3;
  return !ss.fail();
} // iRead3Values
//------------------------------------------------------------------------------
/// \brief Read a named pair of data values from a line.
/// \param a_inStream The stream to read from.
/// \param a_name The expected name before the value.
/// \param d1 The first value.
/// \param d2 The second value.
/// \return True on success.
//------------------------------------------------------------------------------
template <typename _T>
bool iRead2Values(std::istream& a_inStream, const char* a_name, _T& d1, _T& d2)
{
  std::stringstream ss;
  if (!iReadLineToSStream(a_inStream, a_name, ss))
    return false;
  std::string name;
  ss >> name;
  ss >> d1;
  ss >> d2;
  return !ss.fail();
} // iRead2Values
namespace
{
//------------------------------------------------------------------------------
/// \brief Write name followed with up to 3 optional values each preceded by a space,
///        and a new line after the last value.
/// \param a_outStream The stream to write too.
/// \param a_name The name to be written before the value.
/// \param a_val1 The optional first value.
/// \param a_val2 The optional second value.
/// \param a_val3 The optional third value.
//------------------------------------------------------------------------------
template <typename _T1 = int, typename _T2 = int, typename _T3 = int>
void iWriteLine(std::ostream& a_outStream,
                const std::string& a_name,
                const _T1* a_val1 = nullptr,
                const _T2* a_val2 = nullptr,
                const _T3* a_val3 = nullptr)
{
  // assert that a_name is multiple words only if all a_val are null
  XM_ASSERT((!a_val1 && !a_val2 && !a_val3) ||
            !std::regex_match(a_name, std::regex("[^ \t]+[ \t]+[^ \t]+")));
  a_outStream << a_name;
  if (a_val1)
    a_outStream << " " << *a_val1;
  if (a_val2)
    a_outStream << " " << *a_val2;
  if (a_val3)
    a_outStream << " " << *a_val3;
  a_outStream << "\n";
} // iWriteLine
//------------------------------------------------------------------------------
/// \brief Write a named vector of values to multiple lines.
/// \param a_outStream The stream to write too.
/// \param a_name The name to be written before the value.
/// \param a_vec The vector of values.
//------------------------------------------------------------------------------
template <typename _T>
void iWriteVec(std::ostream& a_outStream, const char* a_name, const _T& a_vec)
{
  size_t size = a_vec.size();
  iWriteLine(a_outStream, a_name, &size);
  for (auto val : a_vec)
  {
    std::string sval(STRstd(val));
    iWriteLine(a_outStream, " ", &sval); // name is an indentation of spaces
  }
}
} // namespace

} // namespace

//------------------------------------------------------------------------------
/// \brief Read a line that begins with a name.
/// \param a_inStream The stream to read from.
/// \param a_name The expected name before the value.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool daReadNamedLine(std::istream& a_inStream, const char* a_name)
{
  std::stringstream ss;
  return iReadLineToSStream(a_inStream, a_name, ss);
} // daReadNamedLine
//------------------------------------------------------------------------------
/// \brief Read a line from a stream with the following line endings: CR LF, LF,
/// CR, or none.
/// \param a_inStream The stream to read from.
/// \param a_line The line that was read.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool daReadLine(std::istream& a_inStream, std::string& a_line)
{
  a_line.clear();

  // The characters in the stream are read one-by-one using a std::streambuf.
  // That is faster than reading them one-by-one using the std::istream.
  // Code that uses streambuf this way must be guarded by a sentry object.
  // The sentry object performs various tasks,
  // such as thread synchronization and updating the stream state.

  std::istream::sentry se(a_inStream, true);
  std::streambuf* sb = a_inStream.rdbuf();

  for(;;)
  {
    int c = sb->sbumpc();
    if (c == '\n')
    {
      return !!a_inStream;
    }

    if (c == '\r')
    {
      if (sb->sgetc() == '\n')
        sb->sbumpc();
      return !!a_inStream;
    }

    if (c == std::streambuf::traits_type::eof())
    {
      // Also handle the case when the last line has no line ending
      if (a_line.empty())
        a_inStream.setstate(std::ios::eofbit);
      return !!a_inStream;
    }

    a_line += (char)c;
  }

  return true;
} // daReadLine
//------------------------------------------------------------------------------
/// \brief Read a named integer value from a line.
/// \param a_inStream The stream to read from.
/// \param a_name The expected name before the value.
/// \param a_val The integer value.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool daReadIntLine(std::istream& a_inStream, const char* a_name, int& a_val)
{
  return iReadValue(a_inStream, a_name, a_val);
} // daReadIntLine
//------------------------------------------------------------------------------
/// \brief Read an integer value from a string. Return the remaining string.
/// \param a_line The string to read from. Returns the remaining string.
/// \param a_val The value to read.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool daReadIntFromLine(std::string& a_line, int& a_val)
{
  std::istringstream inStream(a_line);
  inStream >> a_val;
  if (inStream.fail())
    return false;
  size_t position = inStream.tellg();
  if (position != std::string::npos)
    a_line = inStream.str().substr(position);
  else
    a_line = "";
  return !inStream.fail();
} // daReadIntFromLine
//------------------------------------------------------------------------------
/// \brief Read a named double value from a line.
/// \param a_inStream The stream to read from.
/// \param a_name The expected name before the value.
/// \param a_val The double value.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool daReadDoubleLine(std::istream& a_inStream, const char* a_name, double& a_val)
{
  return iReadValue(a_inStream, a_name, a_val);
} // daReadDoubleLine
//------------------------------------------------------------------------------
/// \brief Read a named string value from a line.
/// \param a_inStream The stream to read from.
/// \param a_name The expected name before the value.
/// \param a_val The string value.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool daReadStringLine(std::istream& a_inStream, const char* a_name, std::string& a_val)
{
  return iReadValue(a_inStream, a_name, a_val);
} // daReadStringLine
//------------------------------------------------------------------------------
/// \brief Read named vector of integers from multiple lines.
/// \param a_inStream The stream to read from.
/// \param a_name The expected name before the value.
/// \param a_vec The vector of integers.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool daReadVecInt(std::istream& a_inStream, const char* a_name, VecInt& a_vec)
{
  return iReadVector(a_inStream, a_name, a_vec);
} // daReadVecInt
//------------------------------------------------------------------------------
/// \brief Read named vector of doubles from multiple lines.
/// \param a_inStream The stream to read from.
/// \param a_name The expected name before the value.
/// \param a_vec The vector of doubles.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool daReadVecDbl(std::istream& a_inStream, const char* a_name, VecDbl& a_vec)
{
  return iReadVector(a_inStream, a_name, a_vec);
} // daReadVecDbl
//------------------------------------------------------------------------------
/// \brief Read named vector of Pt3d from multiple lines.
/// \param a_inStream The stream to read from.
/// \param a_name The expected name before the value.
/// \param a_vec The vector of Pt3d.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool daReadVecPt3d(std::istream& a_inStream, const char* a_name, VecPt3d& a_vec)
{
  int size;
  if (!daReadIntLine(a_inStream, a_name, size))
    return false;

  a_vec.resize(0);
  a_vec.reserve(size);
  for (int i = 0; i < size; ++i)
  {
    Pt3d pt;
    daRead3DoubleLine(a_inStream, "POINT ", pt.x, pt.y, pt.z);
    a_vec.push_back(pt);
  }

  return true;
} // daReadVecPt3d
//------------------------------------------------------------------------------
/// \brief Read a named pair of words from a line.
/// \param a_inStream The stream to read from.
/// \param a_name The expected name before the value.
/// \param a_val1 The first word.
/// \param a_val2 The second word.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool daRead2StringLine(std::istream& a_inStream,
                       const char* a_name,
                       std::string& a_val1,
                       std::string& a_val2)
{
  return iRead2Values(a_inStream, a_name, a_val1, a_val2);
} // daRead2StringLine
//------------------------------------------------------------------------------
/// \brief Read a named triplet of words from a line.
/// \param a_inStream The stream to read from.
/// \param a_name The expected name before the value.
/// \param a_val1 The first word.
/// \param a_val2 The second word.
/// \param a_val3 The third word.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool daRead3StringLine(std::istream& a_inStream,
                       const char* a_name,
                       std::string& a_val1,
                       std::string& a_val2,
                       std::string& a_val3)
{
  return iRead3Values(a_inStream, a_name, a_val1, a_val2, a_val3);
} // daRead3StringLine
//------------------------------------------------------------------------------
/// \brief Read a named triplet of doubles from a line.
/// \param a_inStream The stream to read from.
/// \param a_name The expected name before the value.
/// \param a_val1 The first double.
/// \param a_val2 The second double.
/// \param a_val3 The third double.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool daRead3DoubleLine(std::istream& a_inStream,
                       const char* a_name,
                       double& a_val1,
                       double& a_val2,
                       double& a_val3)
{
  return iRead3Values(a_inStream, a_name, a_val1, a_val2, a_val3);
} // daRead3DoubleLine
//------------------------------------------------------------------------------
/// \brief Write a given line to a stream.
/// \param a_outStream The stream to write too.
/// \param a_name The line of text to be written.
//------------------------------------------------------------------------------
void daWriteNamedLine(std::ostream& a_outStream, const char* a_name)
{
  iWriteLine(a_outStream, a_name);
} // daWriteNamedLine
  //------------------------------------------------------------------------------
  /// \brief Write a given line to a stream.
  /// \param a_outStream The stream to write too.
  /// \param a_line The line of text to be written.
  //------------------------------------------------------------------------------
void daWriteLine(std::ostream& a_outStream, const std::string& a_line)
{
  iWriteLine(a_outStream, a_line);
} // daWriteLine
//------------------------------------------------------------------------------
/// \brief Write a named double line value.
/// \param a_outStream The stream to write too.
/// \param a_name The name to be written before the value.
/// \param a_val The double value to write.
//------------------------------------------------------------------------------
void daWriteDoubleLine(std::ostream& a_outStream, const char* a_name, double a_val)
{
  iWriteLine(a_outStream, a_name, &a_val);
} // daWriteDoubleLine
//------------------------------------------------------------------------------
/// \brief Write a named word line.
/// \param a_outStream The stream to write too.
/// \param a_name The name to be written before the value.
/// \param a_val The word.
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void daWriteStringLine(std::ostream& a_outStream, const char* a_name, const std::string& a_val)
{
  iWriteLine(a_outStream, a_name, &a_val);
} // daWriteStringLine
//------------------------------------------------------------------------------
/// \brief Write a named vector of integers to several lines.
/// \param a_outStream The stream to write too.
/// \param a_name The name to be written before the value.
/// \param a_vec The vector of integers.
//------------------------------------------------------------------------------
void daWriteVecInt(std::ostream& a_outStream, const char* a_name, const VecInt& a_vec)
{
  iWriteVec(a_outStream, a_name, a_vec);
} // daWriteVecInt
//------------------------------------------------------------------------------
/// \brief Write a named pair of words to a line.
/// \param a_outStream The stream to write too.
/// \param a_name The name to be written before the value.
/// \param a_val1 The first word.
/// \param a_val2 The second word.
//------------------------------------------------------------------------------
void daWrite2StringLine(std::ostream& a_outStream,
                        const char* a_name,
                        const std::string& a_val1,
                        const std::string& a_val2)
{
  iWriteLine(a_outStream, a_name, &a_val1, &a_val2);
} // daWrite2StringLine
//------------------------------------------------------------------------------
/// \brief Write a named triplet of words to a line.
/// \param a_outStream The stream to write too.
/// \param a_name The name to be written before the value.
/// \param a_val1 The first word.
/// \param a_val2 The second word.
/// \param a_val3 The third word.
//------------------------------------------------------------------------------
void daWrite3StringLine(std::ostream& a_outStream,
                        const char* a_name,
                        const std::string& a_val1,
                        const std::string& a_val2,
                        const std::string& a_val3)
{
  iWriteLine(a_outStream, a_name, &a_val1, &a_val2, &a_val3);
} // daWrite3StringLine
//------------------------------------------------------------------------------
/// \brief Write a named triplet of doubles to a line.
/// \param a_outStream The stream to write too.
/// \param a_name The name to be written before the value.
/// \param a_val1 The first double.
/// \param a_val2 The second double.
/// \param a_val3 The third double.
//------------------------------------------------------------------------------
void daWrite3DoubleLine(std::ostream& a_outStream,
                        const char* a_name,
                        const double& a_val1,
                        const double& a_val2,
                        const double& a_val3)
{
  iWriteLine(a_outStream, a_name, &a_val1, &a_val2, &a_val3);
} // daWrite3DoubleLine
//------------------------------------------------------------------------------
/// \brief Write a named integer value to a line.
/// \param a_outStream The stream to write too.
/// \param a_name The name to be written before the value.
/// \param a_val The integer value.
//------------------------------------------------------------------------------
void daWriteIntLine(std::ostream& a_outStream, const char* a_name, int a_val)
{
  iWriteLine(a_outStream, a_name, &a_val);
} // daWriteIntLine
//------------------------------------------------------------------------------
/// \brief Write a named vector of doubles to multiple lines.
/// \param a_outStream The stream to write too.
/// \param a_name The name to be written before the value.
/// \param a_vec The vector of doubles.
//------------------------------------------------------------------------------
void daWriteVecDbl(std::ostream& a_outStream, const char* a_name, const VecDbl& a_vec)
{
  iWriteVec(a_outStream, a_name, a_vec);
} // daWriteVecDbl
//------------------------------------------------------------------------------
/// \brief Write a named vector of Pt3d to multiple lines.
/// \param a_outStream The stream to write too.
/// \param a_name The name to be written before the value.
/// \param a_points The vector of Pt3d.
//------------------------------------------------------------------------------
void daWriteVecPt3d(std::ostream& a_outStream, const char* a_name, const VecPt3d& a_points)
{
  // write name and size of vector
  const size_t size = a_points.size();
  iWriteLine(a_outStream, a_name, &size);

  // write each indented point and XYZ (why not remove POINT text?)
  for (auto const point : a_points)
  {
    std::string sx(STRstd(point.x));
    std::string sy(STRstd(point.y));
    std::string sz(STRstd(point.z));
    iWriteLine(a_outStream, "  POINT", &sx, &sy, &sz);
  }
} // daWriteVecPt3d

} // namespace xms

#if CXX_TEST
///////////////////////////////////////////////////////////////////////////////
// TESTS
///////////////////////////////////////////////////////////////////////////////

#include <xmscore/dataio/daStreamIo.t.h>

using namespace xms;

////////////////////////////////////////////////////////////////////////////////
/// \class CoUtilsIoUnitTests
/// \brief Tests for Stream IO utilities.
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief Test daReadNamedLine.
//------------------------------------------------------------------------------
void CoUtilsIoUnitTests::testReadNamedLine()
{
  // test read with CR LF, LF, CR, and no line endings
  std::string lineEndingsInput =
    "Windows Line\r\n"
    "Unix Line\n"
    "Mac Line\r"
    "Last Line";
  std::istringstream inStream(lineEndingsInput);
  TS_ASSERT(daReadNamedLine(inStream, "Windows Line"));
  TS_ASSERT(daReadNamedLine(inStream, "Unix Line"));
  TS_ASSERT(daReadNamedLine(inStream, "Mac Line"));
  TS_ASSERT(daReadNamedLine(inStream, "Last Line"));
} // CoUtilsIoUnitTests::testReadNamedLine
//------------------------------------------------------------------------------
/// \brief Test daWriteLine and daReadLine.
//------------------------------------------------------------------------------
void CoUtilsIoUnitTests::testReadWriteLine()
{
  std::ostringstream ostream;
  daWriteLine(ostream, "daWriteLine version 1.0");
  std::string expected = "daWriteLine version 1.0\n";
  std::string found = ostream.str();
  TS_ASSERT_EQUALS(expected, found);

  std::istringstream istream(ostream.str());
  std::string value;
  daReadLine(istream, value);
  expected = "daWriteLine version 1.0";
  TS_ASSERT_EQUALS(expected, value);

  // test read with CR LF, LF, CR, and no line endings
  std::string lineEndingsInput =
    "Windows Line\r\n"
    "Unix Line\n"
    "Mac Line\r"
    "Last Line";
  std::istringstream endingsIn(lineEndingsInput);
  daReadLine(endingsIn, value);
  TS_ASSERT_EQUALS("Windows Line", value);
  daReadLine(endingsIn, value);
  TS_ASSERT_EQUALS("Unix Line", value);
  daReadLine(endingsIn, value);
  TS_ASSERT_EQUALS("Mac Line", value);
  daReadLine(endingsIn, value);
  TS_ASSERT_EQUALS("Last Line", value);
} // CoUtilsIoUnitTests::testReadWriteLine
//------------------------------------------------------------------------------
/// \brief Test daWriteStringLine and daReadStringLine.
//------------------------------------------------------------------------------
void CoUtilsIoUnitTests::testReadWriteStringLine()
{
  std::ostringstream ostream;
  const char* name = "LINE_NAME";
  std::string expectedValue = "VALUE";
  daWriteStringLine(ostream, name, expectedValue);
  std::string expected = "LINE_NAME VALUE\n";
  std::string found = ostream.str();
  TS_ASSERT_EQUALS(expected, found);

  std::istringstream istream(ostream.str());
  std::string foundValue;
  TS_ASSERT(daReadStringLine(istream, name, foundValue));
  TS_ASSERT_EQUALS(expectedValue, foundValue);
} // CoUtilsIoUnitTests::testReadWriteStringLine
//------------------------------------------------------------------------------
/// \brief Test daWrite2StringLine and daRead2StringLine.
//------------------------------------------------------------------------------
void CoUtilsIoUnitTests::testReadWrite2StringLine()
{
  std::ostringstream ostream;
  const char* name = "LINE_NAME";
  std::string expectedValue1 = "VALUE1";
  std::string expectedValue2 = "VALUE2";
  daWrite2StringLine(ostream, name, expectedValue1, expectedValue2);
  std::string expected = "LINE_NAME VALUE1 VALUE2\n";
  std::string found = ostream.str();
  TS_ASSERT_EQUALS(expected, found);

  std::istringstream istream(ostream.str());
  std::string foundValue1;
  std::string foundValue2;
  TS_ASSERT(daRead2StringLine(istream, name, foundValue1, foundValue2));
  TS_ASSERT_EQUALS(expectedValue1, foundValue1);
  TS_ASSERT_EQUALS(expectedValue2, foundValue2);
} // CoUtilsIoUnitTests::testReadWrite2StringLine
//------------------------------------------------------------------------------
/// \brief Test daWrite3StringLine and daRead3StringLine.
//------------------------------------------------------------------------------
void CoUtilsIoUnitTests::testReadWrite3StringLine()
{
  std::ostringstream ostream;
  const char* name = "LINE_NAME";
  std::string expectedValue1 = "VALUE1";
  std::string expectedValue2 = "VALUE2";
  std::string expectedValue3 = "VALUE3";
  daWrite3StringLine(ostream, name, expectedValue1, expectedValue2, expectedValue3);
  std::string expected = "LINE_NAME VALUE1 VALUE2 VALUE3\n";
  std::string found = ostream.str();
  TS_ASSERT_EQUALS(expected, found);

  std::istringstream istream(ostream.str());
  std::string foundValue1;
  std::string foundValue2;
  std::string foundValue3;
  TS_ASSERT(daRead3StringLine(istream, name, foundValue1, foundValue2, foundValue3));
  TS_ASSERT_EQUALS(expectedValue1, foundValue1);
  TS_ASSERT_EQUALS(expectedValue2, foundValue2);
  TS_ASSERT_EQUALS(expectedValue3, foundValue3);
} // CoUtilsIoUnitTests::testReadWrite3StringLine
//------------------------------------------------------------------------------
/// \brief Test daWReadIntFromLine.
//------------------------------------------------------------------------------
void CoUtilsIoUnitTests::testReadIntFromLine()
{
  std::string line = "1 -1 A 2";
  int intValue;
  TS_ASSERT(daReadIntFromLine(line, intValue));
  TS_ASSERT_EQUALS(1, intValue);
  TS_ASSERT_EQUALS(" -1 A 2", line);

  TS_ASSERT(daReadIntFromLine(line, intValue));
  TS_ASSERT_EQUALS(-1, intValue);
  TS_ASSERT_EQUALS(" A 2", line);

  TS_ASSERT(!daReadIntFromLine(line, intValue));
  TS_ASSERT_EQUALS(" A 2", line);
} // CoUtilsIoUnitTests::testReadIntFromLine
//------------------------------------------------------------------------------
/// \brief Test daWriteIntLine and daReadIntLine.
//------------------------------------------------------------------------------
void CoUtilsIoUnitTests::testReadWriteIntLine()
{
  std::ostringstream ostream;
  const char* name = "LINE_NAME";
  const int expect = 22;
  daWriteIntLine(ostream, name, expect);
  std::string oexpected = "LINE_NAME 22\n";
  std::string ofound = ostream.str();
  TS_ASSERT_EQUALS(oexpected, ofound);

  std::istringstream istream(ostream.str());
  int found;
  TS_ASSERT(daReadIntLine(istream, name, found));
  TS_ASSERT_EQUALS(expect, found);
} // CoUtilsIoUnitTests::testReadWriteIntLine
//------------------------------------------------------------------------------
/// \brief Test daWriteDoubleLine and daReadDoubleLine.
//------------------------------------------------------------------------------
void CoUtilsIoUnitTests::testReadWriteDoubleLine()
{
  std::ostringstream ostream;
  const char* name = "LINE_NAME";
  const double expect = 22.1;
  daWriteDoubleLine(ostream, name, expect);
  std::string oexpected = "LINE_NAME 22.1\n";
  std::string ofound = ostream.str();
  TS_ASSERT_EQUALS(oexpected, ofound);

  std::istringstream istream(ostream.str());
  double found;
  TS_ASSERT(daReadDoubleLine(istream, name, found));
  TS_ASSERT_EQUALS(expect, found);
} // CoUtilsIoUnitTests::testReadWriteDoubleLine
//------------------------------------------------------------------------------
/// \brief Test daWrite3DoubleLine and daRead3DoubleLine.
//------------------------------------------------------------------------------
void CoUtilsIoUnitTests::testReadWrite3DoubleLine()
{
  std::ostringstream ostream;
  const char* name = "LINE_NAME";
  const double expect1 = 22.1;
  const double expect2 = 22.2;
  const double expect3 = 22.3;
  daWrite3DoubleLine(ostream, name, expect1, expect2, expect3);
  std::string oexpected = "LINE_NAME 22.1 22.2 22.3\n";
  std::string ofound = ostream.str();
  TS_ASSERT_EQUALS(oexpected, ofound);

  std::istringstream istream(ostream.str());
  double found1;
  double found2;
  double found3;
  TS_ASSERT(daRead3DoubleLine(istream, name, found1, found2, found3));
  TS_ASSERT_EQUALS(expect1, found1);
  TS_ASSERT_EQUALS(expect2, found2);
  TS_ASSERT_EQUALS(expect3, found3);
} // CoUtilsIoUnitTests::testReadWrite3DoubleLine
//------------------------------------------------------------------------------
/// \brief Test daWriteVecInt and daReadVecInt.
//------------------------------------------------------------------------------
void CoUtilsIoUnitTests::testReadWriteVecInt()
{
  std::ostringstream ostream;
  const char* name = "VECTOR_NAME";
  const VecInt expect = {1, 2, 3};
  daWriteVecInt(ostream, name, expect);
  std::string oexpected =
    "VECTOR_NAME 3\n"
    "  1\n"
    "  2\n"
    "  3\n";
  std::string ofound = ostream.str();
  TS_ASSERT_EQUALS(oexpected, ofound);

  std::istringstream istream(ostream.str());
  VecInt found;
  TS_ASSERT(daReadVecInt(istream, name, found));
  TS_ASSERT_EQUALS(expect, found);
} // CoUtilsIoUnitTests::testReadWriteVecInt
//------------------------------------------------------------------------------
/// \brief Test daWriteVecDbl and daReadVecDbl.
//------------------------------------------------------------------------------
void CoUtilsIoUnitTests::testReadWriteVecDbl()
{
  std::ostringstream ostream;
  const char* name = "VECTOR_NAME";
  const VecDbl expect = {1.1, 2.2, 3.3};
  daWriteVecDbl(ostream, name, expect);
  std::string oexpected =
    "VECTOR_NAME 3\n"
    "  1.1\n"
    "  2.2\n"
    "  3.3\n";
  std::string ofound = ostream.str();
  TS_ASSERT_EQUALS(oexpected, ofound);

  std::istringstream istream(ostream.str());
  VecDbl found;
  TS_ASSERT(daReadVecDbl(istream, name, found));
  TS_ASSERT_EQUALS(expect, found);
} // CoUtilsIoUnitTests::testReadWriteVecDbl
//------------------------------------------------------------------------------
/// \brief Test daWriteVecPt3d and daReadVecPt3d.
//------------------------------------------------------------------------------
void CoUtilsIoUnitTests::testReadWriteVecPt3d()
{
  std::ostringstream ostream;
  const char* name = "VECTOR_NAME";
  const VecPt3d expect = {
    {1.1, 1.2, 1.3},
    {2.1, 2.2, 2.3},
  };
  daWriteVecPt3d(ostream, name, expect);
  std::string oexpected =
    "VECTOR_NAME 2\n"
    "  POINT 1.1 1.2 1.3\n"
    "  POINT 2.1 2.2 2.3\n";
  std::string ofound = ostream.str();
  TS_ASSERT_EQUALS(oexpected, ofound);

  std::istringstream istream(ostream.str());
  VecPt3d found;
  TS_ASSERT(daReadVecPt3d(istream, name, found));
  TS_ASSERT_EQUALS(expect, found);
} // CoUtilsIoUnitTests::testReadWriteVecPt3d

#endif
