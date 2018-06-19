#pragma once
//------------------------------------------------------------------------------
/// \file
/// \ingroup xmscore_misc
/// \copyright (C) Copyright Aquaveo 2018. Distributed under the xmsng
///  Software License, Version 1.0. (See accompanying file
///  LICENSE_1_0.txt or copy at http://www.aquaveo.com/xmsng/LICENSE_1_0.txt)
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

// 6. Non-shared Headers

namespace xms
{
/// Bitwise flags used by Prec(), and STR()
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
class Temp2DigitExponents
{
public:
  Temp2DigitExponents();
  ~Temp2DigitExponents();

private:
  int m_oldOutputFormat; ///< Saved output format to restore to orignal value
};

namespace xus
{ // (xms string utilities)

static const char* WHITESPACE = " \t\n\f\r\v"; ///< Whitespace characters

// Convenience functions

bool equal_no_case(const std::string&, const std::string&);
bool find_no_case(const std::string&, const std::string&);

VecStr split(const std::string& source,
             const std::string& a_delimiterList = WHITESPACE,
             bool a_delimiterCompressOn = true);
VecStr explode(const std::string& source, const std::string& a_delimiterString);
std::string implode(const std::vector<std::string>& source, const std::string& delim);
int su_indexOfElem(const VecStr& a_container, const std::string& str);

std::string& left(std::string& a_source, size_t const a_length);
std::string left_copy(const std::string& a_source, size_t const a_length);

std::string& remove(std::string& str, char source);
std::string remove_copy(const std::string& str, char source);

std::string& replace(std::string& str, char source, char dest);
std::string& replace(std::string& str, const std::string& source, const std::string& dest);
std::string replace_copy(const std::string& str, char source, char dest);
std::string replace_copy(const std::string& str,
                         const std::string& source,
                         const std::string& dest);

std::string& right(std::string& a_source, size_t const a_length);
std::string right_copy(const std::string& a_source, size_t const a_length);

std::string su_simplified(const std::string& str);
bool su_iContains(const std::string& a_container, const std::string& a_substr);
bool su_vecContainsStr(const VecStr& a_container, const std::string& str);

std::string& to_lower(std::string& str);
std::string to_lower_copy(const std::string& str);
std::string& to_upper(std::string& str);
std::string to_upper_copy(const std::string& str);

std::string& trim(std::string& str, const std::string& delim = WHITESPACE);
std::string trim_copy(const std::string& str, const std::string& delim = WHITESPACE);
std::string& trim_left(std::string& str, const std::string& delim = WHITESPACE);
std::string& trim_right(std::string& str, const std::string& delim = WHITESPACE);

// Misc

unsigned int count_char(const std::string& str, char c);
bool numeric(const std::string& str);
bool sci_notation(const std::string& str, bool check_numeric = true);
void ChangeExtendedASCII(std::string& str, bool to_extended);
bool MakeUnique(const std::set<std::string>& set_str, std::string& str);
bool str2int(const std::string&, int& i, int base = 0);
bool str2dbl(const std::string&, double& d);

int Prec(double value, int& flags, int length = 15);

} // end namespace xus

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
  static_assert(std::is_integral<T>::value, "Not an integral (integer) type");
  a_n = ((flags & STR_SCIENTIFIC) ? -1 : 0);
  return STRstd((double)a_value, a_n, width, flags);
}

std::string STRstd(std::string a_value);

////////////////////////////////////////////////////////////////////////////////
class XmCommaNumpunct : public std::numpunct<char>
{
protected:
  virtual char do_thousands_sep() const;
  virtual std::string do_grouping() const;
}; // class XmCommaNumpunct

} // end namespace xms
