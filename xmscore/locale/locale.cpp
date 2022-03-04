//------------------------------------------------------------------------------
/// \copyright (C) Copyright Aquaveo 2022.
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 1. Precompiled header

// 2. My header
#include <xmscore/locale/locale.h>

// 3. Standard Library Headers
#include <set>
#include <string>

// 4. External Library Headers
#include <boost/locale.hpp>

// 5. Shared Headers

// 6. Non-shared Headers

namespace xms
{
namespace
{
// From https://stackoverflow.com/a/38656045/15664362
// Allows comparing const char* in a std::set.
struct iLess
{
  bool operator()(const char* a, const char* b) const { return strcmp(a, b) < 0; }
};

std::locale fg_locale;
boost::locale::generator* fg_generator;
std::set<const char*, iLess> fg_domains;

void iInitializeGenerator()
{
  if (fg_generator)
  {
    return;
  }

  auto manager = boost::locale::localization_backend_manager::global();
  manager.select("std");

  fg_generator = new boost::locale::generator(manager);
  fg_locale = fg_generator->generate("en_US");
} // iInitializeGenerator
} // anonymous namespace

//------------------------------------------------------------------------------
/// \brief Add a path to search for messages.
/// \param a_messagesPath: The path to add.
/// \note This must be called before any use of the _() marker, or else it will
///       silently fail to modify the message.
/// \note Dictionaries will be looked for at
///       `<a_messagesPath>/<locale name>/LC_MESSAGES/<a_domain>`.
///       E.g. if a_messagesPath="c:\path\to\messages" and a_domain="xmscore"
///       and the current locale is "en_US", then the dictionary at
///       `c:\path\to\messages\en_US\LC_MESSAGES\xmscore.mo` will be used to
///       translate messages in the xmscore domain.
//------------------------------------------------------------------------------
void stAddMessagePath(const std::string& a_messagePath)
{
  iInitializeGenerator();

  fg_generator->add_messages_path(a_messagePath);
  fg_locale = fg_generator->generate("en_US");
} // stAddMessagePath

//------------------------------------------------------------------------------
/// \brief Translate a message from developer's language to user's language.
/// \param a_message: The message to translate.
/// \param a_domain: The domain being translated for.
/// \returns The translated version of the message if available, else the
///          same message passed in.
//------------------------------------------------------------------------------
std::string stTranslate(const char* a_message, const char* a_domain)
{
  iInitializeGenerator();

  if (fg_domains.count(a_domain) == 0)
  {
    fg_generator->add_messages_domain(a_domain);
    fg_locale = fg_generator->generate("en_US");
  }

  return boost::locale::dgettext(a_domain, a_message, fg_locale);
} // stTranslate

} // namespace xms

#if CXX_TEST
////////////////////////////////////////////////////////////////////////////////
// TESTS
////////////////////////////////////////////////////////////////////////////////

#include <xmscore/locale/locale.t.h>

#include <xmscore/testing/TestTools.h>

using namespace xms;

//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
void LocaleUnitTests::setUp()
{
  stAddMessagePath(LOCALE_ROOT);
} // LocaleUnitTests::testMarkedUntranslated

//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
void LocaleUnitTests::tearDown()
{
  iInitializeGenerator();

  fg_generator->clear_paths();
  fg_generator->clear_domains();
  fg_locale = fg_generator->generate("en_US");
} // LocaleUnitTests::testMarkedUntranslated

//------------------------------------------------------------------------------
/// \brief Translate a marked string with no translation.
//------------------------------------------------------------------------------
void LocaleUnitTests::testMarkedUntranslated()
{
  std::string expected =
    "This message should not be modified by documentation.\n"
    "It is used for testing marked messages with no modifications.\n"
    "Modifying it will cause tests to fail.\n";
  std::string translated =
    _("This message should not be modified by documentation.\n"
      "It is used for testing marked messages with no modifications.\n"
      "Modifying it will cause tests to fail.\n");

  TS_ASSERT(expected == translated);
} // LocaleUnitTests::testMarkedUntranslated

//------------------------------------------------------------------------------
/// \brief Translate a marked string with a translation.
//------------------------------------------------------------------------------
void LocaleUnitTests::testMarkedTranslated()
{
  std::string expected =
    "This message should not be modified by documentation.\n"
    "It is used for testing marked messages with a modification.\n"
    "Modifying it will cause tests to fail.\n"
    "Specifically, it will cause testMarkedTranslated to fail.\n";
  std::string translated =
    _("This message should not be modified by documentation.\n"
      "It is used for testing marked messages with a modification.\n"
      "Modifying it will cause tests to fail.\n");

  TS_ASSERT(expected == translated);
} // LocaleUnitTests::testMarkedTranslated

//------------------------------------------------------------------------------
/// \brief Translate an unmarked string.
//------------------------------------------------------------------------------
void LocaleUnitTests::testUnmarked()
{
  std::string expected =
    "This message should not be modified by documentation.\n"
    "It is used for testing modification of unmarked messages.\n"
    "Modifying it will cause tests to fail.\n";
  std::string translated = xms::stTranslate(
    "This message should not be modified by documentation.\n"
    "It is used for testing modification of unmarked messages.\n"
    "Modifying it will cause tests to fail.\n",
    "xmscorelib");

  TS_ASSERT(expected == translated);
} // LocaleUnitTests::testUnmarked

//------------------------------------------------------------------------------
/// \brief Translate a null-marked string.
//------------------------------------------------------------------------------
void LocaleUnitTests::testNullMarked()
{
  std::string expected =
    "This message should not be modified by documentation.\n"
    "It is used for testing modification of null-marked messages.\n"
    "Modifying it will cause tests to fail.\n";
  std::string translated =
    N_("This message should not be modified by documentation.\n"
       "It is used for testing modification of null-marked messages.\n"
       "Modifying it will cause tests to fail.\n");

  TS_ASSERT(expected == translated);
} // LocaleUnitTests::testNullMarked

#endif
