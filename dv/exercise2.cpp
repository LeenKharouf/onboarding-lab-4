#include <cstdint>
#include <catch2/catch_test_macros.hpp>
#include <VExercise2.h>

TEST_CASE("LFSR Functionality Test") {
  VExercise2 model;
  uint16_t initial_value = 0;
  model.reset = 1; // Start with reset

  // Initialize the model with a known state
  for (int i = 0; i < 5; i++) {
    model.clk = 1; model.init = initial_value; model.eval();
    model.clk = 0; model.eval();
    REQUIRE((uint16_t) ~model.out == initial_value); // Inverse check
    initial_value = rand() % 0xFFFF; // New random initial value
  }

  // Run the LFSR without reset and check the sequence
  uint16_t expected_state = model.out;
  model.reset = 0;
  for (int i = 0; i < 1000; i++) {
    model.clk = 1; model.eval();
    model.clk = 0; model.eval();
    uint16_t calculated_bit = ((expected_state >> 0) ^ (expected_state >> 2)) & 1;
    expected_state = (expected_state << 1) | calculated_bit;
    REQUIRE(model.out == expected_state);
  }
}
