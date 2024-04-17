#ifndef TUTORIAL_OPS_H
#define TUTORIAL_OPS_H

#include "mlir/IR/Builders.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/Interfaces/CallInterfaces.h"
#include "mlir/Interfaces/FunctionImplementation.h"
#include "mlir/Interfaces/InferTypeOpInterface.h"
#include "mlir/Interfaces/SideEffectInterfaces.h"
#include "tutorial/ShapeInferenceInterfaces.h.inc"
#include "tutorial/TutorialDialect.h"
#define GET_OP_CLASSES
#include "tutorial/TutorialOps.h.inc"
#endif // TUTORIAL_OPS_H