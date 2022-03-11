#pragma once
//------------------------------------------------------------------------------
/// \file
/// \ingroup xmscore_misc
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 3. Standard Library Headers
#pragma warning(push)
#pragma warning(disable : 4996) // Windows code: unsafe
#include <iomanip>
#pragma warning(pop)
#include <set>
#include <string>
#include <type_traits>
#include <vector>

// 4. External Library Headers

// 5. Shared Headers
#include <xmscore/stl/vector.h>
#include <xmscore/xmlocale/xmlocale.h>

// 6. Non-shared Headers

namespace xms
{
/// Bitwise flags used by stPrecision(), and STR()
enum PrecFlags {
  STR_FLOAT = 0x01 ///< Float, not double
  ,
  STR_SCIENTIFIC = 0x02 ///< Use scientific notation
  ,
  STR_USEMAXPREC = 0x04 ///< Use maximum precision
  ,
  STR_FULLWIDTH = 0x08 ///< Use full width
  ,
  STR_WITHCOMMAS = 0x10 ///< Use commas in string
};

////////////////////////////////////////////////////////////////////////////////
class StTemp2DigitExponents
{
public:
  StTemp2DigitExponents();
  ~StTemp2DigitExponents();

private:
  int m_oldOutputFormat; ///< Saved output format to restore to orignal value
};

static const char* ST_WHITESPACE = N_(" \t\n\f\r\v"); ///< Whitespace characters

// Convenience functions

bool stEqualNoCase(const std::string&, const std::string&);
bool stFindNoCase(const std::string&, const std::string&);

VecStr stSplit(const std::string& source,
               const std::string& a_delimiterList = ST_WHITESPACE,
               bool a_delimiterCompressOn = true);
VecStr stExplode(const std::string& source, const std::string& a_delimiterString);
std::string stImplode(const std::vector<std::string>& source, const std::string& delim);
int stIndexOfElem(const VecStr& a_container, const std::string& str);

std::string& stLeft(std::string& a_source, size_t const a_length);
std::string stLeftCopy(const std::string& a_source, size_t const a_length);

std::string& stRemove(std::string& str, char source);
std::string stRemoveCopy(const std::string& str, char source);

std::string& stReplace(std::string& str, char source, char dest);
std::string& stReplace(std::string& str, const std::string& source, const std::string& dest);
std::string stReplaceCopy(const std::string& str, char source, char dest);
std::string stReplaceCopy(const std::string& str,
                          const std::string& source,
                          const std::string& dest);

std::string& stRight(std::string& a_source, size_t const a_length);
std::string stRightCopy(const std::string& a_source, size_t const a_length);

std::string stSimplified(const std::string& str);
bool stContains(const std::string& a_container, const std::string& a_substr);
bool stVectorContainsString(const VecStr& a_container, const std::string& str);

std::string& stToLower(std::string& str);
std::string stToLowerCopy(const std::string& str);
std::string& stToUpper(std::string& str);
std::string stToUpperCopy(const std::string& str);

std::string& stTrim(std::string& str, const std::string& delim = ST_WHITESPACE);
std::string stTrimCopy(const std::string& str, const std::string& delim = ST_WHITESPACE);
std::string& stTrimLeft(std::string& str, const std::string& delim = ST_WHITESPACE);
std::string& stTrimRight(std::string& str, const std::string& delim = ST_WHITESPACE);

// Misc

unsigned int stCountChar(const std::string& str, char c);
bool stNumeric(const std::string& str);
bool stScientificNotation(const std::string& str, bool check_numeric = true);
void stChangeExtendedAscii(std::string& str, bool to_extended);
bool stMakeUnique(const std::set<std::string>& set_str, std::string& str);
bool stStringToInt(const std::string&, int& i, int base = 0);
bool stStringToDouble(const std::string&, double& d);

int stPrecision(double value, int& flags, int length = 15);

// Number to string

std::string STRstd(double a_value, int a_n = -1, int width = 15, int flags = 0);
std::string STRstd(float a_value, int a_n = -1, int width = 15, int flags = 0);

//----- OVERLOAD ---------------------------------------------------------------
/// brief Formats an integral type (int, unsigned int, etc ) as a std::string.
///        Ignores precision (n) arg (always 0) and only honors flags
///        STR_SCIENTIFIC and STR_FULLWIDTH.
///
///        This overload is needed when called from a template function.
/// \param a_value = the value.
/// \param a_n     = ignored
/// \param width = the MAX num characters (15 by default)
/// \param flags = \see STRstd for doubles for documentation.
/// \return The string.
template <typename T>
inline std::string STRstd(T a_value, int a_n = 0, int width = 0, int flags = 0)
{
  static_assert(std::is_integral<T>::value, N_("Not an integral (integer) type"));
  a_n = ((flags & STR_SCIENTIFIC) ? -1 : 0);
  return STRstd((double)a_value, a_n, width, flags);
}

std::string STRstd(std::string a_value);

////////////////////////////////////////////////////////////////////////////////
class StCommaNumpunct : public std::numpunct<char>
{
protected:
  virtual char do_thousands_sep() const;
  virtual std::string do_grouping() const;
}; // class StCommaNumpunct

} // end namespace xms
