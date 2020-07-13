#!/bin/bash

set +o pipefail
mkdir -p build/Analysis/VeraPlusPlus
find ${SOURCE_DIRECTORIES} \
  -type f             \
  -name "*.cpp" -o    \
  -name "*.cxx" -o    \
  -name "*.c"   -o    \
  -name "*.cc"  -o    \
  -name "*.hpp" -o    \
  -name "*.hxx" -o    \
  -name "*.h"   -o    \
  -name "*.hh"  -o    \
  -name "*.tpp" -o    \
  -name "*.txx" -o    \
  -name "*.t"   -o    \
  -name "*.tt"        \
  | ${VERA_PATH}/vera++ --xml-report build/Analysis/VeraPlusPlus/report.xml