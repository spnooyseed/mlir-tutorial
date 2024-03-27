#ifndef SHAPE_INFERENECE_PASS_CPP
#define SHAPE_INFERENECE_PASS_CPP

#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Pass/PassManager.h"
#include "tutorial/ShapeInferenceInterfaces.h"
#include "tutorial/TutorialDialect.h"
#include "tutorial/TutorialOps.h"
#include "tutorial/TutorialPass.h"
namespace mlir {
namespace tutorial {
struct ShapeInferencePass
    : public mlir::PassWrapper<ShapeInferencePass,
                               OperationPass<func::FuncOp>> {
  void runOnOperation() override {
    auto f = getOperation();
    llvm::outs() << "\nin ShapeInferencePass = \n" << f << "\n";

    f.walk(
        [&](mlir::Operation* op) { llvm::outs() << "op = " << *op << "\n"; });
  }
};
}  // namespace tutorial
}  // namespace mlir

/// Create a Shape Inference pass.
std::unique_ptr<mlir::Pass> mlir::tutorial::createShapeInferencePass() {
  return std::make_unique<ShapeInferencePass>();
}

#endif  // SHAPE_INFERENECE_PASS_CPP