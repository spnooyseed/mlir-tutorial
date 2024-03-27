#ifndef TUTORIAL_CPP
#define TUTORIAL_CPP

#include "tutorial/TutorialDialect.h"
#include "tutorial/TutorialOps.h"
#include "tutorial/TutorialOpsDialect.cpp.inc"
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

#endif  // TUTORIAL_CPP