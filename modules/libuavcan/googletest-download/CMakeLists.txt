cmake_minimum_required(VERSION 2.8.2)

project(googletest-download NONE)

include(ExternalProject)
ExternalProject_Add(googletest
  GIT_REPOSITORY    https://github.com/google/googletest.git
  GIT_TAG           98a0d007d7092b72eea0e501bb9ad17908a1a036
  SOURCE_DIR        "/home/mmc-wy/mmc_onboard/googletest-src"
  BINARY_DIR        "/home/mmc-wy/mmc_onboard/googletest-build"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)
