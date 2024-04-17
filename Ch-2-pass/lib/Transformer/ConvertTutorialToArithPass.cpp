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
struct ConvertTutorialToArithPass
    : public PassWrapper<ConvertTutorialToArithPass, OperationPass<ModuleOp>> {
  MLIR_DEFINE_EXPLICIT_INTERNAL_INLINE_TYPE_ID(ConvertTutorialToArithPass)
  void runOnOperation() final {
    llvm::outs() << "getname = \n" << getOperation()->getName() << "\n";
    auto f = getOperation();
    llvm::outs() << f << "\n";
    f.walk([&](Operation *op) { llvm::outs() << "op = " << *op << "\n"; });
  }
};
} // namespace

std::unique_ptr<mlir::Pass> tutorial::createConvertTutorialToArithPass() {
  return std::make_unique<ConvertTutorialToArithPass>();
}