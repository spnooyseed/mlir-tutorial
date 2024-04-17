#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/IR/AsmState.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/Parser/Parser.h"
#include "mlir/Pass/PassManager.h"
#include "mlir/Support/FileUtilities.h"
#include "mlir/Transforms/Passes.h"
#include "tutorial/TutorialDialect.h"
#include "tutorial/TutorialOps.h"
#include "tutorial/TutorialPass.h"
#include "llvm/Support/raw_ostream.h"
using namespace mlir;

int main(int argc, char **argv) {
  MLIRContext ctx;
  ctx.loadDialect<func::FuncDialect, arith::ArithDialect,
                  mlir::tutorial::TutorialDialect>();
  auto src = parseSourceFile<ModuleOp>(argv[1], &ctx);
  src->print(llvm::outs());

  mlir::PassManager pm(src.get()->getName());

  // pm.addPass(mlir::createInlinerPass());
  // //createShapeInferencePass  have problem
  // pm.addNestedPass<tutorial::FuncOp>(tutorial::createShapeInferencePass());

  if (failed(pm.run(*src))) {
    return 4;
  }
  src->dump();
  return 0;
}