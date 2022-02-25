//------------------------------------------------------------------------------
/// \copyright (C) Copyright Aquaveo 2022.
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 1. Precompiled header

// 2. My header
#include <xmscore/locale/locale.h>

// 3. Standard Library Headers
#include <string>

// 4. External Library Headers
#include <boost/locale.hpp>

// 5. Shared Headers

// 6. Non-shared Headers

namespace xms
{
namespace
{
boost::locale::generator* fg_generator = nullptr;

void iInitializeGenerator()
{
  if (fg_generator)
  {
    return;
  }

  auto manager = boost::locale::localization_backend_manager::global();
  manager.select("std");
  boost::locale::localization_backend_manager::global(manager);

  fg_generator = new boost::locale::generator(manager);
  std::locale::global(fg_generator->generate("en_US"));
} // iInitializeGenerator
} // anonymous namespace

//------------------------------------------------------------------------------
/// \brief Enable translation for the given domain.
/// \param a_domain: The domain of the messages to be translated. It is
///                  recommended to pass the macro LOCALE_DOMAIN for this.
/// \param a_messagesPath: Where to start looking for messages for this domain.
/// \note This must be called for each domain before using it with stTranslate
///       or the _() marker, or they will silently fail and return the original
///       untranslated message.
/// \note Translation dictionaries will be looked for at
///       `<a_messagesPath>/<locale name>/LC_MESSAGES/<a_domain>`.
///       E.g. if a_messagesPath="c:\path\to\messages" and a_domain="xmscore"
///       and the current locale is "en_US", then the dictionary at
///       `c:\path\to\messages\en_US\LC_MESSAGES\xmscore.mo` will be used to
///       translate messages in the xmscore domain.
//------------------------------------------------------------------------------
void stBindTextDomain(const std::string& a_domain, const std::string& a_messagesPath)
{
  iInitializeGenerator();

  fg_generator->add_messages_path(a_messagesPath);
  fg_generator->add_messages_domain(a_domain);
  std::locale::global(fg_generator->generate("en_US"));
} // stBindTextDomain

//------------------------------------------------------------------------------
/// \brief Translate a message from developer's language to user's language.
/// \param a_message: The message to translate.
/// \returns The translated version of the message if available, else the
///          same message passed in.
//------------------------------------------------------------------------------
std::string stTranslate(const char* a_message, const char* a_domain)
{
  iInitializeGenerator();

  return boost::locale::dgettext(a_domain, a_message);
} // stTranslate

} // namespace xms
