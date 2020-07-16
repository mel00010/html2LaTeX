#!/bin/bash

set +o pipefail
mkdir -p build/Analysis/CodeChecker/ClangSA
cat .codechecker_skip | sed "s|*/PROJECT_DIR|${WORKSPACE}|" > build/Analysis/CodeChecker/ClangSA/.codechecker_skip
${CODECHECKER_PATH}/_CodeChecker analyze "build/Analysis/tmp/ClangSA/compile_commands.json" \
  -j2 \
  --analyzers clangsa \
  --enable-all \
  --enable alpha \
  --ctu \
  -i build/Analysis/CodeChecker/ClangSA/.codechecker_skip \
  --output build/Analysis/CodeChecker/ClangSA/
