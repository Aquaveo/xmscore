**********
filesystem
**********

The :mod:`xms.core.filesystem.filesystem` module provides cross-platform
helpers for working with files and directories. The functions are intentionally
thin wrappers around the standard library; their value is in normalizing
behavior across the XMS suite (consistent handling of relative paths and
trailing-separator differences between Windows and POSIX). Refer to each
function's docstring for the specific exceptions it raises or suppresses
and the sentinel value (if any) returned on failure.

.. automodule:: xms.core.filesystem.filesystem
   :members:
