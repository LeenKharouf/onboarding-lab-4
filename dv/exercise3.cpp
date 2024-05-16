#include <cstdint>
#include <catch2/catch_test_macros.hpp>
#include <VExercise3.h>

uint8_t custom_logic(uint8_t a, uint8_t b, uint8_t c, uint8_t sel) {
  switch (sel) {
    case 0: return a & b;
    case 1: return a | b;
    case 2: return a ^ c;
    default: return (b & c) | (a ^ b);
  }
}

TEST_CASE("Custom Logic Unit Test") {
  VExercise3 model;
  std::default_random_engine engine(std::random_device{}());
  std::uniform_int_distribution<uint8_t> dist(0, 255);

  for (int test_case = 0; test_case < 100; ++test_case) {
    uint8_t a = dist(engine), b = dist(engine), c = dist(engine);
    for (uint8_t sel = 0; sel < 4; ++sel) {
      model.a = a; model.b = b; model.c = c; model.sel = sel;
      model.eval();
      uint8_t expected = custom_logic(a, b, c, sel);
      REQUIRE(model.out == expected);
    }
  }
}
