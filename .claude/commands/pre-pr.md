---
description: Run the full pre-PR validation gate (format, lint, build, tests)
allowed-tools: Bash, Read
---

Run in order, stopping on the first failure. Report pass/fail for each step.
Do not push or open a PR — that requires explicit approval.

1. /aquaveo-cpp:format
2. /aquaveo-python:format
3. /aquaveo-python:lint
4. /aquaveo-cpp:build
5. /aquaveo-cpp:test
6. /aquaveo-python:test-strict
7. !git status --short — confirm no collateral file changes outside the
   intended scope.

If anything fails, surface the failure verbatim and stop. Do not silently
"fix" lint or test failures — that is the whole point of running this gate.
