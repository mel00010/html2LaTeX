#!/bin/bash

mkdir -p build/Analysis/RATS
${RATS_PATH}/rats ${SOURCE_DIRECTORIES} --xml 1> build/Analysis/RATS/report.xml