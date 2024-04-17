#ifndef TUTORIAL_CPP
#define TUTORIAL_CPP

#include "mlir/IR/Builders.h"
#include "mlir/IR/OpImplementation.h"
#include "mlir/IR/Operation.h"
#include "mlir/IR/OperationSupport.h"
#include "mlir/Interfaces/FunctionImplementation.h"
#include "mlir/Support/LogicalResult.h"
#include "tutorial/TutorialDialect.h"
#include "tutorial/TutorialOps.h"
#include "tutorial/TutorialOpsDialect.cpp.inc"
#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/StringRef.h"
#define GET_OP_CLASSES
#include "tutorial/TutorialOps.cpp.inc"
using namespace mlir;
using namespace tutorial;

void TutorialDialect::initialize() {
  addOperations<
#define GET_OP_LIST
#include "tutorial/TutorialOps.cpp.inc"
      >();
}

void TransposeOp::inferShapes() {
  auto arrayTy = llvm::cast<RankedTensorType>(getOperand().getType());
  SmallVector<int64_t, 2> dims(llvm::reverse(arrayTy.getShape()));
  getResult().setType(RankedTensorType::get(dims, arrayTy.getElementType()));
}

// void FuncOp::build(mlir::OpBuilder &builder, mlir::OperationState &state,
//                    llvm::StringRef name, mlir::FunctionType type,
//                    llvm::ArrayRef<mlir::NamedAttribute> attrs) {
//   // FunctionOpInterface provides a convenient `build` method that will
//   populate
//   // the state of our FuncOp, and create an entry block.
//   buildWithEntryBlock(builder, state, name, type, attrs, type.getInputs());
// }

mlir::ParseResult FuncOp::parse(mlir::OpAsmParser &parser,
                                mlir::OperationState &result) {
  // Dispatch to the FunctionOpInterface provided utility method that parses the
  // function operation.
  auto buildFuncType =
      [](mlir::Builder &builder, llvm::ArrayRef<mlir::Type> argTypes,
         llvm::ArrayRef<mlir::Type> results,
         mlir::function_interface_impl::VariadicFlag,
         std::string &) { return builder.getFunctionType(argTypes, results); };

  return mlir::function_interface_impl::parseFunctionOp(
      parser, result, /*allowVariadic=*/false,
      getFunctionTypeAttrName(result.name), buildFuncType,
      getArgAttrsAttrName(result.name), getResAttrsAttrName(result.name));
}

void FuncOp::print(mlir::OpAsmPrinter &p) {
  // Dispatch to the FunctionOpInterface provided utility method that prints the
  // function operation.
  mlir::function_interface_impl::printFunctionOp(
      p, *this, /*isVariadic=*/false, getFunctionTypeAttrName(),
      getArgAttrsAttrName(), getResAttrsAttrName());
}

void ConstantOp::build(mlir::OpBuilder &builder, mlir::OperationState &state,
                       double value) {
  auto dataType = RankedTensorType::get({}, builder.getF64Type());
  auto dataAttribute = DenseElementsAttr::get(dataType, value);
  ConstantOp::build(builder, state, dataType, dataAttribute);
}

#endif // TUTORIAL_CPP