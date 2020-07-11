pipeline {
  agent any

  triggers {
    cron('H */16 * * *')  // Run every 16 hours
  } // triggers

  options {
    buildDiscarder(logRotator(numToKeepStr: '10'))
    skipDefaultCheckout()
    ansiColor('xterm')
  } // options
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
    booleanParam( name: 'RUN_TESTS',
                  defaultValue: true,
                  description: 'Run tests?')
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
    booleanParam( name: 'RUN_SONARCLOUD',
                  defaultValue: true,
                  description: 'Run SonarCloud scanner?')
    string( name: 'CODECHECKER_PATH',
            defaultValue: '/home/mel/codechecker/build/CodeChecker/bin/_CodeChecker',
            description: 'Path to CodeChecker executable')
    string( name: 'SOURCE_DIRECTORIES',
            defaultValue: 'src test',
            description: 'Directories to perform analysis on')
    string( name: 'REFERENCE_JOB',
            defaultValue: 'html2LaTeX/DOM_Interfaces',
            description: 'Reference job for warnings analysis')
  } // parameters

  stages {
    /**
     * Checkout source code from Github on any of the GIT nodes
     */
    stage('Checkout') {
      when {
        expression { params.DO_CHECKOUT == true }
      } // when
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
          ]], // extensions
          submoduleCfg: [],
          userRemoteConfigs: scm.userRemoteConfigs
        ]) // checkout
        stash(name: 'source_code',
              includes: '**/*')
        stash(name: 'dockerfiles',
              includes: 'Dockerfile.*')
      } // steps
    } // stage('Checkout')
    stage('Setup') {
      matrix {
        axes {
          axis {
            name 'COMPILER'
            values 'gcc', 'clang'
          } // axis
        } // axes
        stages {
          stage('BuildDockerFile') {
            agent any
            stages {
              stage('Setup') {
                steps {
                  unstash(name: 'dockerfiles')
                } // steps
              } // stage('Setup')
              stage('Build') {
                agent {
                  dockerfile {
                    filename "Dockerfile.${COMPILER}"
                    args '-v /var/lib/jenkins/tools/:/var/lib/jenkins/tools/'
                    reuseNode true
                  } // dockerfile
                } // agent
                steps {
                  echo "Building Docker image for ${COMPILER}"
                } // steps
              } // stage('Compile')
            } // stages
          } // stage('CompileDockerFile')
        } // stages
      } // matrix
    } // stage('Setup')
    stage('Build and Test') {
      matrix {
        axes {
          axis {
            name 'COMPILER'
            values 'gcc', 'clang'
          } // axis
          axis {
            name 'CONFIGURATION'
            values 'Debug', 'Release', 'RelWithDebInfo', 'Coverage'
          } // axis
          axis {
            name 'DISABLE_PCH'
            values 'True', 'False'
          } // axis
        } // axes
        when {
          expression { params.DO_BUILD == true }
        } // when
        stages {
          stage('SetupAndExecute') {
            agent any
            stages {
              stage('Setup') {
                steps {
                  unstash(name: 'dockerfiles')
                } // steps
              } // stage('Setup')
              stage('Execute') {
                agent {
                  dockerfile {
                    filename "Dockerfile.${COMPILER}"
                    args '-v /var/lib/jenkins/tools/:/var/lib/jenkins/tools/'
                    reuseNode true
                  } // dockerfile
                } // agent
                stages {
                  stage('Build') {
                    when {
                      expression { params.DO_BUILD == true }
                    } // when
                    steps {
                      unstash(name: 'source_code')
                      sh(script: """mkdir -p build/Analysis/CompilerOutput/${COMPILER}/""", label: 'Create build directory')
                      cmakeBuild( buildType: "${CONFIGURATION}",
                                  generator: 'Ninja',
                                  buildDir: "build/${COMPILER}/${CONFIGURATION}/DisablePCH_${DISABLE_PCH}/",
                                  cleanBuild: params.DO_CLEAN_BUILD,
                                  cmakeArgs: "-DDISABLE_PCH=${DISABLE_PCH}",
                                  installation: 'cmake-latest')
                      sh(script: """set +o pipefail ; \
                            ninja -j4 -C build/${COMPILER}/${CONFIGURATION}/DisablePCH_${DISABLE_PCH}/ all \
                            | tee build/Analysis/CompilerOutput/${COMPILER}/${CONFIGURATION}_DisablePCH_${DISABLE_PCH}.log""",
                            label: 'Compile')
                      stash(name: "Tests_${COMPILER}_${CONFIGURATION}_${DISABLE_PCH}",
                            includes: "build/${COMPILER}/${CONFIGURATION}/DisablePCH_${DISABLE_PCH}/test/tests")
                      stash(name: "CompilerOutput_${COMPILER}_${CONFIGURATION}_${DISABLE_PCH}",
                            includes: "build/Analysis/CompilerOutput/${COMPILER}/${CONFIGURATION}_DisablePCH_${DISABLE_PCH}.log",
                            allowEmpty: true)
                    } // steps
                  } // stage('Build')
                  stage('Test') {
                    when {
                      expression { params.RUN_TESTS == true}
                    } // when
                    steps {
                      unstash(name: "Tests_${COMPILER}_${CONFIGURATION}_${DISABLE_PCH}")
                      sh(script: """build/${COMPILER}/${CONFIGURATION}/DisablePCH_${DISABLE_PCH}/test/tests \
                          --gtest_output=xml:build/TestReports/${COMPILER}_${CONFIGURATION}_DisablePCH_${DISABLE_PCH}/""",
                          label: 'Run Tests')
                      stash(name: "TestReports_${COMPILER}_${CONFIGURATION}_${DISABLE_PCH}",
                            includes: "build/TestReports/${COMPILER}_${CONFIGURATION}_DisablePCH_${DISABLE_PCH}/*")
                      stash(name: "TestCoverageData_${COMPILER}_${CONFIGURATION}_${DISABLE_PCH}",
                            includes: "build/${COMPILER}/${CONFIGURATION}/DisablePCH_${DISABLE_PCH}/test/")
                    } // steps
                    post {
                      always {
                        unstash(name: "TestReports_${COMPILER}_${CONFIGURATION}_${DISABLE_PCH}")
                        xunit (
                          thresholds: [ skipped(failureThreshold: '0'),
                                        failed(failureThreshold: '0') ],
                          tools: [ GoogleTest(pattern: """build/TestReports/${COMPILER}_${CONFIGURATION}_DisablePCH_${DISABLE_PCH}/*.xml""") ]
                        )
                      } // always
                    } // post
                  } // stage('Test')
                  stage('Valgrind') {
                    when {
                      expression { params.RUN_ANALYSIS == true && params.RUN_VALGRIND == true}
                    } // when
                    steps {
                      unstash(name: "Tests_${COMPILER}_${CONFIGURATION}_${DISABLE_PCH}")
                      sh(script: 'mkdir -p build/Analysis/Valgrind', label: 'Create Analysis Directory')
                      sh(script: """valgrind \
                            --log-file=build/Analysis/Valgrind/valgrind-${COMPILER}_${CONFIGURATION}_DisablePCH_${DISABLE_PCH}-%p.log \
                            -s \
                            --leak-check=full \
                            --show-leak-kinds=all \
                            build/${COMPILER}/${CONFIGURATION}/DisablePCH_${DISABLE_PCH}/test/tests""",
                            label: 'Run Valgrind')
                      stash(name: "ValgrindResults_${COMPILER}_${CONFIGURATION}_${DISABLE_PCH}",
                            includes: "build/Analysis/Valgrind/valgrind-${COMPILER}_${CONFIGURATION}_DisablePCH_${DISABLE_PCH}-*.log",
                            allowEmpty: true)
                    } // steps
                  } // stage('Valgrind')
                  stage('Coverage') {
                    when {
                      expression { params.RUN_COVERAGE == true && CONFIGURATION == 'Coverage' }
                    } // when
                    steps {
                      unstash(name: "TestCoverageData_${COMPILER}_${CONFIGURATION}_${DISABLE_PCH}")
                      sh(script: 'mkdir -p build/Analysis/Coverage', label: 'Create Analysis Directory')
                      sh(script: """gcovr -r . -x \
                            --object-directory=build/${COMPILER}/${CONFIGURATION}/DisablePCH_${DISABLE_PCH}/test/ \
                            > build/Analysis/Coverage/report-${COMPILER}_${CONFIGURATION}_DisablePCH_${DISABLE_PCH}.xml""",
                            label: 'Run GCovR')
                      stash(name: "CoverageResults_${COMPILER}_${CONFIGURATION}_${DISABLE_PCH}",
                            includes: "build/Analysis/Coverage/report-${COMPILER}_${CONFIGURATION}_DisablePCH_${DISABLE_PCH}.xml",
                            allowEmpty: true)
                    } // steps
                  } // stage('Coverage')
                } // stages
              } // stage('Execute')
            } // stages
          } // stage('SetupAndExecute')
        } // stages
      } // matrix
      post {
        success {
          catchError(buildResult: null, stageResult: null) { unstash(name: "CompilerOutput_gcc_Debug_True")              }
          catchError(buildResult: null, stageResult: null) { unstash(name: "CompilerOutput_gcc_Debug_False")             }
          catchError(buildResult: null, stageResult: null) { unstash(name: "CompilerOutput_gcc_Release_True")            }
          catchError(buildResult: null, stageResult: null) { unstash(name: "CompilerOutput_gcc_Release_False")           }
          catchError(buildResult: null, stageResult: null) { unstash(name: "CompilerOutput_gcc_RelWithDebInfo_True")     }
          catchError(buildResult: null, stageResult: null) { unstash(name: "CompilerOutput_gcc_RelWithDebInfo_False")    }
          catchError(buildResult: null, stageResult: null) { unstash(name: "CompilerOutput_gcc_Coverage_True")           }
          catchError(buildResult: null, stageResult: null) { unstash(name: "CompilerOutput_gcc_Coverage_False")          }
          catchError(buildResult: null, stageResult: null) { unstash(name: "CompilerOutput_clang_Debug_True")            }
          catchError(buildResult: null, stageResult: null) { unstash(name: "CompilerOutput_clang_Debug_False")           }
          catchError(buildResult: null, stageResult: null) { unstash(name: "CompilerOutput_clang_Release_True")          }
          catchError(buildResult: null, stageResult: null) { unstash(name: "CompilerOutput_clang_Release_False")         }
          catchError(buildResult: null, stageResult: null) { unstash(name: "CompilerOutput_clang_RelWithDebInfo_True")   }
          catchError(buildResult: null, stageResult: null) { unstash(name: "CompilerOutput_clang_RelWithDebInfo_False")  }
          catchError(buildResult: null, stageResult: null) { unstash(name: "CompilerOutput_clang_Coverage_True")         }
          catchError(buildResult: null, stageResult: null) { unstash(name: "CompilerOutput_clang_Coverage_False")        }
          catchError(buildResult: null, stageResult: null) { unstash(name: "CoverageResults_gcc_Debug_True")             }
          catchError(buildResult: null, stageResult: null) { unstash(name: "CoverageResults_gcc_Debug_False")            }
          catchError(buildResult: null, stageResult: null) { unstash(name: "CoverageResults_gcc_Release_True")           }
          catchError(buildResult: null, stageResult: null) { unstash(name: "CoverageResults_gcc_Release_False")          }
          catchError(buildResult: null, stageResult: null) { unstash(name: "CoverageResults_gcc_RelWithDebInfo_True")    }
          catchError(buildResult: null, stageResult: null) { unstash(name: "CoverageResults_gcc_RelWithDebInfo_False")   }
          catchError(buildResult: null, stageResult: null) { unstash(name: "CoverageResults_gcc_Coverage_True")          }
          catchError(buildResult: null, stageResult: null) { unstash(name: "CoverageResults_gcc_Coverage_False")         }
          catchError(buildResult: null, stageResult: null) { unstash(name: "CoverageResults_clang_Debug_True")           }
          catchError(buildResult: null, stageResult: null) { unstash(name: "CoverageResults_clang_Debug_False")          }
          catchError(buildResult: null, stageResult: null) { unstash(name: "CoverageResults_clang_Release_True")         }
          catchError(buildResult: null, stageResult: null) { unstash(name: "CoverageResults_clang_Release_False")        }
          catchError(buildResult: null, stageResult: null) { unstash(name: "CoverageResults_clang_RelWithDebInfo_True")  }
          catchError(buildResult: null, stageResult: null) { unstash(name: "CoverageResults_clang_RelWithDebInfo_False") }
          catchError(buildResult: null, stageResult: null) { unstash(name: "CoverageResults_clang_Coverage_True")        }
          catchError(buildResult: null, stageResult: null) { unstash(name: "CoverageResults_clang_Coverage_False")       }
          catchError(buildResult: null, stageResult: null) { unstash(name: "TestReports_gcc_Debug_True")                 }
          catchError(buildResult: null, stageResult: null) { unstash(name: "TestReports_gcc_Debug_False")                }
          catchError(buildResult: null, stageResult: null) { unstash(name: "TestReports_gcc_Release_True")               }
          catchError(buildResult: null, stageResult: null) { unstash(name: "TestReports_gcc_Release_False")              }
          catchError(buildResult: null, stageResult: null) { unstash(name: "TestReports_gcc_RelWithDebInfo_True")        }
          catchError(buildResult: null, stageResult: null) { unstash(name: "TestReports_gcc_RelWithDebInfo_False")       }
          catchError(buildResult: null, stageResult: null) { unstash(name: "TestReports_gcc_Coverage_True")              }
          catchError(buildResult: null, stageResult: null) { unstash(name: "TestReports_gcc_Coverage_False")             }
          catchError(buildResult: null, stageResult: null) { unstash(name: "TestReports_clang_Debug_True")               }
          catchError(buildResult: null, stageResult: null) { unstash(name: "TestReports_clang_Debug_False")              }
          catchError(buildResult: null, stageResult: null) { unstash(name: "TestReports_clang_Release_True")             }
          catchError(buildResult: null, stageResult: null) { unstash(name: "TestReports_clang_Release_False")            }
          catchError(buildResult: null, stageResult: null) { unstash(name: "TestReports_clang_RelWithDebInfo_True")      }
          catchError(buildResult: null, stageResult: null) { unstash(name: "TestReports_clang_RelWithDebInfo_False")     }
          catchError(buildResult: null, stageResult: null) { unstash(name: "TestReports_clang_Coverage_True")            }
          catchError(buildResult: null, stageResult: null) { unstash(name: "TestReports_clang_Coverage_False")           }
          catchError(buildResult: null, stageResult: null) { unstash(name: "ValgrindResults_gcc_Debug_True")             }
          catchError(buildResult: null, stageResult: null) { unstash(name: "ValgrindResults_gcc_Debug_False")            }
          catchError(buildResult: null, stageResult: null) { unstash(name: "ValgrindResults_gcc_Release_True")           }
          catchError(buildResult: null, stageResult: null) { unstash(name: "ValgrindResults_gcc_Release_False")          }
          catchError(buildResult: null, stageResult: null) { unstash(name: "ValgrindResults_gcc_RelWithDebInfo_True")    }
          catchError(buildResult: null, stageResult: null) { unstash(name: "ValgrindResults_gcc_RelWithDebInfo_False")   }
          catchError(buildResult: null, stageResult: null) { unstash(name: "ValgrindResults_gcc_Coverage_True")          }
          catchError(buildResult: null, stageResult: null) { unstash(name: "ValgrindResults_gcc_Coverage_False")         }
          catchError(buildResult: null, stageResult: null) { unstash(name: "ValgrindResults_clang_Debug_True")           }
          catchError(buildResult: null, stageResult: null) { unstash(name: "ValgrindResults_clang_Debug_False")          }
          catchError(buildResult: null, stageResult: null) { unstash(name: "ValgrindResults_clang_Release_True")         }
          catchError(buildResult: null, stageResult: null) { unstash(name: "ValgrindResults_clang_Release_False")        }
          catchError(buildResult: null, stageResult: null) { unstash(name: "ValgrindResults_clang_RelWithDebInfo_True")  }
          catchError(buildResult: null, stageResult: null) { unstash(name: "ValgrindResults_clang_RelWithDebInfo_False") }
          catchError(buildResult: null, stageResult: null) { unstash(name: "ValgrindResults_clang_Coverage_True")        }
          catchError(buildResult: null, stageResult: null) { unstash(name: "ValgrindResults_clang_Coverage_False")       }

          stash(name: 'CompilerOutput',
                includes: 'build/Analysis/CompilerOutput/**/*.log',
                allowEmpty: true)
          stash(name: 'CoverageResults',
                includes: 'build/Analysis/Coverage/*.xml',
                allowEmpty: true)
          stash(name: 'ValgrindResults',
                includes: 'build/Analysis/Valgrind/*.log',
                allowEmpty: true)
          stash(name: 'TestReports',
                includes: 'build/TestReports/**/*.xml',
                allowEmpty: true)
        } // success
      } // post
    } // stage('Build and Test')

    stage('Analysis') {
      when {
        expression { params.RUN_ANALYSIS == true }
      }
      stages {
        stage('Setup') {
          steps {
            cmakeBuild( buildType: 'Debug',
                        generator: 'Ninja',
                        buildDir: 'build/DebugNoPCH',
                        cleanBuild: params.DO_CLEAN_BUILD,
                        cmakeArgs: '-DDISABLE_PCH=True',
                        installation: 'cmake-latest')
            stash(name: 'DebugNoPCHCompDBase',
                  includes: 'build/DebugNoPCH/compile_commands.json')
            sh(script: '''curl --create-dirs -sSLo .sonar/build-wrapper-linux-x86.zip \
                  https://sonarcloud.io/static/cpp/build-wrapper-linux-x86.zip''',
                  label: 'Fetch Sonar Build Wrapper')
            sh(script: 'unzip -o .sonar/build-wrapper-linux-x86.zip -d .sonar/', label: 'Unzip Sonar Build Wrapper')
            sh(script: '''.sonar/build-wrapper-linux-x86/build-wrapper-linux-x86-64 \
                  --out-dir build/BuildWrapper \
                  ninja -j4 -C build/DebugNoPCH all''',
                  label: 'Build with Sonar Build Wrapper')
          } // steps
        } // stage('Setup')
        stage('CodeChecker ClangSA CTU') {
          when {
            expression { params.RUN_CLANGSA_CTU == true && params.DO_BUILD == true}
          } // when

          steps {
            unstash(name: 'DebugNoPCHCompDBase')
            sh(script: 'mkdir -p build/Analysis/CodeChecker/ClangSA', label: 'Create Analysis Directory')
            sh(script: """set +o pipefail ; \
                  cat .codechecker_skip | sed "s|*/PROJECT_DIR|${WORKSPACE}|" \
                > build/Analysis/CodeChecker/ClangSA/.codechecker_skip""")
            sh(script: """${CODECHECKER_PATH} analyze \
                  "build/DebugNoPCH/compile_commands.json" \
                  -j2 \
                  --analyzers clangsa \
                  --enable-all \
                  --enable alpha \
                  --ctu \
                  -i build/Analysis/CodeChecker/ClangSA/.codechecker_skip \
                  --output build/Analysis/CodeChecker/ClangSA/""", label: 'Run ClangSA')
            stash(name: 'CodeCheckerClangSA_CTUResults',
                  includes: 'build/Analysis/CodeChecker/ClangSA/*.plist')
          } // steps
        } // stage('CodeChecker ClangSA CTU')
        stage('CodeChecker ClangSA') {
          when {
            expression { params.RUN_CLANGSA == true && params.DO_BUILD == true}
          } // when
          steps {
            unstash(name: 'DebugNoPCHCompDBase')
            sh(script: 'mkdir -p build/Analysis/CodeChecker/ClangSA', label: 'Create Analysis Directory')
            sh(script: """set +o pipefail ; \
                  cat .codechecker_skip | sed "s|*/PROJECT_DIR|${WORKSPACE}|" \
                > build/Analysis/CodeChecker/ClangSA/.codechecker_skip""")
            sh(script: """${CODECHECKER_PATH} analyze \
                  "build/DebugNoPCH/compile_commands.json" \
                  -j6 \
                  --analyzers clangsa \
                  --enable-all \
                  --enable alpha \
                  -i build/Analysis/CodeChecker/ClangSA/.codechecker_skip \
                  --output build/Analysis/CodeChecker/ClangSA/""", label: 'Run ClangSA')
            stash(name: 'CodeCheckerClangSAResults',
                  includes: 'build/Analysis/CodeChecker/ClangSA/*.plist')
          } // steps
        } // stage('CodeChecker ClangSA')
        stage('CodeChecker ClangTidy') {
          when {
            expression { params.RUN_CLANGTIDY == true && params.DO_BUILD == true}
          } // when
          steps {
            unstash(name: 'DebugNoPCHCompDBase')
            sh(script: 'mkdir -p build/Analysis/CodeChecker/ClangTidy', label: 'Create Analysis Directory')
            sh(script: """set +o pipefail ; \
                  cat .codechecker_skip | sed "s|*/PROJECT_DIR|${WORKSPACE}|" \
                > build/Analysis/CodeChecker/ClangTidy/.codechecker_skip""")
            sh(script: """${CODECHECKER_PATH} analyze \
                  "build/DebugNoPCH/compile_commands.json" \
                  -j6 \
                  --analyzers clang-tidy \
                  --enable-all \
                  -i build/Analysis/CodeChecker/ClangTidy/.codechecker_skip \
                  --output build/Analysis/CodeChecker/ClangTidy/""", label: 'Run ClangTidy')
            stash(name: 'CodeCheckerClangTidyResults',
                  includes: 'build/Analysis/CodeChecker/ClangTidy/*.plist')
           } // steps
        } // stage('CodeChecker ClangTidy')
        stage('CppCheck') {
          when {
            expression { params.RUN_CPPCHECK == true && params.DO_BUILD == true}
          } // when
          steps {
            unstash(name: 'DebugNoPCHCompDBase')
            sh(script: 'mkdir -p build/Analysis/CppCheck')
            sh(script: """cppcheck \
                  -j6 \
                  --project=build/DebugNoPCH/compile_commands.json \
                  -i"${WORKSPACE}/build" \
                  --xml \
                  --xml-version=2 \
                  --enable=all \
                  --language=c++ 2> build/Analysis/CppCheck/cppcheck.xml""", label: 'Run CppCheck')
            stash(name: 'CppCheckResults',
                  includes: 'build/Analysis/CppCheck/cppcheck.xml')
          } // steps
        } // stage('CppCheck')
        stage('Infer') {
          when {
            expression { params.RUN_INFER == true && params.DO_BUILD == true}
          } // when
          steps {
            unstash(name: 'DebugNoPCHCompDBase')
            sh(script: 'mkdir -p build/Analysis/Infer', label: 'Create Analysis Directory')
            sh(script: '''infer run \
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
                  --pmd-xml \
                  --results-dir build/Analysis/Infer''', label: 'Run FBInfer')
            stash(name: 'InferResults',
                  includes: 'build/Analysis/Infer/report.json')
          } // steps
        } // stage('Infer')
        stage('Vera++') {
          when {
            expression { params.RUN_VERA == true }
          } // when
          steps {
            sh(script: 'mkdir -p build/Analysis/VeraPlusPlus', label: 'Create Analysis Directory')
            sh(script: '''set +o pipefail ; \
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
                | vera++ --xml-report build/Analysis/VeraPlusPlus/report.xml''',
              label: 'Run Vera++')
            stash(name: 'VeraResults',
                  includes: 'build/Analysis/VeraPlusPlus/report.xml')
          } // steps
        } // stage('Vera++')
        stage('RATS') {
          when {
            expression { params.RUN_RATS == true }
          } // when
          steps {
            sh(script: 'mkdir -p build/Analysis/RATS', label: 'Create Analysis Directory')
            sh(script: """rats ${SOURCE_DIRECTORIES} --xml \
                  1> build/Analysis/RATS/report.xml""", label: 'Run RATS')
            stash(name: 'RATSResults',
                  includes: 'build/Analysis/RATS/report.xml')
          } // steps
        } // stage('RATS')
        stage('SonarQube analysis') {
          when {
            expression { params.RUN_SONARQUBE == true }
          } // when
          steps {
            catchError(buildResult: null, stageResult: null) { unstash(name: 'DebugNoPCHCompDBase')           }
            catchError(buildResult: null, stageResult: null) { unstash(name: 'CompilerOutput')                }
            catchError(buildResult: null, stageResult: null) { unstash(name: 'TestReports')                   }
            catchError(buildResult: null, stageResult: null) { unstash(name: 'CodeCheckerClangSAResults')     }
            catchError(buildResult: null, stageResult: null) { unstash(name: 'CodeCheckerClangSA_CTUResults') }
            catchError(buildResult: null, stageResult: null) { unstash(name: 'CodeCheckerClangTidyResults')   }
            catchError(buildResult: null, stageResult: null) { unstash(name: 'CppCheckResults')               }
            catchError(buildResult: null, stageResult: null) { unstash(name: 'InferResults')                  }
            catchError(buildResult: null, stageResult: null) { unstash(name: 'ValgrindResults')               }
            catchError(buildResult: null, stageResult: null) { unstash(name: 'VeraResults')                   }
            catchError(buildResult: null, stageResult: null) { unstash(name: 'RATSResults')                   }
            catchError(buildResult: null, stageResult: null) { unstash(name: 'CoverageResults')               }
            unstash(name: 'source_code')

            script {
              def scannerHome = tool 'sonar-scanner';
              withSonarQubeEnv('SonarQube') {
                sh(script: "${scannerHome}/bin/sonar-scanner -Dproject.settings=sonarqube.properties", label: 'Run SonarScanner')
              } // withSonarQubeEnv
            } // script
          } // steps
        } // stage('SonarQube analysis')
        stage('SonarCloud analysis') {
          when {
            expression { params.RUN_SONARCLOUD == true }
          } // when
          steps {
            catchError(buildResult: null, stageResult: null) { unstash(name: 'CompilerOutput')                }
            catchError(buildResult: null, stageResult: null) { unstash(name: 'TestReports')                   }
            catchError(buildResult: null, stageResult: null) { unstash(name: 'CoverageResults')               }
            unstash(name: 'source_code')

            script {
              def scannerHome = tool 'sonar-scanner';
              withSonarQubeEnv('SonarCloud') {
                sh(script: "${scannerHome}/bin/sonar-scanner -Dproject.settings=sonarcloud.properties", label: 'Run SonarScanner')
              } // withSonarQubeEnv
            } // script
          } // steps
        } // stage('SonarCloud analysis')
      } // stages
      post {
        always {
          catchError(buildResult: null, stageResult: null) { unstash(name: 'CompilerOutput')                }
          catchError(buildResult: null, stageResult: null) { unstash(name: 'CodeCheckerClangSAResults')     }
          catchError(buildResult: null, stageResult: null) { unstash(name: 'CodeCheckerClangSA_CTUResults') }
          catchError(buildResult: null, stageResult: null) { unstash(name: 'CodeCheckerClangTidyResults')   }
          catchError(buildResult: null, stageResult: null) { unstash(name: 'CppCheckResults')               }
          catchError(buildResult: null, stageResult: null) { unstash(name: 'InferResults')                  }
          recordIssues(
            enabledForFailure: true,
            referenceJobName: params.REFERENCE_JOB,
            tools: [
              [$class: 'Cmake'],
              cppCheck(pattern: 'build/Analysis/CppCheck/cppcheck.xml'),
              clang(pattern: 'build/Analysis/CompilerOutput/clang/*.log'),
              clangAnalyzer(pattern: 'build/Analysis/CodeChecker/ClangSA/*.plist'),
              clangTidy(pattern: 'build/Analysis/CodeChecker/ClangTidy/*.plist'),
              infer(pattern: 'build/Analysis/Infer/report.xml'),
              gcc3(pattern: 'build/Analysis/CompilerOutput/gcc/*.log')
            ] // tools
          ) // recordIssues
        } // always
      } // post
    } // stage('Analysis')
  } // stages
  post {
    cleanup {
      cleanWs()
    } // cleanup
  } // post
} // pipeline
