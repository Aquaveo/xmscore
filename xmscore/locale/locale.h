//------------------------------------------------------------------------------
/// \copyright (C) Copyright Aquaveo 2022.
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 1. Precompiled header

// 2. My header

// 3. Standard Library Headers
#include <string>

// 4. External Library Headers
#include <boost/locale.hpp>

// 5. Shared Headers

// 6. Non-shared Headers

namespace xms
{
//------------------------------------------------------------------------------
/// \brief Used by stFormat. Not for external use. Single parameter version.
/// \param a_formatter: A boost::locale::format to format with.
/// \param a_first: The parameter to insert.
//------------------------------------------------------------------------------
template <typename First>
void stFormatHelper(boost::locale::format& a_formatter, First& a_first)
{
  a_formatter % a_first;
} // stFormatHelper

//------------------------------------------------------------------------------
/// \brief Used by stFormat. Not for external use. Multiple parameter version.
/// \param a_formatter: A boost::locale::format to format with.
/// \param a_first: The first parameter to insert.
/// \param a_rest: One or more other parameters to insert.
//------------------------------------------------------------------------------
template <typename First, typename... Rest>
void stFormatHelper(boost::locale::format& a_formatter, First& a_first, Rest&... a_rest)
{
  a_formatter % a_first;
  stFormatHelper(a_formatter, a_rest...);
} // stFormatHelper

//------------------------------------------------------------------------------
/// \brief A convenience wrapper around boost::locale::format. Example:
///        Calling `stFormat(fmt, first, second, third)` is equivalent to
///        `(boost::locale::format(fmt) % first % second % third).str()`
/// \param a_format: A format string. Uses the boost::locale::format
///                  specification. See
///                  https://www.boost.org/doc/libs/1_74_0/libs/locale/doc/html/localized_text_formatting.html
///                  This string will have placeholders replaced.
/// \param a_first: An object to insert into the format string.
//------------------------------------------------------------------------------
template <typename First>
void stFormat(std::string& a_format, const First& a_first)
{
  boost::locale::format formatter(a_format);
  stFormatHelper(formatter, a_first);
  a_format = formatter.str();
} // stFormat

//------------------------------------------------------------------------------
/// \brief A multi-parameter overload.
/// \param a_format: A format string.
/// \param a_first: The first object to insert into the string.
/// \param a_rest: One or more other objects to be inserted into the string.
//------------------------------------------------------------------------------
template <typename First, typename... Rest>
void stFormat(std::string& a_format, const First& a_first, const Rest&... a_rest)
{
  boost::locale::format formatter(a_format);
  stFormatHelper(formatter, a_first, a_rest...);
  a_format = formatter.str();
} // stFormat

//------------------------------------------------------------------------------
/// \brief Same as stFormat, but using the C locale. Used for untranslatable
///        strings.
/// \param a_format: A format string.
/// \param a_first: An object to insert into the format string.
//------------------------------------------------------------------------------
template <typename First>
void stCFormat(std::string& a_format, const First& a_first)
{
  boost::locale::format formatter(a_format);
  stFormatHelper(formatter, a_first);
  a_format = formatter.str(std::locale("C"));
} // stCFormat

//------------------------------------------------------------------------------
/// \brief A multi-parameter overload.
/// \param a_format: A format string.
/// \param a_first: The first object to insert into the string.
/// \param a_rest: One or more other objects to be inserted into the string.
//------------------------------------------------------------------------------
template <typename First, typename... Rest>
void stCFormat(std::string& a_format, const First& a_first, const Rest&... a_rest)
{
  boost::locale::format formatter(a_format);
  stFormatHelper(formatter, a_first, a_rest...);
  a_format = formatter.str(std::locale("C"));
} // stCFormat

std::string stTranslate(const char* a_message, const char* a_domain);
void stBindTextDomain(const std::string& a_domain, const std::string& a_messagesPath);

// Used to mark string literals that can be translated. Returns the translated
// literal if available, or the original literal otherwise.
//
// Notes:
// - Translation will silently fail unless you first call stEnableTranslations
//   with the path to your translation files. It's recommended to call
//   stEnabletranslations from your main() function.
// - Only call this on string literals. Don't call it on results of function
//   calls; instead, have the function translate before returning.
// - If the string contains information known only at runtime, make it a
//   template. Use this to mark the template, then stFormat to fill it in.
// - Adjacent string literals are okay. Use them if the string is too long.
// - LOCALE_DOMAIN is a string used to disambiguate messages from multiple
//   programs and/or libraries. Define it to the name of your program or
//   library. E.g. `#define LOCALE_DOMAIN "some_library_name"`. It may be
//   easier to define this on the command line to the compiler than everywhere
//   you include this header.
//
// Examples:
// ```
// std::string message1 = _("A simple use case. This will be translated.");
//
// std::string message2 = _(
//   "This message is too long to all fit on one line.\n"
//   "It was broken up into multiple lines using adjacent string literals.\n"
//   "This is okay because the message extraction tool can understand it."
// );
//
// std::string message3 = _("This has {1} thing(s) known only at runtime.");
// stFormat(message3, n);
// showMessage(message3)
//
// std::string message4 = _(
//   "The heap is {1} percent corrupted.\n"
//   "We require that the heap is less than {2} percent corrupted.\n"
//   "Please fix at least {3} percent of the heap to continue.");
// stFormat(message4, corrupted, limit, limit-corrupted);
// showMessage(message4);
// ```
#define _(a_message) stTranslate(a_message, LOCALE_DOMAIN)

// Used to mark string literals that cannot be translated.
#define M_(a_message) a_message

} // namespace xms