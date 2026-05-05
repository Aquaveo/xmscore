#pragma once
//------------------------------------------------------------------------------
/// \file
/// \brief String manipulation, parsing, and number-to-string formatting helpers.
/// \ingroup misc
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

// 6. Non-shared Headers

namespace xms
{
/// \brief Bitwise flags used by stPrecision() and the STRstd() formatters.
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
/// \class StTemp2DigitExponents
/// \brief RAII helper that switches MSVC's printf to two-digit exponents and restores it on destruction.
class StTemp2DigitExponents
{
public:
  /// \brief Switch to two-digit exponents for the lifetime of this object.
  StTemp2DigitExponents();
  /// \brief Restore the previous output format.
  ~StTemp2DigitExponents();

private:
  int m_oldOutputFormat; ///< Saved output format to restore to orignal value
};

inline constexpr const char ST_WHITESPACE[] = " \t\n\f\r\v"; ///< Whitespace characters

// Convenience functions

/// \brief Compare two strings ignoring case.
bool stEqualNoCase(const std::string&, const std::string&);
/// \brief Returns true if the second string occurs anywhere in the first, ignoring case.
bool stFindNoCase(const std::string&, const std::string&);

/// \brief Split source on any character in a_delimiterList; runs of delimiters are coalesced when a_delimiterCompressOn is true.
VecStr stSplit(const std::string& source,
               const std::string& a_delimiterList = ST_WHITESPACE,
               bool a_delimiterCompressOn = true);
/// \brief Split source on the exact a_delimiterString; empty fields are preserved.
VecStr stExplode(const std::string& source, const std::string& a_delimiterString);
/// \brief Concatenate source with delim between each element.
std::string stImplode(const std::vector<std::string>& source, const std::string& delim);
/// \brief Index of str within a_container, or -1 if not found.
int stIndexOfElem(const VecStr& a_container, const std::string& str);

/// \brief Truncate a_source to its first a_length characters in place; returns the same string.
std::string& stLeft(std::string& a_source, size_t const a_length);
/// \brief Return a copy of a_source truncated to its first a_length characters.
std::string stLeftCopy(const std::string& a_source, size_t const a_length);

/// \brief Remove every occurrence of source from str in place; returns the same string.
std::string& stRemove(std::string& str, char source);
/// \brief Return a copy of str with every occurrence of source removed.
std::string stRemoveCopy(const std::string& str, char source);

/// \brief Replace every occurrence of source with dest in str in place.
std::string& stReplace(std::string& str, char source, char dest);
/// \brief Replace every occurrence of source with dest in str in place.
std::string& stReplace(std::string& str, const std::string& source, const std::string& dest);
/// \brief Return a copy of str with every source character replaced by dest.
std::string stReplaceCopy(const std::string& str, char source, char dest);
/// \brief Return a copy of str with every source substring replaced by dest.
std::string stReplaceCopy(const std::string& str,
                          const std::string& source,
                          const std::string& dest);

/// \brief Truncate a_source to its last a_length characters in place; returns the same string.
std::string& stRight(std::string& a_source, size_t const a_length);
/// \brief Return a copy of a_source truncated to its last a_length characters.
std::string stRightCopy(const std::string& a_source, size_t const a_length);

/// \brief Return a copy of str with leading/trailing whitespace removed and internal runs of whitespace collapsed to a single space.
std::string stSimplified(const std::string& str);
/// \brief Returns true if a_substr appears anywhere in a_container.
bool stContains(const std::string& a_container, const std::string& a_substr);
/// \brief Returns true if a_container contains an exact match for str.
bool stVectorContainsString(const VecStr& a_container, const std::string& str);

/// \brief Lowercase str in place; returns the same string.
std::string& stToLower(std::string& str);
/// \brief Return a lowercase copy of str.
std::string stToLowerCopy(const std::string& str);
/// \brief Uppercase str in place; returns the same string.
std::string& stToUpper(std::string& str);
/// \brief Return an uppercase copy of str.
std::string stToUpperCopy(const std::string& str);

/// \brief Trim leading and trailing characters from delim out of str in place.
std::string& stTrim(std::string& str, const std::string& delim = ST_WHITESPACE);
/// \brief Return a copy of str with leading and trailing characters from delim removed.
std::string stTrimCopy(const std::string& str, const std::string& delim = ST_WHITESPACE);
/// \brief Trim leading characters from delim out of str in place.
std::string& stTrimLeft(std::string& str, const std::string& delim = ST_WHITESPACE);
/// \brief Trim trailing characters from delim out of str in place.
std::string& stTrimRight(std::string& str, const std::string& delim = ST_WHITESPACE);

// Misc

/// \brief Count occurrences of c in str.
unsigned int stCountChar(const std::string& str, char c);
/// \brief Returns true if str parses as a number (integer or floating point).
bool stNumeric(const std::string& str);
/// \brief Returns true if str is in scientific notation; if check_numeric is true, str must also be numeric.
bool stScientificNotation(const std::string& str, bool check_numeric = true);
/// \brief Convert str between extended-ASCII and the platform's narrow encoding in place.
void stChangeExtendedAscii(std::string& str, bool to_extended);
/// \brief If str is already in set_str, append or increment a ` (N)` suffix
///        until the result is not in set_str. The suffix shape is
///        space-paren-integer-paren (e.g. `foo` → `foo (2)`, `foo (2)` →
///        `foo (3)`); callers may parse it back out. Returns true if the
///        string was modified.
bool stMakeUnique(const std::set<std::string>& set_str, std::string& str);
/// \brief Parse a string as an int. Returns false on failure.
bool stStringToInt(const std::string&, int& i, int base = 0);
/// \brief Parse a string as a double. Returns false on failure.
bool stStringToDouble(const std::string&, double& d);

/// \brief Return the precision (digits) needed to round-trip value, also writing flags such as STR_SCIENTIFIC into the flags out-parameter.
int stPrecision(double value, int& flags, int length = 15);

// Number to string

/// \brief Format a double as a string using the given precision/width and PrecFlags bitmask.
std::string STRstd(double a_value, int a_n = -1, int width = 15, int flags = 0);
/// \brief Format a float as a string using the given precision/width and PrecFlags bitmask.
std::string STRstd(float a_value, int a_n = -1, int width = 15, int flags = 0);

//----- OVERLOAD ---------------------------------------------------------------
/// \brief Format an integral type (int, unsigned int, ...) as a std::string.
///
/// Ignores the precision argument (always 0) and only honors the
/// STR_SCIENTIFIC and STR_FULLWIDTH flags. This overload exists so that
/// callers from template code can pass any integer type without picking the
/// floating-point overload by mistake.
/// \param a_value The value to format.
/// \param a_n Ignored.
/// \param width Maximum number of characters (15 by default).
/// \param flags PrecFlags bitmask; see the double overload of STRstd().
/// \return The formatted string.
template <typename T>
inline std::string STRstd(T a_value, int a_n = 0, int width = 0, int flags = 0)
{
  static_assert(std::is_integral<T>::value, "Not an integral (integer) type");
  a_n = ((flags & STR_SCIENTIFIC) ? -1 : 0);
  return STRstd((double)a_value, a_n, width, flags);
}

/// \brief Pass-through overload that returns a_value unchanged; lets STRstd be called generically.
std::string STRstd(std::string a_value);

////////////////////////////////////////////////////////////////////////////////
/// \class StCommaNumpunct
/// \brief std::numpunct facet that groups thousands with commas; install on a stream's locale to format numbers like 1,234,567.
class StCommaNumpunct : public std::numpunct<char>
{
protected:
  /// \brief Returns ',' as the thousands separator.
  virtual char do_thousands_sep() const;
  /// \brief Returns the grouping pattern for thousands.
  virtual std::string do_grouping() const;
}; // class StCommaNumpunct

} // end namespace xms
