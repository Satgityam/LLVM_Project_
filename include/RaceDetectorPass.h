#ifndef LLVM_STATIC_RACE_DETECTOR_PASS_H
#define LLVM_STATIC_RACE_DETECTOR_PASS_H

#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/Pass.h"

#include <set>
#include <string>

namespace llvm {

class RaceDetectorPass : public ModulePass {
public:
  static char ID;
  RaceDetectorPass();

  // Main entry point for the pass
  bool runOnModule(Module &M) override;

private:
  // Helper functions for analysis
  void analyzeFunction(Function &F);
  void analyzeInstruction(Instruction *I);
  void handleStoreInst(StoreInst *SI);
  void handleLoadInst(LoadInst *LI);
  void detectPotentialRace(Value *ptr, bool isWrite, Instruction *I);

  // Utility
  std::string getMemoryAccessType(Value *ptr);
  std::string getThreadIndexSymbol(Value *val);

  // Tracking access patterns
  struct AccessRecord {
    Instruction *inst;
    Value *address;
    bool isWrite;
    std::string threadExpr;
  };

  std::vector<AccessRecord> accesses;
};

} // namespace llvm

#endif // LLVM_STATIC_RACE_DETECTOR_PASS_H
