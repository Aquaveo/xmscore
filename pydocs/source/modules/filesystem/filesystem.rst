**********
filesystem
**********

The :mod:`xms.core.filesystem.filesystem` module provides cross-platform
helpers for working with files and directories. The functions are intentionally
thin wrappers around the standard library; their value is in normalizing
behavior across the XMS suite (consistent handling of relative paths,
trailing-separator differences between Windows and POSIX, and silent failure
modes used by callers that cannot afford to raise).

.. automodule:: xms.core.filesystem.filesystem
   :members:
