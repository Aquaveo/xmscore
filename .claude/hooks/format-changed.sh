#!/usr/bin/env bash
# PostToolUse hook: format only the lines just changed.
# Whole-file reformats create noisy diffs and surface latent linter
# conflicts (Aquaveo strategy doc §06). Best-effort; never blocks.
set -euo pipefail

command -v jq >/dev/null 2>&1 || exit 0

input=$(cat)
file_path=$(printf '%s' "$input" | jq -r '.tool_input.file_path // empty' 2>/dev/null || true)
[ -z "$file_path" ] && exit 0
[ -f "$file_path" ] || exit 0

case "$file_path" in
  *.cpp|*.h|*.hpp|*.cc|*.cxx)
    if command -v clang-format-diff >/dev/null 2>&1; then
      git diff -U0 --no-color -- "$file_path" 2>/dev/null \
        | clang-format-diff -p1 -i -style=file 2>/dev/null || true
    fi
    ;;
  *.py)
    if command -v yapf >/dev/null 2>&1; then
      diff_output=$(git diff -U0 --no-color -- "$file_path" 2>/dev/null || true)
      yapf_args=()
      while IFS= read -r line; do
        if [[ "$line" =~ ^@@\ -[0-9,]+\ \+([0-9]+),?([0-9]*)\ @@ ]]; then
          start="${BASH_REMATCH[1]}"
          count="${BASH_REMATCH[2]:-1}"
          [ "$count" = "0" ] && continue
          end=$((start + count - 1))
          yapf_args+=("--lines=$start-$end")
        fi
      done <<< "$diff_output"
      if [ "${#yapf_args[@]}" -gt 0 ]; then
        yapf --in-place "${yapf_args[@]}" "$file_path" 2>/dev/null || true
      fi
    fi
    ;;
esac
exit 0
