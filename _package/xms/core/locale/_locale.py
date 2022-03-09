from .. import locale
from .._xmscore.locale import translate


def add_domain(domain):
    """
    Allow importing the given domain from this module.

    E.g. after calling this function with `xmscore` you can do `from xms.core.locale import xmscore` and it will
    give you a translation function for the `xmscore` domain.

    Args:
        domain: The domain to add.
    """
    locale.__setattr__(domain, translate_for_domain(domain))


def n_(message):
    """
    Mark a message as untranslatable.

    Marking a string with the _() marker might not be appropriate in some cases, such as when the string is meant
    to be consumed by other code. Most parsers would get confused if you gave them improperly formatted input, for
    example, so some strings should be left unmarked.

    When a string is left unmarked, it becomes ambiguous whether it is unmarked because translation is inappropriate,
    or because someone forgot to mark it. Uninformed people might make false assumptions, or waste time trying to
    figure out whether it should be marked.

    Marking strings with this function indicates that you have thought about whether they should be translatable, and
    decided that they should *not* be translated. When you see a string marked with this function, it's probably safe
    to assume the string shouldn't be translated until you find proof otherwise.

    Args:
        message: A message to mark as untranslatable.

    Returns:
        The message, unmodified.
    """
    return message


def translate_for_domain(domain):
    """
    Get a translator for a particular domain.

    Having multiple code bases means they may have identical messages. It may be correct to translate them to the same
    thing, but we can't be sure. We instead group messages by code base, or "domain". Multiple domains can translate the
    same message in different ways.

    Translators returned by this function are callable objects that take an untranslated message as input, and return
    a translated message as output.

    Typical use will look something like:
    ```
    from xms.core.locale import translate_for_domain
    _ = translate_for_domain('xmscore')
    # later...
    print(_("There was an error. Please fix it. Thanks."))
    ```

    Args:
         domain: The name of the domain to translate for. Will generally be named for the code base, e.g. "xmscore" or
         "xmsgrid".

    Returns:
        A translator for the specified domain. The returned translator can be called with an untranslated message, and
        will return a translated version according to the translator's domain.
    """
    return lambda message: translate(message, domain)
