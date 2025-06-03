cmake_minimum_required(VERSION 3.10)
project(StaticRaceDetector)

find_package(LLVM REQUIRED CONFIG)
list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
include(AddLLVM)

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_library(RaceDetectorPass MODULE
  src/RaceDetectorPass.cpp
)

set_target_properties(RaceDetectorPass PROPERTIES
  COMPILE_FLAGS "-fno-rtti"
)
