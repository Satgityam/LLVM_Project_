cmake_minimum_required(VERSION 3.13)
project(StaticRaceDetector)

set(CMAKE_CXX_STANDARD 17)

# Find LLVM and Clang
find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)

include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${CLANG_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# LLVM components to link
set(LLVM_LINK_COMPONENTS
  Core
  Support
  Analysis
  IRReader
  Passes
)

# Add the LLVM pass (in passes/)
add_llvm_loadable_module(StaticRaceDetector
  passes/RaceDetectorPass.cpp
)
