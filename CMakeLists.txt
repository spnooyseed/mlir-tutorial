cmake_minimum_required(VERSION 3.24.0)

project(mlir-tutorial VERSION 0.0.0)
cmake_policy(SET CMP0116 NEW)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # 生成 compile_commands.json 便于代码高亮
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

find_package(MLIR REQUIRED CONFIG)
message(STATUS "Using MLIRConfig.cmake in: ${MLIR_DIR}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

list(APPEND CMAKE_MODULE_PATH "${MLIR_CMAKE_DIR}")
list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")

include(TableGen)
include(AddLLVM)
include(AddMLIR)
include(HandleLLVMOptions)

include_directories(${LLVM_INCLUDE_DIRS} ${MLIR_INCLUDE_DIRS})

add_executable(mlir-tutorial main.cpp)


target_link_libraries(
  mlir-tutorial
  MLIRIR
  MLIRParser
  MLIRFuncDialect
  MLIRArithDialect
)