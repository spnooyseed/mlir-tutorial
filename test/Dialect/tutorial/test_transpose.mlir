module {
  func.func @main() {
    %0 = "tutorial.constant"() {value = dense<1.0> : tensor<2x3xf64>} : () -> tensor<2x3xf64>
    %1 = "tutorial.transpose"(%0) : (tensor<2x3xf64>) -> tensor<3x2xf64>
    "tutorial.print"(%1) : (tensor<3x2xf64>) -> ()
    return
  }
}