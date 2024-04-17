#ifndef TUTORIAL_PASS_H
#define TUTORIAL_PASS_H
#include <memory>

#include "mlir/Pass/Pass.h"
#include "mlir/Pass/PassRegistry.h"
#include "tutorial/TutorialOps.h"
namespace mlir {
namespace tutorial {

#define GEN_PASS_DECL
#include "tutorial/TutorialPass.h.inc"
std::unique_ptr<mlir::Pass> createShapeInferencePass();

std::unique_ptr<mlir::Pass> createConvertTutorialToArithPass();

#define GEN_PASS_REGISTRATION
#include "tutorial/TutorialPass.h.inc"
} // namespace tutorial
} // namespace mlir

#endif // TUTORIAL_PASS_H