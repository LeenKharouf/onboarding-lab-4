#include <cstdint>
#include <catch2/catch_test_macros.hpp>
#include <VExercise1.h>

// Function to test different operations
void perform_test(uint8_t operationCode, uint8_t(*operation)(uint8_t, uint8_t)) {
    VExercise1 model;
    model.op = operationCode;
    model.a = 0;
    model.b = 0;

    do {
        do {
            model.eval();
            uint8_t expected_result = operation(model.a, model.b);
            REQUIRE(expected_result == model.out);
        } while (++model.b != 0);  // Increment b until it wraps around to 0
    } while (++model.a != 0);  // Increment a until it wraps around to 0
}

// Test cases for different operations
TEST_CASE("Opcode 0, XOR Operation") {
    perform_test(0, [](uint8_t a, uint8_t b) -> uint8_t { return a ^ b; });
}

TEST_CASE("Opcode 1, Left Shift Operation") {
    perform_test(1, [](uint8_t a, uint8_t b) -> uint8_t { return (b >= 8) ? 0 : (a << b); });
}

TEST_CASE("Opcode 2, Modulo Operation") {
    perform_test(2, [](uint8_t a, uint8_t b) -> uint8_t { return (b != 0) ? (a % b) : 0; });
}

TEST_CASE("Opcode 3, NAND Operation") {
    perform_test(3, [](uint8_t a, uint8_t b) -> uint8_t { return ~(a & b); });
}
