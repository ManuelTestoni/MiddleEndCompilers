//=============================================================================
// FILE:
//    TestPass.cpp
//
// DESCRIPTION:
//    Visits all functions in a module and prints their names. Strictly speaking, 
//    this is an analysis pass (i.e. //    the functions are not modified). However, 
//    in order to keep things simple there's no 'print' method here (every analysis 
//    pass should implement it).
//
// USAGE:
//    New PM
//      opt -load-pass-plugin=<path-to>libTestPass.so -passes="test-pass" `\`
//        -disable-output <input-llvm-file>
//
//
// License: MIT
//=============================================================================
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Module.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/Dominators.h"
#include "llvm/ADT/BreadthFirstIterator.h"



using namespace llvm;

void runOnBasicBlock(BasicBlock &B,  LoopInfo &LI) {
  if (Loop *L = LI.getLoopFor(&B)) {
    if (L->getHeader() == &B) {
        outs() << "BasicBlock '" << B.getName() << "' è un loop header\n";
        for (Instruction &I : B) {
          outs() << "Istruzione: " << I << "\n";
        }
    }
  }

}

void printDominanceTree(DominatorTree &DT, Function &F) {
  outs() << "Dominance Tree for function: " << F.getName() << "\n";
  DT.print(outs());
}

namespace {
struct TestPass : public PassInfoMixin<TestPass> {
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM) {
    LoopInfo &LI = AM.getResult<LoopAnalysis>(F);
    DominatorTree &DT = AM.getResult<DominatorTreeAnalysis>(F);
    
    // Verifica se ci sono loop
    if (!LI.empty()) {
      outs() << "Function: " << F.getName() << " contiene un loop\n";
      for (auto &BB : F) {
        runOnBasicBlock(BB, LI);
        printDominanceTree(DT, F);
      }
    } else {
      outs() << "Function: " << F.getName() << " non contiene loop\n";
      return PreservedAnalyses::all();
    }

    return PreservedAnalyses::all();
  }
};

}

//-----------------------------------------------------------------------------
// New PM Registration
//-----------------------------------------------------------------------------
llvm::PassPluginLibraryInfo getTestPassPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "LoopInfo", LLVM_VERSION_STRING,
          [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, FunctionPassManager &FPM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                  if (Name == "loop-info") {
                    FPM.addPass(TestPass());
                    return true;
                  }
                  return false;
                });
          }};
}

// This is the core interface for pass plugins. It guarantees that 'opt' will
// be able to recognize TestPass when added to the pass pipeline on the
// command line, i.e. via '-passes=test-pass'
extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return getTestPassPluginInfo();
}
