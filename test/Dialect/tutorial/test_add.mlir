tutorial.func @test(%a: i32, %b: i32) -> i32 {
  %d = tutorial.add %a, %b : i32
  %f = tutorial.add %d, %d : i32
  tutorial.return %f : i32
}