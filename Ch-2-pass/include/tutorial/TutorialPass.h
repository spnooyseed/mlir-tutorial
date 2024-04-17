#ifndef TUTORIAL_PASS_H
#define TUTORIAL_PASS_H
#include <memory>

namespace mlir {
class Pass;

namespace tutorial {
std::unique_ptr<Pass> createShapeInferencePass();
} // namespace tutorial
} // namespace mlir

#endif // TUTORIAL_PASS_H