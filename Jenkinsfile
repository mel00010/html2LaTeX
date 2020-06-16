pipeline {
  agent any

  triggers {
    cron('H */4 * * *')  // Run every 4 hours
  }

  options {
    buildDiscarder(logRotator(numToKeepStr: '10'))
    skipDefaultCheckout()
    ansiColor('xterm')
  }
  parameters {
    booleanParam( name: 'DO_CHECKOUT',
                  defaultValue: true,
                  description: 'Perform a git checkout?')
    booleanParam( name: 'DO_BUILD',
                  defaultValue: true,
                  description: 'Perform a build?')
    booleanParam( name: 'DO_CLEAN_BUILD',
                  defaultValue: true,
                  description: 'Do a clean build?')
    booleanParam( name: 'BUILD_RELEASE',
                  defaultValue: true,
                  description: 'Perform a build of the Release config?')
    booleanParam( name: 'BUILD_DEBUG',
                  defaultValue: true,
                  description: 'Perform a build of the Debug config?')
    booleanParam( name: 'BUILD_COVERAGE',
                  defaultValue: true,
                  description: 'Perform a build of the Coverage config?')
    booleanParam( name: 'BUILD_DEBUGNOPCH',
                  defaultValue: true,
                  description: 'Perform a build of the DebugNOPCH config?')
    booleanParam( name: 'RUN_TESTS',
                  defaultValue: true,
                  description: 'Run tests?')
    booleanParam( name: 'RUN_TESTS_RELEASE',
                  defaultValue: true,
                  description: 'Run tests for the Release config?')
    booleanParam( name: 'RUN_TESTS_DEBUG',
                  defaultValue: true,
                  description: 'Run tests for the Debug config?')
    booleanParam( name: 'RUN_TESTS_COVERAGE',
                  defaultValue: true,
                  description: 'Run tests for the Coverage config?')
    booleanParam( name: 'RUN_TESTS_DEBUGNOPCH',
                  defaultValue: true,
                  description: 'Run tests for the DebugNOPCH config?')
    booleanParam( name: 'RUN_ANALYSIS',
                  defaultValue: true,
                  description: 'Run analysis?')
    booleanParam( name: 'RUN_CLANGSA_CTU',
                  defaultValue: true,
                  description: 'Run Clang Static Analysis with Cross Translation Unit Analysis?')
    booleanParam( name: 'RUN_CLANGSA',
                  defaultValue: true,
                  description: 'Run Clang Static Analysis?')
    booleanParam( name: 'RUN_CLANGTIDY',
                  defaultValue: true,
                  description: 'Run Clang Tidy?')
    booleanParam( name: 'RUN_CPPCHECK',
                  defaultValue: true,
                  description: 'Run CppCheck?')
    booleanParam( name: 'RUN_INFER',
                  defaultValue: true,
                  description: 'Run Facebook Infer?')
    booleanParam( name: 'RUN_VALGRIND',
                  defaultValue: true,
                  description: 'Run Valgrind?')
    booleanParam( name: 'RUN_VERA',
                  defaultValue: true,
                  description: 'Run Vera++?')
    booleanParam( name: 'RUN_RATS',
                  defaultValue: true,
                  description: 'Run RATS?')
    booleanParam( name: 'RUN_COVERAGE',
                  defaultValue: true,
                  description: 'Run coverage report generation?')
    booleanParam( name: 'RUN_SONARQUBE',
                  defaultValue: true,
                  description: 'Run SonarQube scanner?')
    string( name: 'CODECHECKER_PATH',
            defaultValue: '/home/mel/codechecker/build/CodeChecker/bin/_CodeChecker',
            description: 'Path to CodeChecker executable')
    string( name: 'SOURCE_DIRECTORIES',
            defaultValue: 'src test',
            description: 'Directories to perform analysis on')
  }

  stages {
    /**
     * Checkout source code from Github on any of the GIT nodes
     */
    stage('Checkout') {
      when {
        expression { params.DO_CHECKOUT == true }
      }
      steps {
        checkout([
          $class: 'GitSCM',
          branches: scm.branches,
          doGenerateSubmoduleConfigurations: false,
          extensions: [[
            $class: 'SubmoduleOption',
            disableSubmodules: false,
            parentCredentials: true,
            recursiveSubmodules: true,
            reference: '',
            trackingSubmodules: false
          ]],
          submoduleCfg: [],
          userRemoteConfigs: scm.userRemoteConfigs
        ])
      }
    }
    stage('Build') {
      agent {
        dockerfile {
          args '-v /var/lib/jenkins/tools/:/var/lib/jenkins/tools/'
          reuseNode true
        }
      }
      when {
        expression { params.DO_BUILD == true }
      }
      stages {
        stage('Setup') {
          steps {
            sh('mkdir -p build/Analysis/CompilerOutput')
            cmakeBuild( buildType: 'Debug',
                        generator: 'Ninja',
                        buildDir: 'build/DebugNoPCH',
                        cleanBuild: params.DO_CLEAN_BUILD,
                        cmakeArgs: '-DDISABLE_PCH=True',
                        installation: 'cmake-3.17.3')
            stash(name: 'DebugNoPCHCompDBase',
                  includes: 'build/DebugNoPCH/compile_commands.json')
          }
        }
        stage('Build Release') {
          when {
            expression { params.BUILD_RELEASE == true }
          }
          steps {
            cmakeBuild( buildType: 'Release',
                        generator: 'Ninja',
                        buildDir: 'build/Release',
                        cleanBuild: params.DO_CLEAN_BUILD,
                        installation: 'cmake-3.17.3')
            sh('''ninja -C build/Release all \
                  | tee build/Analysis/CompilerOutput/Release.log''')
            stash name: 'ReleaseTests', includes: 'build/Release/test/tests'
          }
        }
        stage('Build Debug') {
          when {
            expression { params.BUILD_DEBUG == true }
          }
          steps {
            cmakeBuild( buildType: 'Debug',
                        generator: 'Ninja',
                        buildDir: 'build/Debug',
                        cleanBuild: params.DO_CLEAN_BUILD,
                        installation: 'cmake-3.17.3')
            sh('''ninja -C build/Debug all \
                  | tee build/Analysis/CompilerOutput/Debug.log''')
            stash name: 'DebugTests', includes: 'build/Debug/test/tests'
          }
        }
        stage('Build Coverage') {
          when {
            expression { params.BUILD_COVERAGE == true }
          }
          steps {
            cmakeBuild( buildType: 'Coverage',
                        generator: 'Ninja',
                        buildDir: 'build/Coverage',
                        cleanBuild: params.DO_CLEAN_BUILD,
                        installation: 'cmake-3.17.3')
            sh('''ninja -C build/Coverage all \
                  | tee build/Analysis/CompilerOutput/Coverage.log''')
            stash name: 'CoverageTests', includes: 'build/Coverage/test/tests'
          }
        }
        stage('Build DebugNoPCH') {
          when {
            expression { params.BUILD_DEBUGNOPCH == true }
          }
          steps {
            sh('''ninja -C build/DebugNoPCH all \
                | tee build/Analysis/CompilerOutput/DebugNoPCH.log''')
            stash(name: 'DebugNoPCHTests',
                  includes: 'build/DebugNoPCH/test/tests')
          }
        }
      }
      post {
        success {
          stash(name: 'CompilerOutput',
                includes: 'build/Analysis/CompilerOutput/*.log')
        }
      }
    }

    stage('Test') {
      when {
        expression { params.RUN_TESTS == true && params.DO_BUILD == true}
      }
      parallel {
        stage('Test Release') {
          when {
            expression { params.BUILD_RELEASE == true && params.RUN_TESTS_RELEASE == true}
          }
          steps {
            unstash(name: 'ReleaseTests')
            sh('build/Release/test/tests --gtest_output=xml:build/Release/reports/')
            stash(name: 'TestReleaseReports',
                  includes: 'build/Release/reports/*.xml')
          }
          post {
            always {
              xunit (
                thresholds: [ skipped(failureThreshold: '0'),
                              failed(failureThreshold: '0') ],
                tools: [ GoogleTest(pattern: 'build/Release/reports/*.xml') ]
              )
            }
          }
        }
        stage('Test Debug') {
          when {
            expression { params.BUILD_DEBUG == true && params.RUN_TESTS_DEBUG == true}
          }
          steps {
            unstash(name: 'DebugTests')
            sh('build/Debug/test/tests --gtest_output=xml:build/Debug/reports/')
            stash(name: 'TestDebugReports',
                  includes: 'build/Debug/reports/*.xml')
          }
          post {
            always {
              xunit (
                thresholds: [ skipped(failureThreshold: '0'),
                              failed(failureThreshold: '0') ],
                tools: [ GoogleTest(pattern: 'build/Debug/reports/*.xml') ]
              )
            }
          }
        }
        stage('Test Coverage') {
          when {
            expression { params.BUILD_COVERAGE == true && params.RUN_TESTS_COVERAGE == true}
          }
          steps {
            unstash(name: 'CoverageTests')
            sh('build/Coverage/test/tests --gtest_output=xml:build/Coverage/reports/')
            stash(name: 'TestCoverageReports',
                  includes: 'build/Coverage/reports/*.xml')
            stash(name: 'CoverageAnalysisData',
                  includes: 'build/Coverage/test/*')
          }
          post {
            always {
              xunit (
                thresholds: [ skipped(failureThreshold: '0'),
                              failed(failureThreshold: '0') ],
                tools: [ GoogleTest(pattern: 'build/Coverage/reports/*.xml') ]
              )
            }
          }
        }
        stage('Test DebugNoPCH') {
          when {
            expression { params.BUILD_DEBUGNOPCH == true && params.RUN_TESTS_DEBUGNOPCH == true}
          }
          steps {
            unstash(name: 'DebugNoPCHTests')
            sh('build/DebugNoPCH/test/tests --gtest_output=xml:build/DebugNoPCH/reports/')
            stash(name: 'TestDebugNoPCHReports',
                  includes: 'build/DebugNoPCH/reports/*.xml')
          }
          post {
            always {
              xunit (
                thresholds: [ skipped(failureThreshold: '0'),
                              failed(failureThreshold: '0') ],
                tools: [ GoogleTest(pattern: 'build/DebugNoPCH/reports/*.xml') ]
              )
            }
          }
        }
      }
    }

    stage('Analysis') {
      when {
        expression { params.RUN_ANALYSIS == true }
      }
      stages {
        stage('CodeChecker ClangSA CTU') {
          when {
            expression { params.RUN_CLANGSA_CTU == true && params.DO_BUILD == true}
          }

          steps {
            unstash(name: 'DebugNoPCHCompDBase')
            sh('mkdir -p build/Analysis/CodeChecker/ClangSA')
            sh("""cat .codechecker_skip | sed "s|*/PROJECT_DIR|${WORKSPACE}|" \
                > build/Analysis/CodeChecker/ClangSA/.codechecker_skip""")
            sh("""${CODECHECKER_PATH} analyze \
                  "build/DebugNoPCH/compile_commands.json" \
                  -j2 \
                  --analyzers clangsa \
                  --enable-all \
                  --enable alpha \
                  --ctu \
                  -i build/Analysis/CodeChecker/ClangSA/.codechecker_skip \
                  --output build/Analysis/CodeChecker/ClangSA/""")
            stash(name: 'CodeCheckerClangSA_CTUResults',
                  includes: 'build/Analysis/CodeChecker/ClangSA/*.plist')
          }
        }
        stage('CodeChecker ClangSA') {
          when {
            expression { params.RUN_CLANGSA == true && params.DO_BUILD == true}
          }
          steps {
            unstash(name: 'DebugNoPCHCompDBase')
            sh('mkdir -p build/Analysis/CodeChecker/ClangSA')
            sh("""cat .codechecker_skip | sed "s|*/PROJECT_DIR|${WORKSPACE}|" \
                > build/Analysis/CodeChecker/ClangSA/.codechecker_skip""")
            sh("""${CODECHECKER_PATH} analyze \
                  "build/DebugNoPCH/compile_commands.json" \
                  -j8 \
                  --analyzers clangsa \
                  --enable-all \
                  --enable alpha \
                  -i build/Analysis/CodeChecker/ClangSA/.codechecker_skip \
                  --output build/Analysis/CodeChecker/ClangSA/""")
            stash(name: 'CodeCheckerClangSAResults',
                  includes: 'build/Analysis/CodeChecker/ClangSA/*.plist')
          }
        }
        stage('CodeChecker ClangTidy') {
          when {
            expression { params.RUN_CLANGTIDY == true && params.DO_BUILD == true}
          }
          steps {
            unstash(name: 'DebugNoPCHCompDBase')
            sh('mkdir -p build/Analysis/CodeChecker/ClangTidy')
            sh("""cat .codechecker_skip | sed "s|*/PROJECT_DIR|${WORKSPACE}|" \
                > build/Analysis/CodeChecker/ClangTidy/.codechecker_skip""")
            sh("""${CODECHECKER_PATH} analyze \
                  "build/DebugNoPCH/compile_commands.json" \
                  -j8 \
                  --analyzers clang-tidy \
                  --enable-all \
                  -i build/Analysis/CodeChecker/ClangTidy/.codechecker_skip \
                  --output build/Analysis/CodeChecker/ClangTidy/""")
            stash(name: 'CodeCheckerClangTidyResults',
                  includes: 'build/Analysis/CodeChecker/ClangTidy/*.plist')
           }
        }
        stage('CppCheck') {
          when {
            expression { params.RUN_CPPCHECK == true && params.DO_BUILD == true}
          }
          steps {
            unstash(name: 'DebugNoPCHCompDBase')
            sh('mkdir -p build/Analysis/CppCheck')
            sh("""cppcheck \
                  -j8 \
                  --project=build/DebugNoPCH/compile_commands.json \
                  -i"${WORKSPACE}/build" \
                  --xml \
                  --enable=all \
                  --language=c++ 2> build/Analysis/CppCheck/cppcheck.xml""")
            //publishCppcheck( allowNoReport: true, ignoreBlankFiles: true, pattern: '**/cppcheck-result.xml')
            stash(name: 'CppCheckResults',
                  includes: 'build/Analysis/CppCheck/cppcheck.xml')
          }
        }
        stage('Infer') {
          when {
            expression { params.RUN_INFER == true && params.DO_BUILD == true}
          }
          steps {
            unstash(name: 'DebugNoPCHCompDBase')
            sh('mkdir -p build/Analysis/Infer')
            sh('''infer run \
                  --compilation-database build/DebugNoPCH/compile_commands.json \
                  --keep-going \
                  --skip-analysis-in-path build/ \
                  --skip-analysis-in-path-skips-compilation \
                  --cost \
                  --headers \
                  --loop-hoisting \
                  --purity \
                  --pulse \
                  --quandary \
                  --quandaryBO \
                  --siof \
                  --starvation \
                  --siof-check-iostreams \
                  --bufferoverrun \
                  --liveness \
                  --uninit \
                  --biabduction \
                  --jobs 4 \
                  --enable-issue-type ARRAY_OUT_OF_BOUNDS_L1 \
                  --enable-issue-type ARRAY_OUT_OF_BOUNDS_L2 \
                  --enable-issue-type ARRAY_OUT_OF_BOUNDS_L3 \
                  --enable-issue-type BUFFER_OVERRUN_L4 \
                  --enable-issue-type BUFFER_OVERRUN_L5 \
                  --enable-issue-type BUFFER_OVERRUN_U5 \
                  --enable-issue-type CLASS_CAST_EXCEPTION \
                  --enable-issue-type CLASS_CAST_EXCEPTION \
                  --enable-issue-type CONDITION_ALWAYS_FALSE \
                  --enable-issue-type CONDITION_ALWAYS_TRUE \
                  --enable-issue-type DANGLING_POINTER_DEREFERENCE \
                  --enable-issue-type DIVIDE_BY_ZERO \
                  --enable-issue-type EXPENSIVE_ALLOCATION \
                  --enable-issue-type EXPENSIVE_ALLOCATION_COLD_START \
                  --enable-issue-type EXPENSIVE_EXECUTION_TIME \
                  --enable-issue-type EXPENSIVE_EXECUTION_TIME_COLD_START \
                  --enable-issue-type EXPENSIVE_ALLOCATION_COLD_START \
                  --enable-issue-type GLOBAL_VARIABLE_INITIALIZED_WITH_FUNCTION_OR_METHOD_CALL \
                  --enable-issue-type INFINITE_ALLOCATION \
                  --enable-issue-type INFINITE_EXECUTION_TIME \
                  --enable-issue-type INTEGER_OVERFLOW_L5 \
                  --enable-issue-type INTEGER_OVERFLOW_U5 \
                  --enable-issue-type NULL_TEST_AFTER_DEREFERENCE \
                  --enable-issue-type RETURN_VALUE_IGNORED \
                  --enable-issue-type STACK_VARIABLE_ADDRESS_ESCAPE \
                  --enable-issue-type UNARY_MINUS_APPLIED_TO_UNSIGNED_EXPRESSION \
                  --enable-issue-type UNTRUSTED_BUFFER_ACCESS \
                  --enable-issue-type UNTRUSTED_HEAP_ALLOCATION \
                  --enable-issue-type ZERO_ALLOCATION \
                  --enable-issue-type ZERO_EXECUTION_TIME \
                  --type-size \
                  --uninit-interproc \
                  --no-hoisting-report-only-expensive \
                  --results-dir build/Analysis/Infer''')
            stash(name: 'InferResults',
                  includes: 'build/Analysis/Infer/report.json')
          }
        }
        stage('Valgrind') {
          when {
            expression { params.RUN_VALGRIND == true && params.DO_BUILD == true}
          }
          stages {
            stage('Valgrind Release') {
              when {
                expression { params.BUILD_RELEASE == true }
              }
              steps {
                unstash(name: 'ReleaseTests')
                sh('mkdir -p build/Analysis/Valgrind')
                sh('''valgrind \
                      --log-file=build/Analysis/Valgrind/valgrind-Release-%p.log \
                      -s \
                      --leak-check=full \
                      --show-leak-kinds=all \
                      build/Release/test/tests''')
              }
            }
            stage('Valgrind Debug') {
              when {
                expression { params.BUILD_DEBUG == true }
              }
              steps {
                unstash(name: 'DebugTests')
                sh('mkdir -p build/Analysis/Valgrind')
                sh('''valgrind \
                      --log-file=build/Analysis/Valgrind/valgrind-Debug-%p.log \
                      -s \
                      --leak-check=full \
                      --show-leak-kinds=all \
                      build/Debug/test/tests''')
              }
            }
            stage('Valgrind Coverage') {
              when {
                expression { params.BUILD_COVERAGE == true }
              }
              steps {
                unstash(name: 'CoverageTests')
                sh('mkdir -p build/Analysis/Valgrind')
                sh('''valgrind \
                      --log-file=build/Analysis/Valgrind/valgrind-Coverage-%p.log \
                      -s \
                      --leak-check=full \
                      --show-leak-kinds=all \
                      build/Debug/test/tests''')
              }
            }
            stage('Valgrind DebugNoPCH') {
              when {
                expression { params.BUILD_DEBUGNOPCH == true }
              }
              steps {
                unstash(name: 'DebugNoPCHTests')
                sh('mkdir -p build/Analysis/Valgrind')
                sh('''valgrind \
                      --log-file=build/Analysis/Valgrind/valgrind-DebugNoPCH-%p.log \
                      -s \
                      --leak-check=full \
                      --show-leak-kinds=all \
                      build/Debug/test/tests''')
              }
            }

          }
          post {
            success {
              stash(name: 'ValgrindResults',
                    includes: 'build/Analysis/Valgrind/*.log')
            }
          }
        }
        stage('Vera++') {
          when {
            expression { params.RUN_VERA == true }
          }
          steps {
            sh('mkdir -p build/Analysis/VeraPlusPlus')
            sh('''find ${SOURCE_DIRECTORIES} \
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
                | vera++ --xml-report build/Analysis/VeraPlusPlus/report.xml''')
            stash(name: 'VeraResults',
                  includes: 'build/Analysis/VeraPlusPlus/report.xml')
          }
        }
        stage('RATS') {
          when {
            expression { params.RUN_RATS == true }
          }
          steps {
            sh('mkdir -p build/Analysis/RATS')
            sh("""rats ${SOURCE_DIRECTORIES} --xml \
                  1> build/Analysis/RATS/report.xml""")
            stash(name: 'RATSResults',
                  includes: 'build/Analysis/RATS/report.xml')
          }
        }
        stage('Coverage') {
          when {
            expression { params.RUN_COVERAGE == true && params.BUILD_COVERAGE == true && params.RUN_TESTS_COVERAGE == true }
          }
          steps {
            unstash(name: 'CoverageAnalysisData')
            sh('mkdir -p build/Analysis/Coverage')
            sh('''gcovr -r . -x --object-directory=build/Coverage/test/ \
                  > build/Analysis/Coverage/report.xml''')
            stash(name: 'CoverageResults',
                  includes: 'build/Analysis/Coverage/report.xml')
          }
        }
        stage('SonarQube analysis') {
          when {
            expression { params.RUN_SONARQUBE == true }
          }
          steps {
            catchError(buildResult: null, stageResult: null) { unstash(name: 'DebugNoPCHCompDBase')           }
            catchError(buildResult: null, stageResult: null) { unstash(name: 'CompilerOutput')                }
            catchError(buildResult: null, stageResult: null) { unstash(name: 'TestReleaseReports')            }
            catchError(buildResult: null, stageResult: null) { unstash(name: 'TestDebugReports')              }
            catchError(buildResult: null, stageResult: null) { unstash(name: 'TestDebugNoPCHReports')         }
            catchError(buildResult: null, stageResult: null) { unstash(name: 'TestCoverageReports')           }
            catchError(buildResult: null, stageResult: null) { unstash(name: 'CodeCheckerClangSAResults')     }
            catchError(buildResult: null, stageResult: null) { unstash(name: 'CodeCheckerClangSA_CTUResults') }
            catchError(buildResult: null, stageResult: null) { unstash(name: 'CodeCheckerClangTidyResults')   }
            catchError(buildResult: null, stageResult: null) { unstash(name: 'CppCheckResults')               }
            catchError(buildResult: null, stageResult: null) { unstash(name: 'InferResults')                  }
            catchError(buildResult: null, stageResult: null) { unstash(name: 'ValgrindResults')               }
            catchError(buildResult: null, stageResult: null) { unstash(name: 'VeraResults')                   }
            catchError(buildResult: null, stageResult: null) { unstash(name: 'RATSResults')                   }
            catchError(buildResult: null, stageResult: null) { unstash(name: 'CoverageResults')               }

            script {
              def scannerHome = tool 'sonar-scanner';
              withSonarQubeEnv() {
                sh "${scannerHome}/bin/sonar-scanner"
              }
            }
          }
        }
      }
    }
  }
}
