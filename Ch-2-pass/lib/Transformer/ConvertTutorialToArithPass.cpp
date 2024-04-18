#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/IR/BuiltinAttributes.h"
#include "mlir/IR/BuiltinDialect.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/Diagnostics.h"
#include "mlir/IR/DialectRegistry.h"
#include "mlir/IR/PatternMatch.h"
#include "mlir/IR/ValueRange.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Support/LLVM.h"
#include "mlir/Support/LogicalResult.h"
#include "mlir/Support/TypeID.h"
#include "mlir/Transforms/DialectConversion.h"
#include "tutorial/TutorialDialect.h"
#include "tutorial/TutorialOps.h"
#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/Sequence.h"
#include "llvm/Support/Casting.h"
#include <algorithm>
#include <cstdint>
#include <functional>
#include <memory>
#include <utility>
#define GEN_PASS_DEF_CONVERTTOYTOARITH
#include "tutorial/TutorialPass.h"
using namespace mlir;

namespace {

struct AddOpPat : OpRewritePattern<tutorial::AddOp> {
  using OpRewritePattern<tutorial::AddOp>::OpRewritePattern;
  LogicalResult matchAndRewrite(tutorial::AddOp op,
                                PatternRewriter &rewriter) const final {
    llvm::outs() << "addOp = " << op << "\n";
    auto inputs = llvm::to_vector(op.getInputs());
    auto result = inputs[0];
    for (size_t i = 1; i < inputs.size(); ++i) {
      result = rewriter.create<arith::AddIOp>(op->getLoc(), result, inputs[i]);
    }
    rewriter.replaceOp(op, ValueRange(result));
    return success();
  }
};

struct SubOpPat : OpRewritePattern<tutorial::SubOp> {
  using OpRewritePattern<tutorial::SubOp>::OpRewritePattern;
  LogicalResult matchAndRewrite(tutorial::SubOp op,
                                PatternRewriter &rewriter) const final {
    llvm::outs() << "SubOp = " << op << "\n";
    rewriter.replaceOpWithNewOp<arith::SubIOp>(op, op.getLhs(), op.getRhs());
    return success();
  }
};

struct ConvertTutorialToArithPass
    : public PassWrapper<ConvertTutorialToArithPass, OperationPass<ModuleOp>> {
  MLIR_DEFINE_EXPLICIT_INTERNAL_INLINE_TYPE_ID(ConvertTutorialToArithPass)
  void getDependentDialects(DialectRegistry &registry) const override {
    registry.insert<affine::AffineDialect, func::FuncDialect,
                    memref::MemRefDialect>();
  }
  void runOnOperation() final {
    ConversionTarget target(getContext());

    target.addLegalDialect<arith::ArithDialect, affine::AffineDialect,
                           func::FuncDialect, memref::MemRefDialect>();
    // target.addIllegalDialect<tutorial::TutorialDialect>() ;
    RewritePatternSet patterns(&getContext());
    patterns.add<SubOpPat, AddOpPat /*, FuncOpPat*/>(&getContext());

    if (failed(applyPartialConversion(getOperation(), target,
                                      std::move(patterns))))
      signalPassFailure();
  }
};
} // namespace

std::unique_ptr<mlir::Pass> mlir::tutorial::createConvertTutorialToArithPass() {
  return std::make_unique<ConvertTutorialToArithPass>();
}
