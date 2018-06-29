//------------------------------------------------------------------------------
/// \file
/// \ingroup xmscore_misc
/// \copyright (C) Copyright Aquaveo 2018. Distributed under the xmsng
///  Software License, Version 1.0. (See accompanying file
///  LICENSE_1_0.txt or copy at http://www.aquaveo.com/xmsng/LICENSE_1_0.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 1. Precompiled header

// 2. My header
#include <xmscore/misc/StringUtil.h>

// 3. Standard Library Headers
#include <cctype>
#include <cstdio>
#include <float.h>

// 4. External Library Headers
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>

// 5. Shared Headers
#include <xmscore/math/math.h>
#include <xmscore/misc/XmError.h>
#include <regex>

//#pragma warning(disable:4996) // 'strcpy': This function or variable may be unsafe.

// 6. Non-shared Headers

namespace xms
{
////////////////////////////////////////////////////////////////////////////////
/// \class StTemp2DigitExponents
/// \brief When constructed std::cout will temporarily output 2-digit exponents
///        for floating point numbers. Destructor will revert back.
///        Should be able to remove this upon changing to Visual Studio 2015.
//------------------------------------------------------------------------------
/// \brief Temporarily output 2-digit exponents for floating point numbers to
///        match C++ standard. Should be able to remove all instances of this
///        class upon moving to Visual Studio 2015.
//------------------------------------------------------------------------------
StTemp2DigitExponents::StTemp2DigitExponents()
: m_oldOutputFormat(0)
{
#if defined(_MSC_VER) && _MSC_VER < 1900
  m_oldOutputFormat = _get_output_format();
  _set_output_format(_TWO_DIGIT_EXPONENT);
#elif defined(_MSC_VER) && _MSC_VER >= 1900
#pragma message("StTemp2DigitExponents class can be removed.")
#endif
} // StTemp2DigitExponents::StTemp2DigitExponents
//------------------------------------------------------------------------------
/// \brief Revert back to 3-digit exponents for pre-Visual Studio 2015.
//------------------------------------------------------------------------------
StTemp2DigitExponents::~StTemp2DigitExponents()
{
#if defined(_MSC_VER) && _MSC_VER < 1900
  _set_output_format(m_oldOutputFormat);
#endif
} // StTemp2DigitExponents::~StTemp2DigitExponents

//------------------------------------------------------------------------------
/// \brief Counts the number of a given character in a string.
/// \param[in] str: The string.
/// \param[in] c:   The char.
/// \return The count.
//------------------------------------------------------------------------------
unsigned int stCountChar(const std::string& str, char c)
{
  unsigned int count = 0;
  std::string::size_type size = str.size();

  for (std::string::size_type pos = 0; pos < size; ++pos)
  {
    if (str[pos] == c)
    {
      count++;
    }
  }

  return count;
} // stCountChar
//------------------------------------------------------------------------------
/// \brief Determines whether the given string is a valid number.
/// \param[in] str: The string.
/// \return true or false.
//------------------------------------------------------------------------------
bool stNumeric(const std::string& str)
{
  std::string copy(stTrimCopy(str));
  std::stringstream ss(copy);
  double temp;

  ss >> temp;

  return (!ss.fail() && ss.eof());
} // stNumeric
//------------------------------------------------------------------------------
/// \brief Determines whether the given string is a number in scientific
///        notation.
/// \param[in] str:       The string to modify.
/// \param check_numeric: Pass false if you are sure your string is a number.
/// \return true or false.
//------------------------------------------------------------------------------
bool stScientificNotation(const std::string& str, bool check_numeric /*= true*/)
{
  if (check_numeric && !stNumeric(str))
  {
    return false;
  }

  return (str.find_first_of("eE") != std::string::npos);
} // stScientificNotation
//------------------------------------------------------------------------------
/// \brief Replaces the Windows Latin-1 extended ASCII characters with standard
///        ASCII and vice-versa.
/// \param[in,out] str:         The string to modify.
/// \param[in] to_extended: true to add extended ASCII, false to remove it
//------------------------------------------------------------------------------
void stChangeExtendedAscii(std::string& str, bool to_extended)
{
  const char* look_up[] = {// extended ASCII always goes first
                           // must be in pairs
                           "\xb2", "^2",   // superscript two - squared
                           "\xb3", "^3",   // superscript three - cubed
                           "\xb0", "deg_", // degree sign
                                           // this needs to be last and have both NULLs
                           nullptr, nullptr};

  unsigned int src = to_extended ? 1 : 0;
  unsigned int dst = to_extended ? 0 : 1;

  for (; look_up[src] != nullptr; src += 2, dst += 2)
  {
    stReplace(str, look_up[src], look_up[dst]);
  }
} // stChangeExtendedAscii
//------------------------------------------------------------------------------
/// \brief Breaks the string into a vector of strings based on the delimiter
/// \param[in] source:      The string.
/// \param[in] a_delimiter: The delimiter. The whole string is THE delimiter.
/// \return Vector of strings.
///
/// a_delimiter is not a list of delimiters, it is THE delimiter. Use stSplit
/// method if you need to specify multiple different delimiter characters or
/// need to handle multiple adjacent delimiters (ie. "1   2      3")
//------------------------------------------------------------------------------
VecStr stExplode(const std::string& source, const std::string& a_delimiter)
{
  std::string::size_type pos = source.find(a_delimiter);
  std::vector<std::string> exploded;

  if (pos != std::string::npos)
  {
    size_t delim_len = a_delimiter.size();

    exploded.push_back(source.substr(0, pos));

    while (pos != std::string::npos)
    {
      std::string::size_type pos2 = source.find(a_delimiter, pos + 1);
      std::string::size_type length = pos2 - pos - delim_len;

      if (pos2 == std::string::npos)
      {
        length = std::string::npos;
      }

      exploded.push_back(source.substr(pos + delim_len, length));

      pos = pos2;
    }
  }
  else
  {
    if (!source.empty())
    {
      exploded.push_back(source);
    }
  }

  return exploded;
} // stExplode
//------------------------------------------------------------------------------
/// \brief Breaks string into vector of strings based on one or more delimiters.
/// \param[in] a_source:        The string to be split.
/// \param[in] a_delimiterList: String where each character is a delimeter.
/// \param[in] a_delimiterCompressOn: If true, consecutive delimeters are
///                                   treated as one.
/// \return A vector of strings.
/// \see http://stackoverflow.com/questions/236129/split-a-string-in-c
//------------------------------------------------------------------------------
VecStr stSplit(const std::string& a_source,
               const std::string& a_delimiterList /*=wspace*/,
               bool a_delimiterCompressOn /*true*/)
{
  std::string trimmed = stTrimCopy(a_source, a_delimiterList);
  VecStr elems;
  if (a_delimiterCompressOn)
  {
    boost::split(elems, trimmed, boost::is_any_of(a_delimiterList), boost::token_compress_on);
  }
  else
  {
    // Unfortunately, boost::token_compress_off doesn't do the trick because
    // it still compresses the leading and trailing delimiters. The following
    // code works. I don't know how fast it is.
    std::vector<char> temp(a_source.size());
    int end = 0;
    for (size_t i = 0; i < a_source.size(); ++i)
    {
      if (a_delimiterList.find(a_source[i]) != std::string::npos)
      {
        elems.push_back(std::string(&temp[0], end));
        end = 0;
      }
      else
      {
        temp[end++] = a_source[i];
      }
    }
    if (a_delimiterList.find(a_source.back()) != std::string::npos)
    {
      elems.push_back("");
    }
  }
  return elems;
} // stSplit
//------------------------------------------------------------------------------
/// \brief Joins the vector, inserting delim between each item.
/// \param[in] source: A vector of strings.
/// \param[in] delim: The delimiter to be inserted between each string.
/// \return A string.
//------------------------------------------------------------------------------
std::string stImplode(const std::vector<std::string>& source, const std::string& delim)
{
  std::string imploded;

  if (!source.empty())
  {
    size_t size = source.size() - 1;
    for (size_t i = 0; i < size; ++i)
    {
      imploded += source[i];
      imploded += delim;
    }

    imploded += source[size];
  }

  return imploded;
} // stImplode
//------------------------------------------------------------------------------
/// \brief Iterates through a vec of strings and looks for the string.
///        Case sensitive.
/// \param[in] a_container: Vec of strings to iterate through.
/// \param[in] str: Element we're searching for.
/// \return Index of the position of the element. If not found it returns -1.
//------------------------------------------------------------------------------
int stIndexOfElem(const VecStr& a_container, const std::string& str)
{
  int loc = 0;
  for (int i = 0; i < static_cast<int>(a_container.size()); i++)
  {
    if (a_container[i] == str)
    {
      loc = i;
      return loc;
    }
  }
  loc = -1;
  return loc;
} // indexOfElem
//------------------------------------------------------------------------------
/// \brief Trims the white space from a string. This involves creating a copy
///        of the string (twice I believe), so don't call this unless you
///        really don't want the original string modified.
/// \param[in,out] str:   The string.
/// \param[in]     delim: All the characters you want to be trimmed.
/// \return The new string.
//------------------------------------------------------------------------------
std::string stTrimCopy(const std::string& str, const std::string& delim /*= wspace*/)
{
  std::string temp(str);

  return stTrim(temp, delim);
} // stTrimCopy
//------------------------------------------------------------------------------
/// \brief Trims the leading delim characters from a string.
/// \param[in,out] str:   The string to be modified.
/// \param[in]     delim: All the characters you want to be trimmed.
/// \return A reference to str.
//------------------------------------------------------------------------------
std::string& stTrimLeft(std::string& str, const std::string& delim /*= wspace*/)
{
  std::string::size_type pos = str.find_first_not_of(delim);

  if (pos != std::string::npos)
  {
    str.erase(0, pos);
  }
  else
  {
    str.clear();
  }

  return str;
} // stTrimLeft
//------------------------------------------------------------------------------
/// \brief Trims the trailing delim characters from a string.
/// \param[in,out] str:   The string to be modified.
/// \param[in]     delim: All the characters you want to be trimmed.
/// \return A reference to str.
//------------------------------------------------------------------------------
std::string& stTrimRight(std::string& str, const std::string& delim /*= wspace*/)
{
  std::string::size_type pos = str.find_last_not_of(delim);

  if (pos != std::string::npos)
  {
    str.erase(pos + 1);
  }
  else
  {
    str.clear();
  }

  return str;
} // stTrimRight
//------------------------------------------------------------------------------
/// \brief Trim the leading and trailing delim characters from a string.
/// \param[in,out] str:   The string to be modified.
/// \param[in]     delim: All the characters you want to be trimmed.
/// \return A reference to str.
//------------------------------------------------------------------------------
std::string& stTrim(std::string& str, const std::string& delim /*= wspace*/)
{
  stTrimLeft(str, delim);
  return stTrimRight(str, delim);
} // stTrim
//------------------------------------------------------------------------------
/// \brief Returns a copy of str with every instance of source replaced with
///        dest.
/// \param[in,out] str:    The string.
/// \param[in]     source: The character to be replaced.
/// \param[in]     dest:   The character replacing source.
/// \return The new string.
//------------------------------------------------------------------------------
std::string stReplaceCopy(const std::string& str, char source, char dest)
{
  std::string replaced(str);
  stReplace(replaced, source, dest);
  return replaced;
} // stReplaceCopy
//------------------------------------------------------------------------------
/// \brief Returns a copy of str with every instance of source replaced with
///        dest.
/// \param[in,out] str:    The string.
/// \param[in]     source: The sub string to be replaced.
/// \param[in]     dest:   The sub string replacing source.
/// \return The new string.
//------------------------------------------------------------------------------
std::string stReplaceCopy(const std::string& str,
                          const std::string& source,
                          const std::string& dest)
{
  std::string replaced(str);
  stReplace(replaced, source, dest);
  return replaced;
} // stReplaceCopy
//------------------------------------------------------------------------------
/// \brief Returns a reference to str, and replaces every instance of source
///        replaced with dest.
/// \param[in,out] str:    The string to be modified.
/// \param[in]     source: The character to be replaced.
/// \param[in]     dest:   The character replacing source.
/// \return Reference to str.
//------------------------------------------------------------------------------
std::string& stReplace(std::string& str, char source, char dest)
{
  if (source == dest)
  {
    return str;
  }

  size_t pos = str.find(source);

  while (pos != std::string::npos)
  {
    str[pos] = dest;
    pos = str.find(source, pos + 1);
  }

  return str;
} // stReplace
//------------------------------------------------------------------------------
/// \brief Returns a reference to str, and replaces every instance of source
///        replaced with dest.
/// \param[in,out] str:    The string to be modified.
/// \param[in]     source: The sub string to be replaced.
/// \param[in]     dest:   The sub string replacing source.
/// \return Reference to str.
//------------------------------------------------------------------------------
std::string& stReplace(std::string& str, const std::string& source, const std::string& dest)
{
  if (source == dest)
  {
    return str;
  }

  std::string::size_type pos = str.find(source);
  std::string::size_type source_len = source.size();
  std::string::size_type dest_len = dest.size();

  while (pos != std::string::npos)
  {
    str.erase(pos, source_len);
    str.insert(pos, dest);
    pos = str.find(source, pos + dest_len);
  }

  return str;
} // stReplace
//------------------------------------------------------------------------------
/// \brief Returns a copy of str with all instances of char source removed.
/// \param[in,out] str:    The string.
/// \param[in]     source: The character to be removed.
/// \return The new string.
/// \see http://stackoverflow.com/questions/20326356/
//------------------------------------------------------------------------------
std::string stRemoveCopy(const std::string& str, char source)
{
  std::string copy(str);
  return stRemove(copy, source);
} // stRemoveCopy
//------------------------------------------------------------------------------
/// \brief Removes all instances of char source from str and returns a
///        reference to str.
/// \param[in,out] str:    The string to be modified.
/// \param[in]     source: The character to be removed.
/// \return A reference to str.
//------------------------------------------------------------------------------
std::string& stRemove(std::string& str, char source)
{
  str.erase(std::remove(str.begin(), str.end(), source), str.end());
  return str;
} // stRemove
//------------------------------------------------------------------------------
/// \brief Returns a new string that is str with all characters lowercase.
/// \param str: The string.
/// \return The new string.
//------------------------------------------------------------------------------
std::string stToLowerCopy(const std::string& str)
{
  std::string copy(str);
  return stToLower(copy);
} // stToLowerCopy
//------------------------------------------------------------------------------
/// \brief Modifies str to be all lowercase.
/// \param[in,out] str: String to be modified.
/// \return A reference to str.
//------------------------------------------------------------------------------
std::string& stToLower(std::string& str)
{
  std::transform<std::string::iterator, std::string::iterator, int (*)(int)>(
    str.begin(), str.end(), str.begin(), std::tolower);

  return str;
} // stToLower
//------------------------------------------------------------------------------
/// \brief Returns a new string that is str with all characters uppercase.
/// \param str: The string.
/// \return The new string.
//------------------------------------------------------------------------------
std::string stToUpperCopy(const std::string& str)
{
  std::string copy(str);
  return stToUpper(copy);
} // stToUpperCopy
//------------------------------------------------------------------------------
/// \brief Modifies str to be all uppercase.
/// \param[in,out] str: String to be modified.
/// \return A reference to str.
//------------------------------------------------------------------------------
std::string& stToUpper(std::string& str)
{
  std::transform<std::string::iterator, std::string::iterator, int (*)(int)>(
    str.begin(), str.end(), str.begin(), std::toupper);

  return str;
} // stToUpper
//------------------------------------------------------------------------------
/// \brief Extracts first (leftmost) a_length characters from a_source returning a copy.
/// \param[in] a_source: The string.
/// \param[in] a_length: Number of leftmost characters to keep.
/// \return The new string.
//------------------------------------------------------------------------------
std::string stLeftCopy(const std::string& a_source, size_t const a_length)
{
  // make sure we didn't do signed int arithmetic to pass negative length that
  // converts to very large unsigned number
  XM_ASSERT(a_length == std::string::npos || a_length < (size_t)-1 - 1000);

  std::string copy(a_source);
  return stLeft(copy, a_length);
} // stLeftCopy
//------------------------------------------------------------------------------
/// \brief Modifies a_source to contain the first (leftmost) a_length characters.
/// \param[in,out] a_source: The string that is modified.
/// \param[in]     a_length: Number of leftmost characters to keep.
/// \return A reference to a_source.
//------------------------------------------------------------------------------
std::string& stLeft(std::string& a_source, size_t const a_length)
{
  // make sure we didn't do signed int arithmetic to pass negative length that
  // converts to very large unsigned number
  XM_ASSERT(a_length == std::string::npos || a_length < (size_t)-1 - 1000);

  if (a_length == std::string::npos)
    a_source = "";
  else
    a_source = a_source.substr(0, a_length);
  return a_source;
} // stLeft
//------------------------------------------------------------------------------
/// \brief Extracts last (rightmost) a_length characters from a_source
///        returning a copy.
/// \param[in] a_source: The string.
/// \param[in] a_length: Number of rightmost characters to keep.
/// \return The new string.
//------------------------------------------------------------------------------
std::string stRightCopy(const std::string& a_source, size_t const a_length)
{
  // make sure we didn't do signed int arithmetic to pass negative length that
  // converts to very large unsigned number
  XM_ASSERT(a_length == std::string::npos || a_length < (size_t)-1 - 1000);

  std::string copy(a_source);
  return stRight(copy, a_length);
} // stRightCopy
//------------------------------------------------------------------------------
/// \brief Removes all white space from the passed string.
/// \param[in] str: The string to be modified.
/// \return Modified string.
//------------------------------------------------------------------------------
std::string stSimplified(const std::string& str)
{
  std::string modified = std::regex_replace(str, std::regex("\\s+"), " ");
  modified = boost::trim_copy(modified);
  return modified;
} // stSimplified
//------------------------------------------------------------------------------
/// \brief Checks if first string contains second. Case insensitive.
/// \param[in] a_container: Container to search if it includes a substr.
/// \param[in] a_substr: Substring to search for in the container.
/// \return True if a_container contains an occurrence of a_substr, otherwise False.
//------------------------------------------------------------------------------
bool stContains(const std::string& a_container, const std::string& a_substr)
{
  std::string container = boost::to_upper_copy(a_container);
  std::string substr = boost::to_upper_copy(a_substr);

  // return std::search(container.begin(), container.end(),
  //                          substr.begin(), substr.end()) != container.end();

  if (container.find(substr) != std::string::npos)
    return true;
  return false;

} // stContains
//------------------------------------------------------------------------------
/// \brief Checks if a vec of strings contains a string. Case sensitive.
/// \param[in] a_container: Vec of strings to iterate through.
/// \param[in] str: String to search for in the container.
/// \return True if a_container contains a str, otherwise False.
//------------------------------------------------------------------------------
bool stVectorContainsString(const VecStr& a_container, const std::string& str)
{
  return (std::find(a_container.begin(), a_container.end(), str) != a_container.end());
} // stVectorContainsString
//------------------------------------------------------------------------------
/// \brief Modifies a_source to contain the last (rightmost) a_length characters.
/// \param[in,out] a_source: The string that is modified.
/// \param[in]     a_length: Number of rightmost characters to keep.
/// \return A reference to a_source.
//------------------------------------------------------------------------------
std::string& stRight(std::string& a_source, size_t const a_length)
{
  // make sure we didn't do signed int arithmetic to pass negative length that
  // converts to very large unsigned number
  XM_ASSERT(a_length == std::string::npos || a_length < (size_t)-1 - 1000);

  if (a_length >= a_source.size())
  {
    return a_source;
  }
  a_source = a_source.substr(a_source.size() - a_length);
  return a_source;
} // stRight
//------------------------------------------------------------------------------
/// \brief Returns true if a and b are equal while ignoring capitalization.
/// \param[in] a: First string.
/// \param[in] b: Second string.
/// \return true or false.
//------------------------------------------------------------------------------
bool stEqualNoCase(const std::string& a, const std::string& b)
{
  return boost::iequals(a, b);
} // stEqualNoCase
//------------------------------------------------------------------------------
/// \brief Returns true if a contains b while ignoring capitalization.
/// \param[in] a: String to search.
/// \param[in] b: Substring searching for.
/// \return true or false.
//------------------------------------------------------------------------------
bool stFindNoCase(const std::string& a, const std::string& b)
{
  return stToLowerCopy(a).find(stToLowerCopy(b)) != std::string::npos;
} // stEqualNoCase
//------------------------------------------------------------------------------
/// \brief Changes str to "str (2)" etc. if it is in set of set_str
/// \param[in] set_str: A set of strings.
/// \param[in,out] str: A string that's made unique if it is in set_str.
/// \return false if already unique, true if updated.
//------------------------------------------------------------------------------
bool stMakeUnique(const std::set<std::string>& set_str, std::string& str)
{
  if (set_str.find(str) == set_str.end())
  {
    // the name is already unique
    return false;
  }

  std::string tmpstr;

  do
  {
    std::string::size_type pos1, pos2;

    pos1 = str.find('(');
    pos2 = str.find(')');

    if ((pos1 != std::string::npos) && (pos2 != std::string::npos) && (pos1 < pos2))
    {
      int old_val;
      std::string::size_type diff;
      std::stringstream ss;

      pos1++;

      diff = pos2 - pos1;

      ss.str(str.substr(pos1, diff));

      ss >> old_val;

      if (!ss.fail() && ss.eof())
      {
        ss.clear();
        ss.str("");
        ss << (old_val + 1);
        str.replace(pos1, diff, ss.str(), 0, ss.str().length());
      }
      else
      {
        str += " (2)";
      }
    }
    else
    {
      str += " (2)";
    }
  } while (set_str.find(str) != set_str.end());

  return true;
} // stMakeUnique
//------------------------------------------------------------------------------
/// \brief Convert a string to an int.
///
/// Better than stringstream or boost::lexical_cast. See:
/// http://stackoverflow.com/questions/194465/how-to-parse-a-string-to-an-int-in-c
/// \param[in]  s:    The string.
/// \param[out] i:    The double.
/// \param[in]  base: Numeric base.
/// \return true if successful
//------------------------------------------------------------------------------
bool stStringToInt(const std::string& s, int& i, int base /*= 0*/)
{
  try
  {
    size_t bad;
    i = std::stoi(s, &bad, base);
    if (bad < s.size())
    {
      return false;
    }
  }
  catch (std::exception)
  {
    return false;
  }
  return true;
} // stStringToInt
//------------------------------------------------------------------------------
/// \brief Convert a string to an double.
///
/// Better than stringstream or boost::lexical_cast. See:
/// http://stackoverflow.com/questions/194465/how-to-parse-a-string-to-an-int-in-c
/// \param[in]  s: The string.
/// \param[out] d: The double.
/// \return true if successful
//------------------------------------------------------------------------------
bool stStringToDouble(const std::string& s, double& d)
{
  try
  {
    size_t bad;
    d = std::stod(s, &bad);
    if (bad < s.size())
    {
      return false;
    }
  }
  catch (std::exception)
  {
    return false;
  }
  return true;
} // stStringToDouble
//------------------------------------------------------------------------------
/// \brief Returns precision, or the number of digits to the right of the
///        decimal needed to display the [value].  This is used in conjunction
///        with FloatToString() or STR() to get the string.  The precision
///        is calculated such that the total string length (including the
///        minus sign, decimal, E etc.) will never end up longer than
///        \a length (by default, 15 characters) so all edit fields can be
///        about 60 dialog units wide on PC.
/// \param[in]  value: The value.
/// \param[out] flags: Can be either 0, or STR_FLOAT, STR_SCIENTIFIC, or
///         STR_FLOAT | STR_SCIENTIFIC.  So, if your number is a float, or you
///         want it in scientific notation, you can specify that with the flags.
/// \param[in] length: Number characters available to display the number
/// \return The precision.
//------------------------------------------------------------------------------
int stPrecision(double value, int& flags, int length /* =15 */)
{
#if BOOST_OS_WINDOWS
  if (!_finite(value))
#else
  if (!std::isfinite(value))
#endif
    return 0;

  const int MAXFLOATDIGITS(7);   // max sig figs available with single precision
  const int MAXDOUBLEDIGITS(14); // max sig figs available with double precision

  double i; // integer part
  double f; // fractional part
  std::string istring;
  std::string fstring;
  std::string format;
  size_t charptr;
  int64_t ipart = 0;
  short ilength, flength; // string lengths of integer and fractional parts
  short prec;             // ends up as num sig figs to right of decimal
  short maxdigits;        // max num digits to right of decimal to meet limit of 15
  bool isFraction = false;

  // Step 1 ////////////////////////////////////////////////////////////////////

  /* First test if we need scientific notation for example
     123456789012345

     -1000000000000.0  <- this number gets changed to...
     -1.0000000e+012   <- this
     -0.000001234567   <- this number gets changed to...
     -1.2345678e-006   <- this
  */

  if (length >= 8)
  { // Have to have at least 8 spaces to do sci notation
    double max;
    max = pow(10.0, (double)(length - 3));
    const double min = 1e-5; // arbitrary value to use scientific notation below
    // const double toleranceValueForZero = 1e-15; // arbitrary value to make values
    //                                            // below zero (perhaps should be
    //                                            // user defined in future)
    // I'm returning this to the way it was because this change broke one of
    // our tutorials in which 2e-17 is a valid input but this change made it
    // impossible to enter that number and switched it to 0.0. I don't think
    // we can impose an arbitrary value here in this macro that will be
    // satisfactory to everyone in all cases. So, it should be done outside
    // of this macro. Please don't change this without discussing it with
    // everyone. -MJK
    if (GT_EPS(fabs(value), max, DBL_EPSILON) || EQ_EPS(fabs(value), max, DBL_EPSILON) ||
        //(GT_TOL(fabs(value), 0.0, toleranceValueForZero) &&
        (GT_EPS(fabs(value), 0.0, DBL_EPSILON) && LT_EPS(fabs(value), min, DBL_EPSILON)))
    {
      flags |= STR_SCIENTIFIC;
    }
  }

  // Step 2 ////////////////////////////////////////////////////////////////////

  /* Now find the number of sig figs there are to the right
     of the decimal.  The basic strategy is to
     get a string from the number and count the characters that are sig
     figs.  There are different ways to get a string from the number and
     we have tried and compared several in an attempt to get the best
     results.  The switch statement below has the different methods we've
     tried.  We keep the old stuff around because when we find that the
     current thing isn't working for some case, we can look back and see
     what we've already tried. */

  if (flags & STR_SCIENTIFIC)
  {
    if (flags & STR_FLOAT)
      istring = (boost::format("%1.6e") % value).str();
    else
      istring = (boost::format("%1.15e") % value).str();
    fstring = istring;
    charptr = istring.find('.');
    istring = istring.substr(0, charptr);
    charptr = fstring.find('.');
    if (charptr != std::string::npos)
    {
      charptr++;
      fstring = fstring.substr(charptr);
    }
    charptr = fstring.find('e');
    fstring = fstring.substr(0, charptr);
  }
  else
  {
    int myvar = 3;
    std::string theval;
    switch (myvar)
    {
    case 1: // here we try getting all the digits we can and then formatting
            // the string afterward

    {
      // force the number into scientific and get all available valid digits
      if (flags & STR_FLOAT)
        theval = (boost::format("%1.6e") % value).str();
      else
        theval = (boost::format("%1.13e") % value).str();

      f = modf(value, &i);
      ipart = boost::numeric_cast<int64_t>(i);
      // get a string from the number
      istring = (boost::format("%d") % ipart).str();
      ilength = (short)istring.size();

      // remove the period from the string
      stRemove(theval, '.');
      // remove the integer part from the front of the string
      theval.erase(0, ilength);
      // delete the end of the string where 'e+004' is
      size_t indx = theval.find("e");
      theval.erase(indx, theval.size() - indx);
      // copy what is left into fstring
      fstring = theval;
    }
    break;
    case 2:
    {
      f = modf(value, &i);
      ipart = boost::numeric_cast<int64_t>(i);
      istring = (boost::format("%d") % ipart).str();
      // get a string from the number
      fstring = (boost::format("%Lg") % f).str();
      // Sometimes %g will use scientific notation, sometimes it won't.  If it
      // does, we've got to switch it to non-scientific notation.
      if (fstring.find("e") != std::string::npos || fstring.find("E") != std::string::npos)
      {
        double f2; // fractional part
        f2 = std::stod(fstring);
        fstring = (boost::format("%.16lf") % f2).str();
      }
      charptr = fstring.find('.');
      if (charptr != std::string::npos)
      {
        charptr++;
        fstring = fstring.substr(charptr);
      }
    }
    break;
    case 3:
    {
      modf(value, &i);
      ipart = boost::numeric_cast<int64_t>(i);
      istring = (boost::format("%d") % ipart).str();
      ilength = (short)istring.size();
      if (ipart < 0)
        ilength--;

      int maxDigits;
      if (flags & STR_FLOAT)
        maxDigits = MAXFLOATDIGITS;
      else
        maxDigits = MAXDOUBLEDIGITS;
      if (ipart == 0 && value != 0.0)
      {
        isFraction = true;
        modf(log10(fabs(value)), &i);
        int digits = maxDigits - Round(i);
        if (value > 0.0)
          ilength = (short)(digits + 2);
        else
          ilength = (short)(digits + 3);
        format = (boost::format("%s%d.%d%s") % "%" % ilength % digits % "f").str();
      }
      else
      {
        format =
          (boost::format("%s%d.%d%s") % "%" % ilength % Miabs(maxDigits - ilength) % "f").str();
      }

      fstring = (boost::format(format) % value).str();

      charptr = fstring.find('.');
      if (charptr != std::string::npos)
      {
        charptr++;
        fstring = fstring.substr(charptr);
      }
    }
    break;
    }
  }
  ilength = (short)istring.size();
  flength = (short)fstring.size();

  /* "Only about 7 decimal digits are representable in single-precision IEEE
     format, and about 16 in double-precision IEEE format" (The Perils of
     Floating-Point).  So subtract ilength (the length of the left side) from
     7 or 16 and see how many are left over on the right.  Start from that
     point and work left, skipping zeros until we hit a non-zero number. */
  if (value < 0)
  {
    ilength--; /* don't count the - sign as a sig fig. */
  }
  if (isFraction)
    prec = flength;
  else if (flags & STR_FLOAT)
  {
    prec = MAXFLOATDIGITS - ilength - 1;
  }
  else
  {
    prec = MAXDOUBLEDIGITS - ilength - 1;
  }
  if (ilength == 1 && ipart == 0)
  {
    prec++; // 0 on left of 0.1 isn't a sig fig, one more avail for right
  }
  if (prec >= flength)
  {
    prec = flength - 1; // just in case we screwed up some how
  }
  for (; prec >= 0; prec--)
  {
    if (fstring.at(prec) != '0')
      break;
  }
  prec++;
  // At this point prec is number of sig figs to the right of the decimal

  // Step 3 ////////////////////////////////////////////////////////////////////

  /* Find the max number of digits to the right of the decimal we can allow,
     based on a total number of <length> digits including the '-' and the '.'
     This is necessary because we might get round off errors above causing
     garbage values towards the end of the string causing prec to be more
     than it should be.  Here's an example if <length> is 15. */

  /*      123456789012345                        123456789012345  maxdigits  */
  /*                         fabs(value) >= fabs(-100000000000.0)     1      */
  /* fabs(-100000000000.0) > fabs(value) >= fabs(-10000000000.00)     2      */
  /* fabs(-10000000000.00) > fabs(value) >= fabs(-1000000000.000)     3      */
  /* fabs(-1000000000.000) > fabs(value) >= fabs(-100000000.0000)     4      */
  /* fabs(-100000000.0000) > fabs(value) >= fabs(-10000000.00000)     5      */
  /* fabs(-10000000.00000) > fabs(value) >= fabs(-1000000.000000)     6      */
  /* fabs(-1000000.000000) > fabs(value) >= fabs(-100000.0000000)     7      */
  /* fabs(-100000.0000000) > fabs(value) >= fabs(-10000.00000000)     8      */
  /* fabs(-10000.00000000) > fabs(value) >= fabs(-1000.000000000)     9      */
  /* fabs(-1000.000000000) > fabs(value) >= fabs(-100.0000000000)     10     */
  /* fabs(-100.0000000000) > fabs(value) >= fabs(-10.00000000000)     11     */
  /* fabs(-10.00000000000) > fabs(value) >= fabs(-1.000000000000)     12     */
  /* fabs(-1.000000000000) > fabs(value) >= fabs(-.1000000000000)     12     */
  /* fabs(-.1000000000000) > fabs(value) >= fabs(-.0100000000000)     12     */

  if (flags & STR_SCIENTIFIC)
  {
    maxdigits = (short)(length - 8); // 8 places used for -1. and e+012
  }
  else
  {
    maxdigits = (short)(length - 3); // 3 because 1 for + or -, 1 for 0, 1 for . (-0.)
    double testval;
    testval = 10.0;
    if (!LT_EPS(fabs(value), testval, DBL_EPSILON))
    {
      do
      {
        maxdigits--;
        testval *= 10.0;
      } while (!LT_EPS(fabs(value), testval, DBL_EPSILON));
    }
  }
  if (!(value < 0.0))
  {
    maxdigits++; // If value is positive, you get one more
  }

  // Step 4 ////////////////////////////////////////////////////////////////////

  // Compare the maximum number of significant digits to the right of the
  // decimal allowed <maxdigits> with how many we have <prec>.  If we have
  // more than we're allowed, we have to throw out the extra.   If we have
  // to throw some out, we have to see if the ones we have left are
  // still significant - if the ones on the right are 0, then they're no
  // longer significant.

  if (prec > maxdigits)
  {
    prec = maxdigits;
    // format = (boost::format("%s%d.%d%s") % "%" % ilength % prec % "f").str();
    // fstring = (boost::format(format) % value).str();
    // charptr = fstring.find('.');
    // if (charptr != std::string::npos) {
    //  charptr++;
    //  fstring = fstring.substr(charptr);
    //}
    if ((int)fstring.size() > prec && fstring.at(prec - 1) == '0')
    {
      std::stringstream ss;
      ss << fstring.at(prec);
      int val;
      ss >> val;
      if (val > 4)
        fstring.at(prec - 1) = '1';
    }
    for (; prec >= 1; prec--)
    {
      if (fstring.at(prec - 1) != '0')
      {
        break;
      }
    }
  }
  if (prec < 1)
  {
    prec = 1; // always show 5.0 instead of just 5 to indicate it's a float
  }

  return prec;
} // stPrecision
//------------------------------------------------------------------------------
/// \brief Get a properly formatted string from a double
///
///        The reason for the short name is so that we can easily
///        replace code like this:
///          fprintf(fp, "%g %g", value1, value2);
///        with code like this:
///          fprintf(fp, "%s %s", STR(value1), STR(value2));
///
/// \param a_value = the floating point number to be formatted as a string
/// \param a_n     = the MAX precision, -1 (default) is auto compute
/// \param width   = the MAX num characters (15 by default)
/// \param flags   = bitwise flags:
///                STR_FLOAT = 1
///                  Treat value as floating point value (i.e. only 7 digits of
///                  precision are available)
///                STR_SCIENTIFIC = 2
///                  Force use of scientific notation
///                STR_USEMAXPREC = 4
///                  This only applies when a_n is not -1. a_n value is the
///                  desired precision. When this flag is set, the returned
///                  string may have less precision because trailing zeros
///                  are removed. When this flag is not set, they are not
///                  removed.
///                  Example:  a_n = 3 and a_value = 5.0003
///                    With this flag, returned string is "5.0". Without this
///                    flag, the returned string is "5.000".
///                STR_FULLWIDTH = 8
///                  Forces string to be 'width' in length. If the number is
///                  less than this width, it is padded with spaces on the
///                  right side.
///                STR_WITHCOMMAS = 16
///                  Includes commas in the number (345,000.0). Does
///                  account for different locales.
/// \return std::string of the number.
//------------------------------------------------------------------------------
std::string STRstd(double a_value, int a_n /*=-1*/, int width /*=15*/, int flags /*=0*/)
{
  std::string str;
  int prec = 0;

  // put this check in for old stuff
  if (a_n >= 800)
  {
    XM_ASSERT(false);
    a_n = -1;
  }

    // check for invalid values
#if BOOST_OS_WINDOWS
  if (!_finite(a_value))
  {
    switch (_fpclass(a_value))
    {
    case _FPCLASS_NINF:
      str = "-INF";
      break;
    case _FPCLASS_PINF:
      str = "+INF";
      break;
    default:
      str = "NaN";
      break;
    }
    return str;
  }
#else
  if (!std::isfinite(a_value))
  {
    switch (std::fpclassify(a_value))
    {
    case FP_INFINITE:
      if (std::signbit(a_value))
        str = "-INF";
      else
        str = "+INF";
      break;
    default:
      str = "NaN";
      break;
    }
    return str;
  }
#endif

  // if not specifying an exact prec, autocompute
  if ((a_n == -1) || (flags & STR_USEMAXPREC))
  {
    // if using max precision and the number is small, truncate the number to
    // max precision here before stPrecision() switches the number to scientific
    // notation (a number that is beyond the limited precision range)
    if ((flags & STR_USEMAXPREC) && LT_TOL(fabs(a_value), 1e-4, DBL_EPSILON))
    {
      a_value *= pow(10.0, a_n);
      a_value = floor(a_value + 0.5);
      a_value /= pow(10.0, a_n);
    }
    // figure out the auto-computed prec is
    try
    {
      prec = stPrecision(a_value, flags, width);
    }
    catch (std::exception&)
    {
      // we had an error. Generally with casting the modf integer part
      return "";
    }
    if ((flags & STR_USEMAXPREC) && prec > a_n)
    {
      prec = a_n;
    }
  }
  else
  {
    prec = a_n;
  }

  // Format the format string, then use it to format str

  std::string format;
  if (flags & STR_SCIENTIFIC)
  {
    // sprintf(format, "%%.%de", Miabs(prec));
    format = (boost::format("%%.%de") % Miabs(prec)).str();
  }
  else
  {
    // sprintf(format, "%%.%dlf", prec);
    // I added Miabs because according to my book it must be nonnegative
    // and some combinations result in a negative prec, which crashes. -MJK
    format = (boost::format("%%.%dlf") % Miabs(prec)).str();
  }

  if (!(flags & STR_WITHCOMMAS))
  {
    // str.Format(format, a_value);
    str = (boost::format(format) % a_value).str();
  }
  else
  {
    // Use the system locale to get the commas (or whatever else)
    std::locale loc(""); // system locale
    str = (boost::format(format, loc) % a_value).str();
  }

  // in some cases when specifying max prec, trailing zeros can occur. For
  // example, if the number is 5.0003 and the maxprec is 3, the string right
  // here will be 5.000 instead of 5.0.
  if ((a_n == -1) || (flags & STR_USEMAXPREC))
  {
    // see if there's a decimal point
    size_t index = str.find('.');
    if (index != std::string::npos)
    {
      if ((index = str.find_first_of("eE")) != std::string::npos)
      {
        // Scientific.  Start at 'e' or 'E' and go left, removing zeros
        index--;
        while (index > 0 && str.at(index) == '0' && str.at(index - 1) != '.')
        {
          str.erase(index, 1);
          index--;
        }
      }
      else
      {
        // take off any trailing zeros
        stTrimRight(str, "0");
        // make sure there's at least one zero
        if (str[str.size() - 1] == '.')
        {
          str += '0';
        }
      }
    }
  }

  // in some cases you want the string to always be a certain number of
  // character. This is most common with FORTRASH fixed format garbage.
  if (flags & STR_FULLWIDTH)
  {
    size_t diff = width - str.size();
    if (diff > 0)
    {
      std::string str1, str2;
      for (size_t i = 0; i < diff; i++)
        str1 += " ";
      str2 = str;
      str = str1 + str2;
    }
  }

  // if the string is "-0.0" remove the negative sign
  if (str == "-0.0")
  {
    str = "0.0";
  }

  return str;
} // STRstd
//----- OVERLOAD ---------------------------------------------------------------
/// \brief Get a properly formatted string from a float
///
///        The reason for the short name is so that we can easily
///        replace code like this:
///          fprintf(fp, "%g %g", value1, value2);
///        with code like this:
///          fprintf(fp, "%s %s", STR(value1), STR(value2));
///
/// \param value = the floating point number to be formatted as a string
/// \param n     = the MAX precision, -1 (default) is auto compute
/// \param width = the MAX num characters (15 by default)
/// \param flags = bitwise flags:
///                STR_FLOAT = 1
///                  Treat value as floating point value (i.e. only 7 digits of
///                  precision are available)
///                STR_SCIENTIFIC = 2
///                  Force use of scientific notation
///                STR_USEMAXPREC = 4
///                  This only applies when a_n is not -1. a_n value is the
///                  desired precision. When this flag is set, the returned
///                  string may have less precision because trailing zeros
///                  are removed. When this flag is not set, they are not
///                  removed.
///                  Example:  a_n = 3 and a_value = 5.0003
///                    With this flag, returned string is "5.0". Without this
///                    flag, the returned string is "5.000".
///                STR_FULLWIDTH = 8
///                  Forces string to be 'width' in length. If the number is
///                  less than this width, it is padded with spaces on the
///                  right side.
///                STR_WITHCOMMAS = 16
///                  Includes commas in the number (345,000.0). Does
///                  account for different locales.
/// \return std::string of the number.
//----- OVERLOAD ---------------------------------------------------------------
std::string STRstd(float value, int n /*=-1*/, int width /*=15*/, int flags /*=0*/)
{
  return STRstd((double)value, n, width, flags);
} // STRstd
//----- OVERLOAD ---------------------------------------------------------------
/// \brief This version is needed because the template parameter could be a
///        string.
/// \param value   = the value.
/// \return The string.
//----- OVERLOAD ---------------------------------------------------------------
std::string STRstd(std::string value)
{
  return value;
}

////////////////////////////////////////////////////////////////////////////////
/// \class StCommaNumpunct
/// \brief Used to format numbers with comma separators.
///        \see http://stackoverflow.com/questions/7276826
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief Returns the character used to separate numbers by thousands.
/// \return The character.
//------------------------------------------------------------------------------
char StCommaNumpunct::do_thousands_sep() const
{
  return ',';
} // StCommaNumpunct::do_thousands_sep
//------------------------------------------------------------------------------
/// \brief Returns the string defining how many numbers between separators.
/// \return The grouping string.
//------------------------------------------------------------------------------
std::string StCommaNumpunct::do_grouping() const
{
  return "\03";
} // StCommaNumpunct::do_grouping

} // end namespace xms

