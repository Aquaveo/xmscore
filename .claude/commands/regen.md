---
description: Regenerate CMakeLists.txt and conanfile.py from build.toml
allowed-tools: Bash
---

Regenerate the gitignored build files using a local-dev placeholder version.
99.99.99 is the convention used in this project for unreleased local builds —
the real version is injected from the git tag at release time.

!xmsconan_gen --version 99.99.99 build.toml

After it succeeds, run /aquaveo-cpp:validate-build to confirm the regen
matches the filesystem and report any drift.
