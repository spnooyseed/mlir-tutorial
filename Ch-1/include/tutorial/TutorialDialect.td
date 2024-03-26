
#ifndef Tutorial_Dialect_TD
#define Tutorial_Dialect_TD
// project a definition of the 'tutorial' dialect in the ODS Framewrok
include "mlir/IR/OpBase.td"

def Tutorial_Dialect : Dialect{

    // namespace of our dialect , can get by Tutorial_Dialect::getDialectNamespace()
    let name = "tutorial" ;

    // cppNamespace 属性：
    // let cppNamespace = "toy"; 这行代码指定了生成的 C++ 代码中方言类所在的命名空间。
    // 在 C++ 编程中，命名空间是一种封装一组标识符（如类、函数等）的方法，以避免名称冲突。cppNamespace 属性告诉 TableGen 生成器在生成 C++ 代码时，应该将方言相关的类和枚举放在名为 "toy" 的命名空间下。
    // 例如，如果方言中定义了一个名为 MyOp 的操作，那么在生成的 C++ 代码中，这个操作的完整名称将是 toy::MyOp。
    let cppNamespace = "::tutorial" ;

    // A short one-line summary of our dialect.
    let summary = "A high-level dialect for analyzing and optimizing the Toy language" ;
    
    // A much longer description of our dialect.
    let description = [{
        The Tutorial language is a tensor-based language that allows you to define
        functions, perform some math computation, and print results. This dialect
        provides a representation of the language that is amenable to analysis and
        optimization.
    }] ;
}

#endif // Tutorial_Dialect_TD