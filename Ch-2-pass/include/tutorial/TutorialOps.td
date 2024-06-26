
#ifndef TUTORIAL_OPS_TD
#define TUTORIAL_OPS_TD

include "TutorialDialect.td"
include "mlir/IR/OpBase.td"
include "mlir/Interfaces/SideEffectInterfaces.td"
include "mlir/Interfaces/FunctionInterfaces.td"
include "mlir/IR/SymbolInterfaces.td"
include "ShapeInferenceInterfaces.td"

include "mlir/Interfaces/InferTypeOpInterface.td"
// begin define own op derived baseOp Class
def ConstantOp : Tutorial_Op<"constant" , [Pure]> {
    let arguments = (ins
        F64ElementsAttr:$value
    );

    let results = (outs F64Tensor) ;

    let builders = [
        OpBuilder<(ins "double":$value)>,
        OpBuilder<(ins "DenseElementsAttr":$value), [{
            // Call into an autogenerated `build` method.
            build($_builder, $_state, value.getType(), value);
        }]>
    ] ;
    let builders = [OpBuilder<(ins "double":$value)> , 
        OpBuilder<(ins "DenseElementsAttr":$value), [{
        build($_builder, $_state, value.getType(), value);
        }]>,
    ];
    let summary = [{define a tutorial.constant op}] ;
    let description = [{ define a input of F64ElementsAttr , outs is F64Tensor}] ;
}

def AddOp : Tutorial_Op<"add", [Pure, SameOperandsAndResultType]> {
  let summary = "add operation";
  let arguments = (ins Variadic<AnyType>:$inputs);
  let results = (outs AnyType:$result);
  let assemblyFormat = "$inputs attr-dict `:` type($result)";
}

def SubOp : Tutorial_Op<"sub", [Pure, SameOperandsAndResultType]> {
  let summary = "sub operation";
  let arguments = (ins AnyType:$lhs, AnyType:$rhs);
  let results = (outs AnyType:$result);
  let assemblyFormat = "$lhs `,` $rhs attr-dict `:` type($result)";
}

def TransposeOp : Tutorial_Op<"transpose" , [Pure , DeclareOpInterfaceMethods<ShapeInferenceOpInterface>]> {
    let arguments = (ins AnyType:$value) ;
    let results = (outs AnyType);
    let summary = [{define a tutorial.transpose op}] ;
}

def PrintOp : Tutorial_Op<"print" , [Pure]> {
    let arguments = (ins AnyType:$input);
    let summary = [{define a tutorial.print op}];

    // can set mlir Format in td file
    let assemblyFormat = "$input attr-dict `:` type($input)";
}

def FuncOp : Tutorial_Op<"func" , [FunctionOpInterface , IsolatedFromAbove]> {
    let summary = "user defined function operation";
    let description = [{
        The "toy.func" operation represents a user defined function. These are
        callable SSA-region operations that contain toy computations.

        Example:

        ```mlir
        toy.func @main() {
        %0 = toy.constant dense<5.500000e+00> : tensor<f64>
        %1 = toy.reshape(%0 : tensor<f64>) to tensor<2x2xf64>
        toy.print %1 : tensor<2x2xf64>
        toy.return
        }
        ```
    }];

    let arguments = (ins
        SymbolNameAttr:$sym_name ,
        TypeAttrOf<FunctionType>:$function_type,
        OptionalAttr<DictArrayAttr>:$arg_attrs,
        OptionalAttr<DictArrayAttr>:$res_attrs
    );

    let regions = (region AnyRegion:$body);
    // let builders = [OpBuilder<(ins
    //     "StringRef":$name, "FunctionType":$type,
    //     CArg<"ArrayRef<NamedAttribute>", "{}">:$attrs)
    // >];
    let extraClassDeclaration = [{
        //===------------------------------------------------------------------===//
        // FunctionOpInterface Methods
        //===------------------------------------------------------------------===//

        /// Returns the argument types of this function.
        ArrayRef<Type> getArgumentTypes() { return getFunctionType().getInputs(); }

        /// Returns the result types of this function.
        ArrayRef<Type> getResultTypes() { return getFunctionType().getResults(); }

        /// Returns the region on the current operation that is callable.
        ::mlir::Region *getCallableRegion() { return &getBody(); }
    }];
    let hasCustomAssemblyFormat = 1;
    // let skipDefaultBuilders = 1;
}


def ReturnOp : Tutorial_Op<"return" , [Pure , Terminator , HasParent<"FuncOp">]> {


    let summary = "return operation" ;
    let description = [{
        The "return" operation represents a return operation within a function.
        The operation takes an optional tensor operand and produces no results.
        The operand type must match the signature of the function that contains
        the operation. For example:

        ```mlir
        toy.func @foo() -> tensor<2xf64> {
            ...
            toy.return %0 : tensor<2xf64>
        }
        ```
    }] ;

    let arguments = (ins Variadic<AnyType>:$input) ;

    let assemblyFormat = "($input^ `:` type($input))? attr-dict "; 
    // let builders = [OpBuilder<(ins) , [{build($_builder , $_state , std::nullopt);}]>];
    // let extraClassDeclaration = [{
    //     bool hasOperand() { return getNumOperands() != 0; }
    // }];

    // let hasVerifier = 1;
}

#endif // TUTORIAL_OPS_TD