//#if 0
#ifdef CXX_TEST

#include <xmscore/misc/StringUtil.t.h>

#include <xmscore/testing/TestTools.h>
#include <xmscore/testing/TestTools.h>

//----- Namespace declaration --------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// \class StringUtilUnitTests
/// \brief Tests for StringUtil
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief Test stChangeExtendedAscii
//------------------------------------------------------------------------------
void StringUtilUnitTests::testExtendedASCII()
{
  // \xb2 superscript two - squared
  // \xb3 superscript three - cubed
  // \xb0 degree sign
  std::string str1("test\xb2");
  std::string str2("test\xb3");
  std::string str3("\xb0test");

  xms::stChangeExtendedAscii(str1, false);
  xms::stChangeExtendedAscii(str2, false);
  xms::stChangeExtendedAscii(str3, false);

  TS_ASSERT_EQUALS("test^2", str1);
  TS_ASSERT_EQUALS("test^3", str2);
  TS_ASSERT_EQUALS("deg_test", str3);

  xms::stChangeExtendedAscii(str1, true);
  xms::stChangeExtendedAscii(str2, true);
  xms::stChangeExtendedAscii(str3, true);

  TS_ASSERT_EQUALS("test\xb2", str1);
  TS_ASSERT_EQUALS("test\xb3", str2);
  TS_ASSERT_EQUALS("\xb0test", str3);
} // StringUtilUnitTests::testExtendedASCII
//------------------------------------------------------------------------------
/// \brief Test stImplode
//------------------------------------------------------------------------------
void StringUtilUnitTests::testImplodeExplode()
{
  std::vector<std::string> values;

  values.push_back("test");
  values.push_back("test2");
  values.push_back("test3");
  values.push_back("test4");

  std::string result = xms::stImplode(values, "stuff");

  TS_ASSERT_EQUALS("teststufftest2stufftest3stufftest4", result);

  std::vector<std::string> result2;
  result2 = xms::stExplode(result, "stuff");
  TS_ASSERT_EQUALS_VEC(values, result2);

  values.clear();
  result = xms::stImplode(values, "stuff");
  TS_ASSERT_EQUALS("", result);

  result2 = xms::stExplode(result, "stuff");
  TS_ASSERT_EQUALS_VEC(values, result2);

  values.push_back("test");
  result = xms::stImplode(values, "stuff");
  TS_ASSERT_EQUALS("test", result);

  result2 = xms::stExplode(result, "stuff");
  TS_ASSERT_EQUALS_VEC(values, result2);

  result = xms::stImplode(values, "     "); // test     test2     test3     test4
  result2 = xms::stExplode(result, " ");
  std::vector<std::string> expected = {"test", "test2", "test3", "test4"};
  // TS_ASSERT_EQUALS_VEC(expected, result2); // FAIL!

} // StringUtilUnitTests::testImplodeExplode
//------------------------------------------------------------------------------
/// \brief Test stIndexOfElem()
//------------------------------------------------------------------------------
void StringUtilUnitTests::testSuIndexOfElem()
{
  int expected = -1;
  xms::VecStr container = {"me", "you", "they", "we", "Us"};
  int test1 = xms::stIndexOfElem(container, "us"); // this should return -1
  TS_ASSERT_EQUALS(expected, test1);

  expected = 2;
  int test2 = xms::stIndexOfElem(container, "they"); // this should return 2
  TS_ASSERT_EQUALS(expected, test2);
} // StringUtilUnitTests::testSuIndexOfElem
//------------------------------------------------------------------------------
/// \brief Test stSplit
//------------------------------------------------------------------------------
void StringUtilUnitTests::testSplit()
{
  std::string s = " 1 2  3\t4\t\t5 \t6 ";
  std::vector<std::string> expected;
  std::vector<std::string> r;

  r = xms::stSplit(s);
  expected = {"1", "2", "3", "4", "5", "6"};
  TS_ASSERT_EQUALS_VEC(expected, r);

  r = xms::stSplit(s, " ");
  expected = {"1", "2", "3\t4\t\t5", "\t6"};
  TS_ASSERT_EQUALS_VEC(expected, r);

  r = xms::stSplit(s, "\t");
  expected = {" 1 2  3", "4", "5 ", "6 "};
  TS_ASSERT_EQUALS_VEC(expected, r);

  r = xms::stSplit(s, " \t");
  expected = {"1", "2", "3", "4", "5", "6"};
  TS_ASSERT_EQUALS_VEC(expected, r);

  r = xms::stSplit(",,A,B,,C,,,", ",", false);
  expected = {"", "", "A", "B", "", "C", "", "", ""};
  TS_ASSERT_EQUALS_VEC(expected, r);
} // StringUtilUnitTests::testSplit
//------------------------------------------------------------------------------
/// \brief Test stMakeUnique
//------------------------------------------------------------------------------
void StringUtilUnitTests::testMakeUnique()
{
  const std::string expected1("make");
  const std::string expected2("make (2)");
  const std::string expected3("make (10)");

  std::set<std::string> set_str;
  std::string str("make");

  set_str.insert("test");
  set_str.insert("stuff");
  set_str.insert("yup");

  TS_ASSERT(!xms::stMakeUnique(set_str, str));
  TS_ASSERT_EQUALS(expected1, str);

  set_str.insert("make");
  set_str.insert("make (3)");

  TS_ASSERT(xms::stMakeUnique(set_str, str));
  TS_ASSERT_EQUALS(expected2, str);

  set_str.insert("make (2)");
  set_str.insert("make (4)");
  set_str.insert("make (5)");
  set_str.insert("make (6)");
  set_str.insert("make (7)");
  set_str.insert("make (8)");
  set_str.insert("make (9)");

  TS_ASSERT(xms::stMakeUnique(set_str, str));
  TS_ASSERT_EQUALS(expected3, str);
} // StringUtilUnitTests::testMakeUnique
//------------------------------------------------------------------------------
/// \brief Test stTrim
//------------------------------------------------------------------------------
void StringUtilUnitTests::testTrim()
{
  // TS_FAIL("StringUtilUnitTests::testTrim");
  {
    std::string test("\f  this has white space\t   \n   \r  \v");
    xms::stTrim(test);
    TS_ASSERT_EQUALS("this has white space", test);
  }
  {
    std::string test("              ");
    xms::stTrim(test);
    // Is this how it should work?
    // TS_ASSERT_EQUALS("              ", test);
    // No. Fixed to match how CString::Trim works 5/29/2015 by MJK.
    TS_ASSERT_EQUALS("", test);
  }
  {
    std::string test("    ,     *     ");
    xms::stTrim(test, " ,*");
    TS_ASSERT_EQUALS("", test);
  }
} // StringUtilUnitTests::testTrim
//------------------------------------------------------------------------------
/// \brief Test stReplace
//------------------------------------------------------------------------------
void StringUtilUnitTests::testReplace()
{
  std::string test("this has a few spaces");

  xms::stReplace(test, ' ', '_');
  TS_ASSERT_EQUALS("this_has_a_few_spaces", test);

  std::string test_copy(xms::stReplaceCopy(test, '_', ' '));
  TS_ASSERT_EQUALS("this has a few spaces", test_copy);
  TS_ASSERT_EQUALS("this_has_a_few_spaces", test);

  xms::stReplace(test, "a_few", "zero");
  TS_ASSERT_EQUALS("this_has_zero_spaces", test);

  xms::stReplace(test, "_", ""); // Replace spaces with nothing
  TS_ASSERT_EQUALS("thishaszerospaces", test);
} // StringUtilUnitTests::testReplace
//------------------------------------------------------------------------------
/// \brief Test stCountChar
//------------------------------------------------------------------------------
void StringUtilUnitTests::testCountChar()
{
  std::string test(
    "how much wood would a woodchuck chuck if a woodchuck could"
    " chuck wood?");

  TS_ASSERT_EQUALS(11, xms::stCountChar(test, 'o'));
} // StringUtilUnitTests::testCountChar
//------------------------------------------------------------------------------
/// \brief Test stNumeric and stScientificNotation
//------------------------------------------------------------------------------
void StringUtilUnitTests::testNumAndSciNot()
{
  std::string test("-123e+201");

  TS_ASSERT(xms::stNumeric(test));
  TS_ASSERT(xms::stScientificNotation(test));

  test = "42";

  TS_ASSERT(xms::stNumeric(test));
  TS_ASSERT(!xms::stScientificNotation(test));

  test = "muffin monster";

  TS_ASSERT(!xms::stNumeric(test));
  TS_ASSERT(!xms::stScientificNotation(test));
  // This is why you don't pass false unless you are sure you have a number.
  // It will pass if it finds an e or E. This is for speeding up if you create
  // a stNumeric string and want to see if it went to scientific notation.
  TS_ASSERT(xms::stScientificNotation(test, false));
} // StringUtilUnitTests::testNumAndSciNot
//------------------------------------------------------------------------------
/// \brief test stToUpper
//------------------------------------------------------------------------------
void StringUtilUnitTests::testToUpper()
{
  std::string str("aBcD");
  TS_ASSERT_EQUALS("ABCD", xms::stToUpper(str));

  const std::string str_const("aBcD");
  // TS_ASSERT_EQUALS("ABCD", xms::stToUpper(str_const));
  // The above doesn't compile. You have to use stToUpperCopy with a const
  TS_ASSERT_EQUALS("ABCD", xms::stToUpperCopy(str_const));

} // StringUtilUnitTests::testToUpper
//------------------------------------------------------------------------------
/// \brief test stStringToInt
//------------------------------------------------------------------------------
void StringUtilUnitTests::test_str2int()
{
  // TS_FAIL("StringUtilUnitTests::test_str2int");

  std::string str;
  const int TEST_NONE = -1;
  int i = TEST_NONE;
  bool rv;

  str = "";
  i = TEST_NONE;
  rv = xms::stStringToInt(str, i);
  TS_ASSERT_EQUALS(i, TEST_NONE);
  TS_ASSERT_EQUALS(rv, false);

  str = "aBcD";
  i = TEST_NONE;
  rv = xms::stStringToInt(str, i);
  TS_ASSERT_EQUALS(i, TEST_NONE);
  TS_ASSERT_EQUALS(rv, false);

  str = "1aBcD";
  i = TEST_NONE;
  rv = xms::stStringToInt(str, i);
  TS_ASSERT_EQUALS(i, 1);
  TS_ASSERT_EQUALS(rv, false);

  str = "1";
  i = TEST_NONE;
  rv = xms::stStringToInt(str, i);
  TS_ASSERT_EQUALS(i, 1);
  TS_ASSERT_EQUALS(rv, true);

  str = "-1";
  i = TEST_NONE;
  rv = xms::stStringToInt(str, i);
  TS_ASSERT_EQUALS(i, -1);
  TS_ASSERT_EQUALS(rv, true);

  str = "0";
  i = TEST_NONE;
  rv = xms::stStringToInt(str, i);
  TS_ASSERT_EQUALS(i, 0);
  TS_ASSERT_EQUALS(rv, true);

  str = "1.0";
  i = TEST_NONE;
  rv = xms::stStringToInt(str, i);
  TS_ASSERT_EQUALS(i, 1);
  TS_ASSERT_EQUALS(rv, false);

  str = "1.5";
  i = TEST_NONE;
  rv = xms::stStringToInt(str, i);
  TS_ASSERT_EQUALS(i, 1);
  TS_ASSERT_EQUALS(rv, false);

} // StringUtilUnitTests::testToUpper
//------------------------------------------------------------------------------
/// \brief test various string utility functions.
//------------------------------------------------------------------------------
void StringUtilUnitTests::testMisc()
{
  // TS_FAIL("StringUtilUnitTests::testMisc");

  std::string s1 = "abcdefg";
  const std::string s2 = s1;
  std::string s3;

  // stLeft

  xms::stLeft(s1, 0);
  TS_ASSERT_EQUALS("", s1);
  s1 = s2;
  xms::stLeft(s1, 1);
  TS_ASSERT_EQUALS("a", s1);
  s1 = s2;
  xms::stLeft(s1, 2);
  TS_ASSERT_EQUALS("ab", s1);
  s1 = s2;
  xms::stLeft(s1, 7);
  TS_ASSERT_EQUALS("abcdefg", s1);
  s1 = s2;
  xms::stLeft(s1, 8);
  TS_ASSERT_EQUALS("abcdefg", s1);
  s1 = s2;

  // stLeftCopy

  s3 = xms::stLeftCopy(s2, 0);
  TS_ASSERT_EQUALS("abcdefg", s2);
  TS_ASSERT_EQUALS("", s3);
  s3 = xms::stLeftCopy(s2, 1);
  TS_ASSERT_EQUALS("abcdefg", s2);
  TS_ASSERT_EQUALS("a", s3);
  s3 = xms::stLeftCopy(s2, 2);
  TS_ASSERT_EQUALS("abcdefg", s2);
  TS_ASSERT_EQUALS("ab", s3);
  s3 = xms::stLeftCopy(s2, 7);
  TS_ASSERT_EQUALS("abcdefg", s2);
  TS_ASSERT_EQUALS("abcdefg", s3);
  s3 = xms::stLeftCopy(s2, 8);
  TS_ASSERT_EQUALS("abcdefg", s2);
  TS_ASSERT_EQUALS("abcdefg", s3);

  // stRight

  xms::stRight(s1, 0);
  TS_ASSERT_EQUALS("", s1);
  s1 = s2;
  xms::stRight(s1, 1);
  TS_ASSERT_EQUALS("g", s1);
  s1 = s2;
  xms::stRight(s1, 2);
  TS_ASSERT_EQUALS("fg", s1);
  s1 = s2;
  xms::stRight(s1, 7);
  TS_ASSERT_EQUALS("abcdefg", s1);
  s1 = s2;
  xms::stRight(s1, 8);
  TS_ASSERT_EQUALS("abcdefg", s1);
  s1 = s2;

  // stRightCopy

  s3 = xms::stRightCopy(s2, 0);
  TS_ASSERT_EQUALS("abcdefg", s2);
  TS_ASSERT_EQUALS("", s3);
  s3 = xms::stRightCopy(s2, 1);
  TS_ASSERT_EQUALS("abcdefg", s2);
  TS_ASSERT_EQUALS("g", s3);
  s3 = xms::stRightCopy(s2, 2);
  TS_ASSERT_EQUALS("abcdefg", s2);
  TS_ASSERT_EQUALS("fg", s3);
  s3 = xms::stRightCopy(s2, 7);
  TS_ASSERT_EQUALS("abcdefg", s2);
  TS_ASSERT_EQUALS("abcdefg", s3);
  s3 = xms::stRightCopy(s2, 8);
  TS_ASSERT_EQUALS("abcdefg", s2);
  TS_ASSERT_EQUALS("abcdefg", s3);

  // stEqualNoCase

  TS_ASSERT_EQUALS(true, xms::stEqualNoCase("ABC", "abc"));
  TS_ASSERT_EQUALS(true, xms::stEqualNoCase("abc", "ABC"));
  TS_ASSERT_EQUALS(false, xms::stEqualNoCase("ABC", "ABCD"));
  TS_ASSERT_EQUALS(false, xms::stEqualNoCase("abc", "abcd"));
  TS_ASSERT_EQUALS(false, xms::stEqualNoCase("BCD", "ABCD"));
  TS_ASSERT_EQUALS(false, xms::stEqualNoCase("bcd", "abcd"));
  TS_ASSERT_EQUALS(false, xms::stEqualNoCase("ABC", "DEFG"));

  // stRemove

  std::string s7 = "abcd abcd abcd";
  const std::string s8 = s7;
  std::string s9;

  xms::stRemove(s7, ' ');
  TS_ASSERT_EQUALS("abcdabcdabcd", s7);
  s7 = s8;
  xms::stRemove(s7, 'g');
  TS_ASSERT_EQUALS("abcd abcd abcd", s7);
  s7 = s8;
  xms::stRemove(s7, 'c');
  TS_ASSERT_EQUALS("abd abd abd", s7);

  // stRemoveCopy
  s9 = xms::stRemoveCopy(s8, ' ');
  TS_ASSERT_EQUALS("abcd abcd abcd", s8);
  TS_ASSERT_EQUALS("abcdabcdabcd", s9);
  s9 = xms::stRemoveCopy(s8, 'g');
  TS_ASSERT_EQUALS("abcd abcd abcd", s8);
  TS_ASSERT_EQUALS("abcd abcd abcd", s9);
  s9 = xms::stRemoveCopy(s8, 'c');
  TS_ASSERT_EQUALS("abcd abcd abcd", s8);
  TS_ASSERT_EQUALS("abd abd abd", s9);

} // StringUtilUnitTests::testMisc
//------------------------------------------------------------------------------
/// \brief Tests StCommaNumpunct.
//------------------------------------------------------------------------------
void StringUtilUnitTests::testXmCommaNumpunct()
{
  double d1 = 123456.0123;
  double d2 = 0.123456789;
  int i = 123456789;
  std::stringstream ss;
  std::locale commaLocale(std::locale(), new xms::StCommaNumpunct());
  ss.imbue(commaLocale);
  ss << d1 << " " << d2 << " " << i;
  std::string s(ss.str());
  std::string expected = "123,456 0.123457 123,456,789";
  TS_ASSERT_EQUALS(expected, s);
} // StringUtilUnitTests::testXmCommaNumpunct
//------------------------------------------------------------------------------
/// \brief Tests stSimplified.
//------------------------------------------------------------------------------
void StringUtilUnitTests::testSuSimplified()
{
  std::string s = "\t  Testing  \rextra   \nspace \t    \n\t";
  std::string expected = "Testing extra space";
  std::string modified = xms::stSimplified(s);
  TS_ASSERT_EQUALS(expected, modified);
} // StringUtilUnitTests::testXmCommaNumpunct
//------------------------------------------------------------------------------
/// \brief Tests stContains
//------------------------------------------------------------------------------
void StringUtilUnitTests::testSuIcontains()
{
  std::string container = "Isn't ThiS a Lovely day?";
  std::string str1 = "DAY";
  std::string str2 = "these a";
  bool expectedT = true;
  bool expectedF = false;

  bool test1 = xms::stContains(container, str1);
  TS_ASSERT_EQUALS(expectedT, test1);

  bool test2 = xms::stContains(container, str2);
  TS_ASSERT_EQUALS(expectedF, test2);

  bool test3 = xms::stContains(container, "THis");
  TS_ASSERT_EQUALS(expectedT, test3)
} // StringUtilUnitTests::testSuIcontains()
//------------------------------------------------------------------------------
/// \brief Tests stVectorContainsString
//------------------------------------------------------------------------------
void StringUtilUnitTests::testSuVecContainsStr()
{
  bool expectedT = true;
  bool expectedF = false;
  xms::VecStr container = {"me", "you", "they", "we", "Us"};

  bool test1 = xms::stVectorContainsString(container, "we");
  TS_ASSERT_EQUALS(expectedT, test1);

  bool test2 = xms::stVectorContainsString(container, "she");
  TS_ASSERT_EQUALS(expectedF, test2);
} // StringUtilUnitTests::testSuVecContainsStr
#endif
//#endif
