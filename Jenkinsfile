pipeline {
  agent none

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
                  defaultValue: false,
                  description: 'Run SonarCloud scanner?')
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
      agent any
      when {
        expression { params.DO_CHECKOUT == true }
      } // when
      steps {
        cleanWs(deleteDirs:true, disableDeferredWipeout: true)
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
      post { cleanup { cleanWs(deleteDirs:true, disableDeferredWipeout: true) } }
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
          stage('Setup Docker') {
            agent any
            stages {
              stage('Setup') {
                steps {
                  cleanWs(deleteDirs:true, disableDeferredWipeout: true)
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
                  cleanWs(deleteDirs:true, disableDeferredWipeout: true)
                  echo("Built Dockerfile.${COMPILER}")
                  unstash(name: 'source_code')
                  ansiColor('xterm') {
                    cmakeBuild( buildType: 'Debug',
                                generator: 'Ninja',
                                buildDir: "build/${COMPILER}/DebugNoPCH",
                                cleanBuild: params.DO_CLEAN_BUILD,
                                cmakeArgs: '-DDISABLE_PCH=True',
                                installation: 'cmake-latest')
                  } // ansiColor('xterm')
                  stash(name: "DebugNoPCHCompDBase_${COMPILER}",
                        includes: "build/${COMPILER}/DebugNoPCH/compile_commands.json")
                  stash(name: "DebugNoPCH_${COMPILER}",
                        includes: "build/${COMPILER}/DebugNoPCH/*")
                } // steps
                post { cleanup { cleanWs(deleteDirs:true, disableDeferredWipeout: true) } }
              } // stage('Compile')
            } // stages
          } // stage('BuildDockerFile')
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
          stage('Setup and Execute') {
            agent any
            stages {
              stage('Setup') {
                steps {
                  cleanWs(deleteDirs:true, disableDeferredWipeout: true)
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
                      cleanWs(deleteDirs:true, disableDeferredWipeout: true)
                      unstash(name: 'source_code')
                      sh(script: """mkdir -p build/Analysis/CompilerOutput/${COMPILER}/""", label: 'Create build directory')
                      ansiColor('xterm') {
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
                      } // ansiColor('xterm')
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
                      ansiColor('xterm') {
                        sh(script: """build/${COMPILER}/${CONFIGURATION}/DisablePCH_${DISABLE_PCH}/test/tests \
                            --gtest_output=xml:build/TestReports/${COMPILER}_${CONFIGURATION}_DisablePCH_${DISABLE_PCH}/""",
                            label: 'Run Tests')
                      } // ansiColor('xterm')
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
                        ) // xunit
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
                      ansiColor('xterm') {
                        sh(script: """valgrind \
                              --log-file=build/Analysis/Valgrind/valgrind-${COMPILER}_${CONFIGURATION}_DisablePCH_${DISABLE_PCH}-%p.log \
                              -s \
                              --leak-check=full \
                              --show-leak-kinds=all \
                              build/${COMPILER}/${CONFIGURATION}/DisablePCH_${DISABLE_PCH}/test/tests""",
                              label: 'Run Valgrind')
                       } // ansiColor('xterm')
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
                      ansiColor('xterm') {
                        sh(script: """gcovr -r . -x \
                              --object-directory=build/${COMPILER}/${CONFIGURATION}/DisablePCH_${DISABLE_PCH}/test/ \
                              > build/Analysis/Coverage/report-${COMPILER}_${CONFIGURATION}_DisablePCH_${DISABLE_PCH}.xml""",
                              label: 'Run GCovR')
                      } // ansiColor('xterm')
                      stash(name: "CoverageResults_${COMPILER}_${CONFIGURATION}_${DISABLE_PCH}",
                            includes: "build/Analysis/Coverage/report-${COMPILER}_${CONFIGURATION}_DisablePCH_${DISABLE_PCH}.xml",
                            allowEmpty: true)
                    } // steps
                  } // stage('Coverage')
                } // stages
                post { cleanup { cleanWs(deleteDirs:true, disableDeferredWipeout: true) } }
              } // stage('Execute')
            } // stages
            post { cleanup { cleanWs(deleteDirs:true, disableDeferredWipeout: true) } }
          } // stage('SetupAndExecute')
        } // stages
      } // matrix
      post {
        success {
          node(null) {
            cleanWs(deleteDirs:true, disableDeferredWipeout: true)
            collateBuildOutput()
            cleanWs(deleteDirs:true, disableDeferredWipeout: true)
          } // node(null)
        } // success
      } // post
    } // stage('Build and Test')

    stage('Analysis') {
      when {
        expression { params.RUN_ANALYSIS == true }
      }
      parallel {
        stage('CodeChecker ClangSA CTU') {
          agent {
            dockerfile {
              filename "Dockerfile.clang"
              args '-v /var/lib/jenkins/tools/:/var/lib/jenkins/tools/'
              reuseNode true
            } // dockerfile
          } // agent
          when {
            expression { params.RUN_CLANGSA_CTU == true && params.DO_BUILD == true}
          } // when
          environment {
            CODECHECKER_PATH = tool name: 'CodeChecker', type: 'com.cloudbees.jenkins.plugins.customtools.CustomTool'
          }
          steps {
            cleanWs(deleteDirs:true, disableDeferredWipeout: true)
            unstash(name: 'DebugNoPCHCompDBase_clang')
            unstash(name: 'source_code')
            ansiColor('xterm') {
              sh(script: 'tools/run_clangsa_ctu.sh', label: 'Run ClangSA')
            } // ansiColor('xterm')
            stash(name: 'CodeCheckerClangSA_CTUResults',
                  includes: 'build/Analysis/CodeChecker/ClangSA/*.plist')
          } // steps
          post { cleanup { cleanWs(deleteDirs:true, disableDeferredWipeout: true) } }
        } // stage('CodeChecker ClangSA CTU')
        stage('CodeChecker ClangSA') {
          agent {
            dockerfile {
              filename "Dockerfile.clang"
              args '-v /var/lib/jenkins/tools/:/var/lib/jenkins/tools/'
              reuseNode true
            } // dockerfile
          } // agent
          when {
            expression { params.RUN_CLANGSA == true && params.DO_BUILD == true}
          } // when
          environment {
            CODECHECKER_PATH = tool name: 'CodeChecker', type: 'com.cloudbees.jenkins.plugins.customtools.CustomTool'
          }
          steps {
            cleanWs(deleteDirs:true, disableDeferredWipeout: true)
            unstash(name: 'DebugNoPCHCompDBase_clang')
            unstash(name: 'source_code')
            ansiColor('xterm') {
              sh(script: 'tools/run_clangsa.sh', label: 'Run ClangSA')
            } // ansiColor('xterm')
            stash(name: 'CodeCheckerClangSAResults',
                  includes: 'build/Analysis/CodeChecker/ClangSA/*.plist')
          } // steps
          post { cleanup { cleanWs(deleteDirs:true, disableDeferredWipeout: true) } }
        } // stage('CodeChecker ClangSA')
        stage('CodeChecker ClangTidy') {
          agent {
            dockerfile {
              filename "Dockerfile.clang"
              args '-v /var/lib/jenkins/tools/:/var/lib/jenkins/tools/'
              reuseNode true
            } // dockerfile
          } // agent
          when {
            expression { params.RUN_CLANGTIDY == true && params.DO_BUILD == true}
          } // when
          environment {
            CODECHECKER_PATH = tool name: 'CodeChecker', type: 'com.cloudbees.jenkins.plugins.customtools.CustomTool'
          }
          steps {
            cleanWs(deleteDirs:true, disableDeferredWipeout: true)
            unstash(name: 'DebugNoPCHCompDBase_clang')
            unstash(name: 'source_code')
            ansiColor('xterm') {
              sh(script: 'tools/run_clang_tidy.sh', label: 'Run ClangTidy')
            } // ansiColor('xterm')
            stash(name: 'CodeCheckerClangTidyResults',
                  includes: 'build/Analysis/CodeChecker/ClangTidy/*.plist')
           } // steps
           post { cleanup { cleanWs(deleteDirs:true, disableDeferredWipeout: true) } }
        } // stage('CodeChecker ClangTidy')
        stage('CppCheck') {
          agent any
          when {
            expression { params.RUN_CPPCHECK == true && params.DO_BUILD == true}
          } // when
          environment {
            CPPCHECK_PATH = tool name: 'cppcheck', type: 'com.cloudbees.jenkins.plugins.customtools.CustomTool'
          } // environment

          steps {
            cleanWs(deleteDirs:true, disableDeferredWipeout: true)
            unstash(name: 'DebugNoPCHCompDBase_clang')
            unstash(name: 'source_code')
            ansiColor('xterm') {
              sh(script: """tools/run_cppcheck.sh""", label: 'Run CppCheck')
            } // ansiColor('xterm')
            stash(name: 'CppCheckResults',
                  includes: 'build/Analysis/CppCheck/cppcheck.xml')
          } // steps
          post { cleanup { cleanWs(deleteDirs:true, disableDeferredWipeout: true) } }
        } // stage('CppCheck')
        stage('Infer') {
          agent any
          when {
            expression { params.RUN_INFER == true && params.DO_BUILD == true}
          } // when
          environment {
            INFER_PATH = tool name: 'infer', type: 'com.cloudbees.jenkins.plugins.customtools.CustomTool'
          } // environment
          steps {
            cleanWs(deleteDirs:true, disableDeferredWipeout: true)
            unstash(name: 'DebugNoPCHCompDBase_clang')
            unstash(name: 'source_code')
            ansiColor('xterm') {
              sh(script: 'tools/run_infer.sh', label: 'Run FBInfer')
            } // ansiColor('xterm')
            stash(name: 'InferResults',
                  includes: 'build/Analysis/Infer/report.json')
          } // steps
          post { cleanup { cleanWs(deleteDirs:true, disableDeferredWipeout: true) } }
        } // stage('Infer')
        stage('Vera++') {
          agent any
          when {
            expression { params.RUN_VERA == true }
          } // when
          environment {
            VERA_PATH = tool name: 'vera++', type: 'com.cloudbees.jenkins.plugins.customtools.CustomTool'
          } // environment
          steps {
            cleanWs(deleteDirs:true, disableDeferredWipeout: true)
            unstash(name: 'source_code')
            ansiColor('xterm') {
              sh(script: 'tools/run_vera.sh',
                label: 'Run Vera++')
            } // ansiColor('xterm')
            stash(name: 'VeraResults',
                  includes: 'build/Analysis/VeraPlusPlus/report.xml')
          } // steps
          post { cleanup { cleanWs(deleteDirs:true, disableDeferredWipeout: true) } }
        } // stage('Vera++')
        stage('RATS') {
          agent any
          when {
            expression { params.RUN_RATS == true }
          } // when
          environment {
            RATS_PATH = tool name: 'rats', type: 'com.cloudbees.jenkins.plugins.customtools.CustomTool'
          } // environment
          steps {
            cleanWs(deleteDirs:true, disableDeferredWipeout: true)
            unstash(name: 'source_code')
            ansiColor('xterm') {
              sh(script: 'tools/run_rats.sh', label: 'Run RATS')
            } // ansiColor('xterm')
            stash(name: 'RATSResults',
                  includes: 'build/Analysis/RATS/report.xml')
          } // steps
          post { cleanup { cleanWs(deleteDirs:true, disableDeferredWipeout: true) } }
        } // stage('RATS')
      } // parallel
      post {
        always {
          node(null) {
            cleanWs(deleteDirs:true, disableDeferredWipeout: true)
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
            cleanWs(deleteDirs:true, disableDeferredWipeout: true)
          } // node(null)
        } // always
      } // post
    } // stage('Analysis')
    stage('Sonar') {
      parallel {
        stage('SonarQube analysis') {
          agent any
          when {
            expression { params.RUN_SONARQUBE == true }
          } // when
          environment {
            SONAR_SCANNER_PATH = tool name: 'sonar-scanner', type: 'hudson.plugins.sonar.SonarRunnerInstallation'
          } // environment
          steps {
            cleanWs(deleteDirs:true, disableDeferredWipeout: true)
            catchError(buildResult: null, stageResult: null) { unstash(name: 'DebugNoPCHCompDBase_gcc')       }
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

            withSonarQubeEnv('SonarQube') {
              ansiColor('xterm') {
                sh(script: "${SONAR_SCANNER_PATH}/bin/sonar-scanner -Dproject.settings=sonarqube.properties",
                   label: 'Run SonarScanner')
              } // ansiColor('xterm')
            } // withSonarQubeEnv
          } // steps
          post { cleanup { cleanWs(deleteDirs:true, disableDeferredWipeout: true) } }
        } // stage('SonarQube analysis')
        stage('SonarCloud analysis') {
          agent any
          stages {
            stage('Setup') {
              steps {
                cleanWs(deleteDirs:true, disableDeferredWipeout: true)
                unstash(name: 'dockerfiles')
              } // steps
            } // stage('Setup')
            stage('Analysis') {
              agent {
                dockerfile {
                  filename "Dockerfile.gcc"
                  args '-v /var/lib/jenkins/tools/:/var/lib/jenkins/tools/'
                  reuseNode true
                } // dockerfile
              } // agent
              when {
                expression { params.RUN_SONARCLOUD == true }
              } // when
              environment {
                SONAR_SCANNER_PATH = tool name: 'sonar-scanner', type: 'hudson.plugins.sonar.SonarRunnerInstallation'
                SONAR_BUILD_WRAPPER_PATH = tool name: 'SonarBuildWrapper', type: 'com.cloudbees.jenkins.plugins.customtools.CustomTool'
              } // environment
              steps {
                cleanWs(deleteDirs:true, disableDeferredWipeout: true)
                unstash(name: 'source_code')
                unstash(name: 'DebugNoPCH_gcc')
                sh(script: """${SONAR_BUILD_WRAPPER_PATH}/build-wrapper-linux-x86-64 \
                      --out-dir build/BuildWrapper \
                      ninja -j4 -C build/gcc/DebugNoPCH all""",
                      label: 'Build with Sonar Build Wrapper')
                catchError(buildResult: null, stageResult: null) { unstash(name: 'CompilerOutput')                }
                catchError(buildResult: null, stageResult: null) { unstash(name: 'TestReports')                   }
                catchError(buildResult: null, stageResult: null) { unstash(name: 'CoverageResults')               }
                withSonarQubeEnv('SonarCloud') {
                  ansiColor('xterm') {
                    sh(script: "${SONAR_SCANNER_PATH}/bin/sonar-scanner -Dproject.settings=sonarcloud.properties",
                       label: 'Run SonarScanner')
                  } // ansiColor('xterm')
                } // withSonarQubeEnv
              } // steps
              post { cleanup { cleanWs(deleteDirs:true, disableDeferredWipeout: true) } }
            } // stage('Analysis')
          } // stages
        } // stage('SonarCloud analysis')
      } // parallel
    } // stage('Sonar')
  } // stages
} // pipeline

void collateBuildOutput() {
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
  catchError(buildResult: null, stageResult: null) { unstash(name: "CoverageResults_gcc_Coverage_True")          }
  catchError(buildResult: null, stageResult: null) { unstash(name: "CoverageResults_gcc_Coverage_False")         }
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
}
