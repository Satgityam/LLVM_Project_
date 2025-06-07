#!/bin/bash

set -e

# Create build folder if not exists
mkdir -p build
cd build

# Run cmake and make
cmake ..
make

# Generate LLVM IR from CUDA kernel
cd ..
clang++ -x cuda --cuda-gpu-arch=sm_50 -nocudalib -S -emit-llvm kernels/test_kernel.cu -o kernels/test_kernel.ll

# Run the LLVM pass
opt -load ./build/libStaticRaceDetector.dylib -race-detector kernels/test_kernel.ll
