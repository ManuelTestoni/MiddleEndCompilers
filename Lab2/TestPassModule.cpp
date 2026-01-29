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

using namespace llvm;

bool runOnBasicBlock(BasicBlock &B) {
    
  // Preleviamo le prime due istruzioni del BB
  Instruction &Inst1st = *B.begin(), &Inst2nd = *(++B.begin());

  

  for (auto &Inst : B) {
    outs() << "Istruzione: " << Inst << "\n";

    // Controlla se l'istruzione è una moltiplicazione
    if (Inst.getOpcodeName() == std::string("mul")) {
        outs() << "Istruzione mul detectata! \n";

        // Controlla gli operandi della moltiplicazione
        for (unsigned i = 0; i < Inst.getNumOperands(); ++i) {
            Value *Operand = Inst.getOperand(i);

            if (ConstantInt *C = dyn_cast<ConstantInt>(Operand)) {
                int64_t Val = C->getSExtValue(); 
                
                if (Val > 0 && (Val & (Val - 1)) == 0) {
                    outs() << "Trovato! L'istruzione ha un operando che è una potenza di 2.\n";

                    // Calcola il logaritmo base 2 del valore
                    unsigned Log2Val = Log2_64(Val);

                    Value *OtherOperand = Inst.getOperand(1 - i);
                    Instruction *ShiftInst = BinaryOperator::CreateShl(
                        OtherOperand, ConstantInt::get(C->getType(), Log2Val));
                    ShiftInst->insertAfter(&Inst);

                    Inst.replaceAllUsesWith(ShiftInst);

                    outs() << "Nuova istruzione creata: " << *ShiftInst << "\n";
                }
            }
        }
    }
}

 

  // Manipolazione delle istruzioni
  Instruction *NewInst = BinaryOperator::Create(
      Instruction::Add, Inst1st.getOperand(0), Inst1st.getOperand(0));

  NewInst->insertAfter(&Inst1st);
  // Si possono aggiornare le singole references separatamente?
  // Controlla la documentazione e prova a rispondere.
  Inst1st.replaceAllUsesWith(NewInst);

  return true;
}

bool runOnFunction(Function &F) {
  bool Transformed = false;

  for (auto Iter = F.begin(); Iter != F.end(); ++Iter) {
    if (runOnBasicBlock(*Iter)) {
      Transformed = true;
    }
  }

  return Transformed;
}
//-----------------------------------------------------------------------------
// TestPass implementation
//-----------------------------------------------------------------------------
// No need to expose the internals of the pass to the outside world - keep
// everything in an anonymous namespace.
namespace {


// New PM implementation
struct TestPass : public llvm::ModulePass {
  static char ID; // Identificatore unico per il passaggio

  TestPass() : ModulePass(ID) {}

  bool runOnModule(llvm::Module &M) override {
    // Implementa il tuo passaggio qui che agisce sul modulo
    return false;
  }
};

} // namespace




//-----------------------------------------------------------------------------
// New PM Registration
//-----------------------------------------------------------------------------
llvm::PassPluginLibraryInfo getTestPassPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "TestPass", LLVM_VERSION_STRING,
          [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, ModulePassManager &MPM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                  if (Name == "test-pass") {
                    // Aggiungi il passaggio per il modulo
                    MPM.addPass(TestPass());
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
