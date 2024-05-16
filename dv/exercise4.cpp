#include <cstdint>
#include <catch2/catch_test_macros.hpp>
#include <VExercise4.h>

uint8_t data_selector(uint8_t sel, uint8_t alpha, uint8_t beta, uint8_t gamma) {
  switch (sel) {
    case 0: return alpha;
    case 1: return beta;
    case 2: return gamma;
    default: return alpha | (beta & gamma);
  }
}

TEST_CASE("Data Selector Test") {
  VExercise4 model;
  model.alpha = 3; model.beta = 5; model.gamma = 7;
  model.cs = 1; // Chip select enabled

  for (int sel = 0; sel < 4; ++sel) {
    model.sel = sel;
    model.eval();
    uint8_t expected_output = data_selector(sel, model.alpha, model.beta, model.gamma);
    REQUIRE(model.out == expected_output);
  }

  // Test when chip select is disabled
  model.cs = 0; model.eval();
  for (int sel = 0; sel < 4; ++sel) {
    model.sel = sel;
    model.eval();
    REQUIRE(model.out == 0); // All outputs should be zero
  }
}
