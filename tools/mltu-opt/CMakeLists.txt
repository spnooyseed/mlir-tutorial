set(LLVM_LINK_COMPONENTS
  Core
  Support
  AsmParser
  )

get_property(dialect_libs GLOBAL PROPERTY MLIR_DIALECT_LIBS)
get_property(conversion_libs GLOBAL PROPERTY MLIR_CONVERSION_LIBS)
get_property(extension_libs GLOBAL PROPERTY MLIR_EXTENSION_LIBS)



set(LIBS
  ${dialect_libs}
  ${conversion_libs}
  ${extension_libs}

  MLIRAffineAnalysis
  MLIRAnalysis
  MLIRCastInterfaces
  MLIRDialect
  MLIRParser
  MLIRPass
  MLIRTransforms
  MLIRTransformUtils
  MLIRSupport
  MLIRIR
  Tutorial
  # TODO: Remove when registerAllGPUToLLVMIRTranslations is no longer
  # registered directly in mlir-opt.cpp.
  MLIRToLLVMIRTranslationRegistration
  )

add_llvm_tool(mltu-opt
  mltu-opt.cpp
)

target_link_libraries(mltu-opt PRIVATE ${LIBS})
llvm_update_compile_flags(mltu-opt)
mlir_check_all_link_libraries(mltu-opt)
message(STATUS "mltu-opt = ${mltu-opt}")
message(STATUS "MLIR_DIALECT_LIBS = ${MLIR_DIALECT_LIBS}")