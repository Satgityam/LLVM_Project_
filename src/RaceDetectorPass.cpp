#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/Pass.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
  struct RaceDetectorPass : public ModulePass {
    static char ID;
    RaceDetectorPass() : ModulePass(ID) {}

    bool runOnModule(Module &M) override {
      errs() << "Running Static Race Detector...\n";

      for (Function &F : M) {
        if (F.isDeclaration()) continue;

        errs() << "Analyzing Function: " << F.getName() << "\n";

        for (auto &BB : F) {
          for (auto &I : BB) {
            if (auto *store = dyn_cast<StoreInst>(&I)) {
              errs() << "Found store to memory: ";
              store->getPointerOperand()->print(errs());
              errs() << "\n";
            }
            if (auto *load = dyn_cast<LoadInst>(&I)) {
              errs() << "Found load from memory: ";
              load->getPointerOperand()->print(errs());
              errs() << "\n";
            }
          }
        }
      }
      return false;
    }
  };
}

char RaceDetectorPass::ID = 0;
static RegisterPass<RaceDetectorPass> X("race-detect", "Static Race Detector Pass");
