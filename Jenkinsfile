pipeline {
  agent any

  options {
    buildDiscarder(logRotator(numToKeepStr: '10'))
    skipDefaultCheckout()
  }
  parameters {
    booleanParam( name: 'DO_CHECKOUT',
                  defaultValue: true,
                  description: 'Perform a git checkout?')
    booleanParam( name: 'DO_BUILD',
                  defaultValue: true,
                  description: 'Perform a build?')
    booleanParam( name: 'DO_CLEAN_BUILD',
                  defaultValue: false,
                  description: 'Do a clean build?')
    booleanParam( name: 'RUN_TESTS',
                  defaultValue: true,
                  description: 'Run tests?')
    booleanParam( name: 'RUN_ANALYSIS',
                  defaultValue: true,
                  description: 'Run analysis?')
    booleanParam( name: 'RUN_CLANGSA_CTU',
                  defaultValue: false,
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
      steps {
        sh('mkdir -p build/Analysis/CompilerOutput')

        cmakeBuild( buildType: 'Release',
                    generator: 'Ninja',
                    buildDir: 'build/Release',
                    cleanBuild: params.DO_CLEAN_BUILD,
                    installation: 'cmake-3.17.3')
        sh('''ninja -C build/Release all \
              | tee build/Analysis/CompilerOutput/release.log''')
        stash name: 'ReleaseTests', includes: 'build/Release/test/tests'

        cmakeBuild( buildType: 'Debug',
                    generator: 'Ninja',
                    buildDir: 'build/Debug',
                    cleanBuild: params.DO_CLEAN_BUILD,
                    installation: 'cmake-3.17.3')
        sh('''ninja -C build/Debug all \
              | tee build/Analysis/CompilerOutput/debug.log''')
        stash name: 'DebugTests', includes: 'build/Debug/test/tests'

        cmakeBuild( buildType: 'Coverage',
                    generator: 'Ninja',
                    buildDir: 'build/Coverage',
                    cleanBuild: params.DO_CLEAN_BUILD,
                    installation: 'cmake-3.17.3')
        sh('''ninja -C build/Coverage all \
              | tee build/Analysis/CompilerOutput/coverage.log''')
        stash name: 'CoverageTests', includes: 'build/Coverage/test/tests'

        cmakeBuild( buildType: 'Debug',
                    generator: 'Ninja',
                    buildDir: 'build/DebugNoPCH',
                    cleanBuild: params.DO_CLEAN_BUILD,
                    cmakeArgs: '-DDISABLE_PCH=True',
                    installation: 'cmake-3.17.3')
        sh('''ninja -C build/DebugNoPCH all \
            | tee build/Analysis/CompilerOutput/debugnopch.log''')
        stash(name: 'DebugNoPCHTests',
              includes: 'build/DebugNoPCH/test/tests')
        stash(name: 'DebugNoPCHCompDBase',
              includes: 'build/DebugNoPCH/compile_commands.json')

        stash(name: 'CompilerOutput',
              includes: 'build/Analysis/CompilerOutput/*.log')
      }
    }

    stage('Test') {
      when {
        expression { params.RUN_TESTS == true }
      }
      parallel {
        stage('Test Release') {
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
        stage('Test DebugNoPCH') {
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
        stage('Test Coverage') {
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
      }
    }

    stage('Analysis') {
      when {
            expression { params.RUN_ANALYSIS == true }
      }
      stages {
        stage('CodeChecker ClangSA CTU') {
          when {
            expression { params.RUN_CLANGSA_CTU == true }
          }

          steps {
            unstash(name: 'DebugNoPCHCompDBase')
            sh('mkdir -p build/Analysis/CodeChecker/ClangSA')
            sh("""cat .codechecker_skip | sed "s|*/GameEngine|${WORKSPACE}|" \
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
            expression { params.DO_CLANGSA == true }
          }
          steps {
            unstash(name: 'DebugNoPCHCompDBase')
            sh('mkdir -p build/Analysis/CodeChecker/ClangSA')
            sh("""cat .codechecker_skip | sed "s|*/GameEngine|${WORKSPACE}|" \
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
            expression { params.RUN_CLANGTIDY == true }
          }
          steps {
            unstash(name: 'DebugNoPCHCompDBase')
            sh('mkdir -p build/Analysis/CodeChecker/ClangTidy')
            sh("""cat .codechecker_skip | sed "s|*/GameEngine|${WORKSPACE}|" \
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
            expression { params.RUN_CPPCHECK == true }
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
            expression { params.RUN_INFER == true }
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
                  --pulse \
                  --quandary \
                  --quandaryBO \
                  --siof \
                  --starvation \
                  --siof-check-iostreams \
                  --bufferoverrun \
                  --liveness \
                  --biabduction \
                  --jobs 4 \
                  --results-dir build/Analysis/Infer''')
            stash(name: 'InferResults',
                  includes: 'build/Analysis/Infer/report.json')
          }
        }
        stage('Valgrind') {
          when {
            expression { params.RUN_VALGRIND == true }
          }
          steps {
            unstash(name: 'ReleaseTests')
            unstash(name: 'DebugTests')
            sh('mkdir -p build/Analysis/Valgrind')
            sh('''valgrind \
                  --log-file=build/Analysis/Valgrind/valgrind-%p.log \
                  -s \
                  --leak-check=full \
                  --show-leak-kinds=all \
                  build/Release/test/tests''')
            sh('''valgrind \
                  --log-file=build/Analysis/Valgrind/valgrind-%p.log \
                  -s \
                  --leak-check=full \
                  --show-leak-kinds=all \
                  build/Debug/test/tests''')
            stash(name: 'ValgrindResults',
                  includes: 'build/Analysis/Valgrind/*.log')
          }
        }
        stage('Vera++') {
          when {
            expression { params.RUN_VERA == true }
          }
          steps {
            sh('mkdir -p build/Analysis/VeraPlusPlus')
            sh('''find src samples test \
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
            sh('''rats src samples test --xml \
                  1> build/Analysis/RATS/report.xml''')
            stash(name: 'RATSResults',
                  includes: 'build/Analysis/RATS/report.xml')
          }
        }
        stage('Coverage') {
          when {
            expression { params.RUN_COVERAGE == true }
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
