#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
struct RaceDetector : public FunctionPass {
  static char ID;
  RaceDetector() : FunctionPass(ID) {}

  bool runOnFunction(Function &F) override {
    errs() << "Analyzing function: " << F.getName() << "\n";

    for (auto &BB : F) {
      for (auto &I : BB) {
        if (LoadInst *LI = dyn_cast<LoadInst>(&I)) {
          if (LI->getPointerAddressSpace() == 3) { // shared memory
            errs() << "[Read] Shared memory access: " << I << "\n";
          }
        } else if (StoreInst *SI = dyn_cast<StoreInst>(&I)) {
          if (SI->getPointerAddressSpace() == 3) { // shared memory
            errs() << "[Write] Shared memory access: " << I << "\n";
          }
        }
      }
    }

    return false;
  }
};
}

char RaceDetector::ID = 0;
static RegisterPass<RaceDetector> X("race-detect", "Static Race Detector Pass", false, false);
