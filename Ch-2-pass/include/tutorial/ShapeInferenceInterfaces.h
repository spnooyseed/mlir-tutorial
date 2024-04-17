//===- ShapeInferenceInterface.h - Interface definitions for ShapeInference -=//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the declarations of the shape inference interfaces defined
// in ShapeInferenceInterface.td.
//
//===----------------------------------------------------------------------===//

#ifndef tutorial_SHAPEINFERENCEINTERFACE_H_
#define tutorial_SHAPEINFERENCEINTERFACE_H_

#include "mlir/IR/OpDefinition.h"

namespace mlir {
namespace tutorial {

/// Include the auto-generated declarations.
#include "tutorial/ShapeInferenceInterfaces.h.inc"
} // namespace tutorial
} // namespace mlir

#endif // tutorial_SHAPEINFERENCEINTERFACE_H_
