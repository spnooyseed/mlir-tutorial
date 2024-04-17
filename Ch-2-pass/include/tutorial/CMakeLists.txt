add_mlir_dialect(TutorialOps tutorial)
add_mlir_doc(TutorialOps TutorialOps tutorial/  -gen-op-doc) # no effect ,but i dont no reason

set(LLVM_TARGET_DEFINITIONS TutorialPass.td)
mlir_tablegen(TutorialPass.h.inc -gen-pass-decls)
add_public_tablegen_target(TutorialTransformsIncGen)

set(LLVM_TARGET_DEFINITIONS ShapeInferenceInterfaces.td)
mlir_tablegen(ShapeInferenceInterfaces.h.inc -gen-op-interface-decls)
mlir_tablegen(ShapeInferenceInterfaces.cpp.inc -gen-op-interface-defs)
add_public_tablegen_target(TutorialShapeInferenceOpInterfaceIncGen)