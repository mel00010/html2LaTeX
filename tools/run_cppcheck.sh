#!/bin/bash

mkdir -p build/Analysis/CppCheck
${CPPCHECK_PATH}/cppcheck \
  -j6 \
  --project=build/DebugNoPCH/compile_commands.json \
  -i"${WORKSPACE}/build" \
  --xml \
  --xml-version=2 \
  --enable=all \
  --language=c++ 2> build/Analysis/CppCheck/cppcheck.xml