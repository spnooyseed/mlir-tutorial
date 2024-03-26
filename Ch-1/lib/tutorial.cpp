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