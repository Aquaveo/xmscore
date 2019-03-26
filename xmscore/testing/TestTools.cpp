//------------------------------------------------------------------------------
/// \file
/// \brief Functions for running unit or intermediate tests
/// \ingroup core_testing
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 1. Precompiled header

// 2. My own header
#include <xmscore/testing/TestTools.h>

// 3. Standard library headers
#include <fstream>
#include <sstream>

// 4. External library headers
#pragma warning(push)
#pragma warning(disable : 4103) // boost code: alignment change
#include <boost/filesystem.hpp>
#pragma warning(pop)
#include <cxxtest/GlobalFixture.h>
#include <cxxtest/TestSuite.h>

#if BOOST_OS_WINDOWS
#include <Windows.h>
#elif BOOST_OS_LINUX
#include <sys/stat.h>
#include <unistd.h>
#elif BOOST_OS_MACOS
#include <mach-o/dyld.h>
#endif

// 5. Shared code headers
#include <xmscore/misc/XmLog.h>
#include <xmscore/misc/environment.h>
#include <xmscore/points/pt.h>

// 6. Non-shared code headers

namespace xms
{
//----- Constants / Enumerations -----------------------------------------------

//----- Classes / Structs ------------------------------------------------------
namespace
{
class CheckXmLogFixture : public CxxTest::GlobalFixture
{
public:
  bool setUp() override;
  bool tearDown() override;
};

static CheckXmLogFixture fg_checkXmLogFixture;
static bool fg_checkLogForEachTest = false;

//----- Internal functions -----------------------------------------------------

//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
bool CheckXmLogFixture::setUp()
{
  if (fg_checkLogForEachTest)
  {
    xms::ttByPassMessages(1);
    std::string errors = XmLog::Instance().GetAndClearStackStr();
    TS_ASSERT_EQUALS(std::string(), errors);
    return errors == "";
  }
  else
  {
    XmLog::Instance().GetAndClearStackStr();
    return true;
  }
} // CheckXmLogFixture::setUp
//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
bool CheckXmLogFixture::tearDown()
{
  if (fg_checkLogForEachTest)
  {
    xms::ttClearSkippingMessages();
    std::string errors = XmLog::Instance().GetAndClearStackStr();
    TS_ASSERT_EQUALS(std::string(), errors);
    // if expected use TS_ASSERT_STACKED_ERRORS
    return errors == "";
  }
  else
  {
    XmLog::Instance().GetAndClearStackStr();
    return true;
  }
} // CheckXmLogFixture::tearDown

//------------------------------------------------------------------------------
/// \brief See if file exists for testing.
/// \param[in] a_filePath: Path to check for existing file.
/// \return true if found.
//------------------------------------------------------------------------------
bool iFindTestFile(const std::string& a_filePath)
{
  FILE* fp;
  bool found;
#if BOOST_OS_WINDOWS
  if (fopen_s(&fp, a_filePath.c_str(), "r") || fp == nullptr)
    found = false;
  else
    found = true;
#else
  fp = fopen(a_filePath.c_str(), "r");
  found = fp != NULL;
#endif
  if (fp)
    fclose(fp);
  return found;
} // iFindTestFile

} // namespace

//----- Class / Function definitions -------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// \class ETestMessagingState
/// \brief Class to allow running in batch mode without ui elements.
/// Currently only used for testing but it can be used for anything.
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief Constructor
//------------------------------------------------------------------------------
ETestMessagingState::ETestMessagingState()
: m_skippingMessages(false)
, m_defaultSet(false)
, m_defaultRetValue(0)
{
} // ETestMessagingState::ETestMessagingState
//------------------------------------------------------------------------------
/// \brief Set default result value.
/// \param a_: true or false
//------------------------------------------------------------------------------
void ETestMessagingState::SetDefault(int a_)
{
  m_defaultSet = true;
  m_defaultRetValue = a_;
} // ETestMessagingState::SetDefault
//------------------------------------------------------------------------------
/// \brief Change to no default value set.
//------------------------------------------------------------------------------
void ETestMessagingState::ClearDefault()
{
  m_defaultSet = false;
} // ETestMessagingState::ClearDefault
//------------------------------------------------------------------------------
/// \brief Get default value.
/// \return Default value.
//------------------------------------------------------------------------------
int ETestMessagingState::GetDefault()
{
  return m_defaultRetValue;
} // ETestMessagingState::GetDefault
//------------------------------------------------------------------------------
/// \brief Set if skipping messages.
/// \param a_: true or false.
//------------------------------------------------------------------------------
void ETestMessagingState::SetSkipping(bool a_)
{
  m_skippingMessages = a_;
} // ETestMessagingState::SetSkipping
//------------------------------------------------------------------------------
/// \brief Get if skipping messages.
/// \return true if skipping messages.
//------------------------------------------------------------------------------
bool ETestMessagingState::GetSkipping()
{
  return m_skippingMessages;
} // ETestMessagingState::GetSkippin
//------------------------------------------------------------------------------
/// \brief Was default value set (true) or has it been cleared?
/// \return true if default value was set.
//------------------------------------------------------------------------------
bool ETestMessagingState::DefaultValWasSet()
{
  return m_defaultSet;
} // ETestMessagingState::DefaultValWasSet
//------------------------------------------------------------------------------
/// \brief Bypass the ui elements and just set return value
/// \param a_defaultChoice: The option to use automatically when the user
///                         would otherwise be prompted for input.
//------------------------------------------------------------------------------
void ttByPassMessages(int a_defaultChoice)
{
  ttTestMessagingState().SetDefault(a_defaultChoice);
  ttTestMessagingState().SetSkipping(true);
} // ttByPassMessages
//------------------------------------------------------------------------------
/// \brief Has ttByPassMessages been called without calling
///        ttClearSkippingMessages
/// \return true if we are skipping messages.
//------------------------------------------------------------------------------
bool ttSkippingMessages()
{
  return ttTestMessagingState().GetSkipping();
} // ttSkippingMessages
//------------------------------------------------------------------------------
/// \brief Get the default choice when skipping messages.
/// \return The default choice.
//------------------------------------------------------------------------------
int ttByPassDefault()
{
  return ttTestMessagingState().GetDefault();
} // ttByPassDefault
//------------------------------------------------------------------------------
/// \brief Turn off skipping ui elements
//------------------------------------------------------------------------------
void ttClearSkippingMessages()
{
  ttTestMessagingState().SetSkipping(false);
  ttTestMessagingState().ClearDefault();
} // ttClearSkippingMessages
//------------------------------------------------------------------------------
/// \brief Get the batch mode singleton
/// \return Reference to ETestMessagingState
//------------------------------------------------------------------------------
ETestMessagingState& ttTestMessagingState()
{
  static ETestMessagingState m_;
  return m_;
} // ttTestMessagingState
//------------------------------------------------------------------------------
/// \brief Set check of XM_LOG before and after each test.
/// \param a_setting: true to check.
//------------------------------------------------------------------------------
void ttCheckXmLogForEachTest(bool a_setting)
{
  fg_checkLogForEachTest = a_setting;
} // ttSetCheckXmLogForEachTest
//------------------------------------------------------------------------------
/// \brief Turn on check of XM_LOG before and after each test.
/// \return true if currently checking.
//------------------------------------------------------------------------------
bool ttCheckXmLogForEachTest()
{
  return fg_checkLogForEachTest;
} // ttCheckXmLogForEachTest
//------------------------------------------------------------------------------
/// \brief CXX Test assert that the stackable XM_LOG has the expected errors.
/// \param a_file: File.
/// \param a_line: Line.
/// \param a_expected: string
//------------------------------------------------------------------------------
void ttAssertStackedErrors(const char* a_file, int a_line, const std::string& a_expected)
{
  if (ttCheckXmLogForEachTest())
  {
    std::string errors = XmLog::Instance().GetAndClearStackStr();
    _TS_ASSERT_EQUALS(a_file, a_line, a_expected, errors);
  }
} // ttAssertStackedErrors
//------------------------------------------------------------------------------
/// \brief Get testing base and output file using the compiled for architecture.
///        Checks for appended "MacOsX" for Mac OS X and "64" for 64-bit builds.
///        For example with Mac OS 64-bit build looks for test_baseMacOsX.vtu
///        then if not found test_base64.vtu, then if neither found then uses
///        test_base.vtu.
/// \param[in] a_path: Path to the file.
/// \param[in] a_fileBase: File name without extension.
/// \param[in] a_extension: File extension.
/// \param[out] a_baseFilePath: Path to base file.
/// \param[out] a_outFilePath: Path to output file.
//------------------------------------------------------------------------------
void ttGetTestFilePaths(const std::string& a_path,
                        const std::string& a_fileBase,
                        const std::string& a_extension,
                        std::string& a_baseFilePath,
                        std::string& a_outFilePath)
{
  bool foundBase = false;
#if BOOST_OS_MACOS
  // see if there is a different base file for mac os x
  if (!foundBase)
  {
    a_baseFilePath = a_path + a_fileBase + "_baseMacOsX" + a_extension;
    foundBase = iFindTestFile(a_baseFilePath);
  }
#elif BOOST_OS_LINUX
  // see if there is a different base file for linux
  if (!foundBase)
  {
    a_baseFilePath = a_path + a_fileBase + "_baseLinux" + a_extension;
    foundBase = iFindTestFile(a_baseFilePath);
  }
#endif

#if defined(ENV64BIT)
  // see if there is a different base file for 64 bit
  if (!foundBase)
  {
    a_baseFilePath = a_path + a_fileBase + "_base64" + a_extension;
    foundBase = iFindTestFile(a_baseFilePath);
  }
#elif defined(ENV32BIT)
    // ensure either ENV32BIT or ENV64BIT is defined
#else
#error "Must define either ENV32BIT or ENV64BIT"
#endif
  if (!foundBase)
    a_baseFilePath = a_path + a_fileBase + "_base" + a_extension;

  a_outFilePath = a_path + a_fileBase + "_out" + a_extension;
} // ttGetTestFilePaths
//------------------------------------------------------------------------------
/// \brief Returns true if the two files are equal.
/// \param[in] a_file1: Path to first file.
/// \param[in] a_file2: Path to second file.
/// \param[out] a_message: Error message if the files aren't equal.
/// \return true if files are equal, else false.
//------------------------------------------------------------------------------
bool ttTextFilesEqual(const std::string& a_file1,
                      const std::string& a_file2,
                      std::string& a_message)
{
  std::ifstream iOut(a_file1), iBase(a_file2);
  std::string lineOut, lineBase;
  int lineCnt(1);
  if (!iOut.is_open() || !iBase.is_open())
  {
    std::stringstream msg;
    msg << "Unable to open file: "
        << "\n";
    if (!iOut.is_open())
    {
      msg << a_file1;
    }
    else
    {
      msg << a_file2;
    }
    a_message = msg.str();
    return false;
  }
  while (!iOut.eof() && !iBase.eof())
  {
    std::getline(iOut, lineOut);
    std::getline(iBase, lineBase);
    // remove trailing \r character on unix os
    lineOut.erase(lineOut.find_last_not_of("\n\r") + 1);
    lineBase.erase(lineBase.find_last_not_of("\n\r") + 1);
    if (lineOut != lineBase)
    {
      std::stringstream msg;
      msg << "Files different on line " << lineCnt << "."
          << "\n"
          << "File: " << a_file1 << "."
          << "\n"
          << lineOut << "\n"
          << "File: " << a_file2 << "."
          << "\n"
          << lineBase << "\n";
      a_message = msg.str();
      return false;
    }
    lineCnt++;
  }
  return true;
} // ttTextFilesEqual
//----- OVERLOAD ---------------------------------------------------------------
/// \brief Returns true if the two files are equal.
/// \param[in] a_srcFile: Source code file where this is called from.
/// \param[in] a_line: Line in source code file where this is called from.
/// \param[in] a_file1: Path to first file.
/// \param[in] a_file2: Path to second file.
//----- OVERLOAD ---------------------------------------------------------------
void ttTextFilesEqual(const std::string& a_srcFile,
                      unsigned a_line,
                      const std::string& a_file1,
                      const std::string& a_file2)
{
  std::string msg;
  if (!ttTextFilesEqual(a_file1, a_file2, msg))
    _TS_FAIL(a_srcFile.c_str(), a_line, msg.c_str());
} // ttTextFilesEqual
//------------------------------------------------------------------------------
/// \brief Returns true if the two streams are equal.
/// \param[in] a_src: Source code file where this is called from.
/// \param[in] a_line: Line in source code file where this is called from.
/// \param[in] a_strm1: First stream.
/// \param[in] a_strm2: Second stream.
//------------------------------------------------------------------------------
void ttStreamsEqual(const std::string& a_src,
                    unsigned int a_line,
                    std::istream& a_strm1,
                    std::istream& a_strm2)
{
  std::string line1, line2;
  unsigned int line_count(1);

  // clear the flags and rewind the streams
  a_strm1.clear();
  a_strm2.clear();

  a_strm1.seekg(0);
  a_strm2.seekg(0);

  while (!a_strm1.eof() && !a_strm2.eof())
  {
    std::getline(a_strm1, line1);
    std::getline(a_strm2, line2);

    if (line1 != line2)
    {
      std::stringstream msg;

      msg << "Streams different on line " << line_count << ".\n";
      msg << "Stream1:  \"" << line1 << "\"\n";
      msg << "Stream2:  \"" << line2 << "\"\n";

      _TS_FAIL(a_src.c_str(), a_line, msg.str().c_str());
    }

    ++line_count;
  }

  if ((a_strm1.eof() && !a_strm2.eof()) || (!a_strm1.eof() && a_strm2.eof()))
  {
    _TS_FAIL(a_src.c_str(), a_line, "Streams of different lengths");
  }
} // ttStreamsEqual
//------------------------------------------------------------------------------
/// \brief  Returns true if the points are equal to within tolerance.
/// \param a_pt1: Point 1.
/// \param a_pt2: Point 2.
/// \param a_tolerance: tolerance.
/// \return true if equal within tolerance.
//------------------------------------------------------------------------------
bool ttEqualPointsXYZ(const Pt3d& a_pt1, const Pt3d& a_pt2, double a_tolerance)
{
  return ttEqualPointsXYZ(a_pt1.x, a_pt1.y, a_pt1.z, a_pt2.x, a_pt2.y, a_pt2.z, a_tolerance);
} // ttEqualPointsXYZ
//------------------------------------------------------------------------------
/// \brief  Returns true if the points are equal to within tolerance.
/// \param a_x1: x of point 1.
/// \param a_y1: y of point 1.
/// \param a_z1: z of point 1.
/// \param a_x2: x of point 2.
/// \param a_y2: y of point 2.
/// \param a_z2: z of point 2.
/// \param a_tolerance: tolerance.
/// \return true if equal.
//------------------------------------------------------------------------------
bool ttEqualPointsXYZ(double a_x1,
                      double a_y1,
                      double a_z1,
                      double a_x2,
                      double a_y2,
                      double a_z2,
                      double a_tolerance)
{
  if ((fabs(a_x1 - a_x2) <= a_tolerance) && (fabs(a_y1 - a_y2) <= a_tolerance) &&
      (fabs(a_z1 - a_z2) <= a_tolerance))
    return true;
  return false;
} // ttEqualPointsXYZ
//------------------------------------------------------------------------------
/// \brief  Returns true if the points are equal to within tolerance.
/// \param a_x1: x of point 1.
/// \param a_y1: y of point 1.
/// \param a_x2: x of point 2.
/// \param a_y2: y of point 2.
/// \param a_tolerance: a_tolerance.
/// \return true if equal.
//------------------------------------------------------------------------------
bool ttEqualPointsXY(double a_x1, double a_y1, double a_x2, double a_y2, double a_tolerance)
{
  double dx = fabs(a_x1 - a_x2);
  double dy = fabs(a_y1 - a_y2);
  if (dx > a_tolerance || dy > a_tolerance)
    return false;
  else if (sqrt(dx * dx + dy * dy) <= a_tolerance)
    return true;
  else
    return false;
} // ttEqualPointsXY
//------------------------------------------------------------------------------
/// \overload
/// \param a_pt1: Point 1.
/// \param a_pt2: Point 2.
/// \param a_tolerance: tolerance.
/// \return true if equal within tolerance.
//------------------------------------------------------------------------------
bool ttEqualPointsXY(const Pt2d& a_pt1, const Pt2d& a_pt2, double a_tolerance)
{
  return ttEqualPointsXY(a_pt1.x, a_pt1.y, a_pt2.x, a_pt2.y, a_tolerance);
} // ttEqualPointsXY
//------------------------------------------------------------------------------
/// \overload
/// \param a_pt1: Point 1.
/// \param a_pt2: Point 2.
/// \param a_tolerance: tolerance.
/// \return true if equal within tolerance.
//------------------------------------------------------------------------------
bool ttEqualPointsXY(const Pt3d& a_pt1, const Pt3d& a_pt2, double a_tolerance)
{
  return ttEqualPointsXY(a_pt1.x, a_pt1.y, a_pt2.x, a_pt2.y, a_tolerance);
} // ttEqualPointsXY

} // namespace xms
