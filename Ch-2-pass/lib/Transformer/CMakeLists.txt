add_mlir_library(
    TutorialTransformer
    ConvertTutorialToArithPass.cpp
    ShapeInferencePass.cpp
    
    DEPENDS TutorialTransformsIncGen

    LINK_LIBS
    MLIRArithDialect
    MLIRArithToLLVM

)