#!/usr/bin/env bash
# PreToolUse hook: refuse edits to authoritative tool configs.
# Stops the "weaken the linter to silence the warning" anti-pattern.
# Fix the code, not the config.
#
# Note: this hook protects the *root* pyproject.toml (a tool config in
# many Python projects). It is unrelated to the _package/pyproject.toml
# case in block-generated-files.sh, which is a generated wheel manifest.
set -euo pipefail

command -v jq >/dev/null 2>&1 || exit 0

input=$(cat)
file_path=$(printf '%s' "$input" | jq -r '.tool_input.file_path // empty' 2>/dev/null || true)
[ -z "$file_path" ] && exit 0

# Bare-relative variants are required — see block-generated-files.sh.
case "$file_path" in
  */_clang-format|_clang-format \
  |*/.flake8|.flake8 \
  |*/setup.cfg|setup.cfg \
  |*/pyproject.toml|pyproject.toml)
    cat >&2 <<EOF
BLOCKED: $file_path is an authoritative tool config.
Don't relax the linter/formatter to silence a warning — fix the code.
If the config genuinely needs to change, ask Gage first.
EOF
    exit 2
    ;;
esac
exit 0
