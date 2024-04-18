tutorial.func @test(%a: i32, %b: i32 , %c : i32) -> i32 {
  %d = tutorial.add %a, %b , %c : i32
  %f = tutorial.sub %d, %c : i32
  tutorial.return %f : i32
}