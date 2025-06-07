#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
  struct RaceDetectorPass : public FunctionPass {
    static char ID;
    RaceDetectorPass() : FunctionPass(ID) {}

    bool runOnFunction(Function &F) override {
      errs() << "Running Race Detector on function: " << F.getName() << "\n";

      for (auto &BB : F) {
        for (auto &I : BB) {
          if (auto *LI = dyn_cast<LoadInst>(&I)) {
            errs() << "  Load from: ";
            LI->getPointerOperand()->print(errs());
            errs() << "\n";
          } else if (auto *SI = dyn_cast<StoreInst>(&I)) {
            errs() << "  Store to: ";
            SI->getPointerOperand()->print(errs());
            errs() << "\n";
          }
        }
      }

      return false;
    }
  };
}

char RaceDetectorPass::ID = 0;
static RegisterPass<RaceDetectorPass> X("race-detector", "Static Race Detector for CUDA Kernels", false, false);
