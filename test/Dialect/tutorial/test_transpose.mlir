
tutorial.func @main(%0 :tensor<2x3xf64>) {
  %1 = "tutorial.transpose"(%0) : (tensor<2x3xf64>) -> tensor<3x2xf64>
  tutorial.return %1 : tensor<3x2xf64>
}
