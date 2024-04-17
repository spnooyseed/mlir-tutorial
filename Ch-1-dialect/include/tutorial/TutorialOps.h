#ifndef TUTORIAL_OPS_H
#define TUTORIAL_OPS_H

#include "mlir/IR/Builders.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/Interfaces/SideEffectInterfaces.h"
#include "tutorial/TutorialDialect.h"
#define GET_OP_CLASSES
#include "tutorial/TutorialOps.h.inc"
#endif // TUTORIAL_OPS_H