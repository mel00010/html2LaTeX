#!/bin/bash

set +o pipefail
mkdir -p ${WORKSPACE}/build/Analysis/CodeChecker/ClangSA
cat ${WORKSPACE}/.codechecker_skip | sed "s|*/PROJECT_DIR|${WORKSPACE}|" > ${WORKSPACE}/build/Analysis/CodeChecker/ClangSA/.codechecker_skip
cat ${WORKSPACE}/build/Analysis/CodeChecker/ClangSA/.codechecker_skip
${CODECHECKER_PATH}/_CodeChecker analyze "${WORKSPACE}/build/Analysis/tmp/ClangSA_CTU/compile_commands.json" \
  -j2 \
  --analyzers clangsa \
  --enable-all \
  --enable alpha \
  --ctu \
  -i ${WORKSPACE}/build/Analysis/CodeChecker/ClangSA/.codechecker_skip \
  --output ${WORKSPACE}/build/Analysis/CodeChecker/ClangSA/
