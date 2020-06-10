pipeline {
  agent any

  options {
    buildDiscarder(logRotator(numToKeepStr: '10'))
    skipDefaultCheckout()
  }
  parameters {
    string( name: 'CODECHECKER_PATH',
            defaultValue: '/home/mel/codechecker/build/CodeChecker/bin/_CodeChecker',
            description: 'Path to CodeChecker executable')
    booleanParam( name: 'DO_CLANGSA_CTU',
                  defaultValue: false,
                  description: 'Run Clang Static Analysis with Cross Translation Unit Analysis?')
    booleanParam( name: 'DO_CLEAN_BUILD',
                  defaultValue: false,
                  description: 'Do a clean build?')
  }

  stages {
    /**
     * Checkout source code from Github on any of the GIT nodes
     */
    stage('Checkout') {
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
      steps {
        sh('mkdir -p build/Analysis/CompilerOutput')

        cmakeBuild( buildType: 'Release',
                    generator: 'Ninja',
                    buildDir: 'build/Release',
                    cleanBuild: params.DO_CLEAN_BUILD,
                    installation: 'cmake-3.17.3')
        sh('''ninja -C build/Release all tests\
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
      stages {
        stage('CodeChecker ClangSA CTU') {
          when {
            expression { params.DO_CLANGSA_CTU == true }
          }

          steps {
            unstash(name: 'DebugNoPCHCompDBase')
            sh('mkdir -p build/Analysis/CodeChecker/ClangSA')
            sh("""${CODECHECKER_PATH} analyze \
                  "build/DebugNoPCH/compile_commands.json" \
                  -j2 \
                  --analyzers clangsa \
                  --enable-all \
                  --enable alpha \
                  --ctu \
                  -i .codechecker_skip \
                  --output build/Analysis/CodeChecker/ClangSA/""")
            stash(name: 'CodeCheckerClangSA_CTUResults',
                  includes: 'build/Analysis/CodeChecker/ClangSA/*.plist')
          }
        }
        stage('CodeChecker ClangSA') {
          when {
            expression { params.DO_CLANGSA_CTU == false }
          }
          steps {
            unstash(name: 'DebugNoPCHCompDBase')
            sh('mkdir -p build/Analysis/CodeChecker/ClangSA')
            sh("""${CODECHECKER_PATH} analyze \
                  "build/DebugNoPCH/compile_commands.json" \
                  -j8 \
                  --analyzers clangsa \
                  --enable-all \
                  --enable alpha \
                  -i .codechecker_skip \
                  --output build/Analysis/CodeChecker/ClangSA/""")
            stash(name: 'CodeCheckerClangSAResults',
                  includes: 'build/Analysis/CodeChecker/ClangSA/*.plist')
          }
        }
        stage('CodeChecker ClangTidy') {
          steps {
            unstash(name: 'DebugNoPCHCompDBase')
            sh('mkdir -p build/Analysis/CodeChecker/ClangTidy')
            sh("""${CODECHECKER_PATH} analyze \
                  "build/DebugNoPCH/compile_commands.json" \
                  -j8 \
                  --analyzers clang-tidy \
                  --enable-all \
                  -i .codechecker_skip \
                  --output build/Analysis/CodeChecker/ClangTidy/""")
            stash(name: 'CodeCheckerClangTidyResults',
                  includes: 'build/Analysis/CodeChecker/ClangTidy/*.plist')
           }
        }
        stage('CppCheck') {
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
          steps {
            unstash(name: 'DebugNoPCHCompDBase')
            sh('mkdir -p build/Analysis/Infer')
            sh('''infer run \
                  --compilation-database build/DebugNoPCH/compile_commands.json \
                  --keep-going \
                  --results-dir build/Analysis/Infer''')
            stash(name: 'InferResults',
                  includes: 'build/Analysis/Infer/report.json')
          }
        }
        stage('Valgrind') {
          steps {
            unstash(name: 'ReleaseTests')
            unstash(name: 'DebugTests')
            sh('mkdir -p build/Analysis/Valgrind')
            sh('''valgrind build/Release/test/tests \
                  --log-file=build/Analysis/Valgrind/valgrind-%p.log''')
            sh('''valgrind build/Debug/test/tests \
                  --log-file=build/Analysis/Valgrind/valgrind-%p.log''')
            stash(name: 'ValgrindResults',
                  includes: 'build/Analysis/Valgrind/*.log')
          }
        }
        stage('Vera++') {
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
          steps {
            sh('mkdir -p build/Analysis/RATS')
            sh('''rats src samples test --xml \
                  1> build/Analysis/RATS/report.xml''')
            stash(name: 'RATSResults',
                  includes: 'build/Analysis/RATS/report.xml')
          }
        }
        stage('Coverage') {
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
          steps {
            unstash(name: 'DebugNoPCHCompDBase')
            unstash(name: 'CompilerOutput')
            unstash(name: 'TestReleaseReports')
            unstash(name: 'TestDebugReports')
            unstash(name: 'TestDebugNoPCHReports')
            unstash(name: 'TestCoverageReports')
            unstash(name: 'CodeCheckerClangSAResults')
            unstash(name: 'CodeCheckerClangSA_CTUResults')
            unstash(name: 'CodeCheckerClangTidyResults')
            unstash(name: 'CppCheckResults')
            unstash(name: 'InferResults')
            unstash(name: 'ValgrindResults')
            unstash(name: 'VeraResults')
            unstash(name: 'RATSResults')
            unstash(name: 'CoverageResults')

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
