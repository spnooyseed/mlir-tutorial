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
#include "tutorial/ShapeInferenceInterfaces.cpp.inc"
struct ShapeInferencePass
    : public mlir::PassWrapper<ShapeInferencePass,
                               OperationPass<tutorial::FuncOp>> {
  void runOnOperation() override {
    auto f = getOperation();
    llvm::outs() << "\nin ShapeInferencePass = \n" << f << "\n";

    llvm::SmallPtrSet<mlir::Operation *, 16> opWorkList;

    f.walk([&](mlir::Operation *op) {
      llvm::outs() << "op = " << *op << "\n";
      opWorkList.insert(op);
    });

    while (!opWorkList.empty()) {
      auto nextOp = llvm::find_if(opWorkList, allOperandsInferred);

      if (nextOp == opWorkList.end())
        break;

      Operation *op = *nextOp;
      opWorkList.erase(op);

      if (auto shapeOp = llvm::dyn_cast<ShapeInference>(op)) {
        shapeOp.inferShapes();
      } else {
        llvm::outs() << *op << "\n";
        op->emitError("unable to infer shape of operation without shape");
        return signalPassFailure();
      }
    }

    if (!opWorkList.empty()) {
      f.emitError("shape inference failed , ")
          << opWorkList.size() << " operations couldn't be inferend\n";
      signalPassFailure();
    }
  }

  /// A utility method that returns if the given operation has all of its
  /// operands inferred.
  static bool allOperandsInferred(Operation *op) {
    return llvm::all_of(op->getOperandTypes(), [](Type operandType) {
      return llvm::isa<RankedTensorType>(operandType);
    });
  }
};
} // namespace tutorial
} // namespace mlir

/// Create a Shape Inference pass.
std::unique_ptr<mlir::Pass> mlir::tutorial::createShapeInferencePass() {
  return std::make_unique<ShapeInferencePass>();
}

#endif // SHAPE_INFERENECE_PASS_CPP