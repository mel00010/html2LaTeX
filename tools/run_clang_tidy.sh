#!/bin/bash
set +o pipefail
mkdir -p ${WORKSPACE}/build/Analysis/CodeChecker/ClangTidy
cat ${WORKSPACE}/.codechecker_skip | sed "s|*/PROJECT_DIR|${WORKSPACE}|" > ${WORKSPACE}/build/Analysis/CodeChecker/ClangTidy/.codechecker_skip
cat ${WORKSPACE}/build/Analysis/CodeChecker/ClangTidy/.codechecker_skip
${CODECHECKER_PATH}/_CodeChecker analyze "${WORKSPACE}/build/Analysis/tmp/ClangTidy/compile_commands.json" \
  -j6 \
  --analyzers clang-tidy \
  --enable-all \
  -i ${WORKSPACE}/build/Analysis/CodeChecker/ClangTidy/.codechecker_skip \
  --output ${WORKSPACE}/build/Analysis/CodeChecker/ClangTidy/
