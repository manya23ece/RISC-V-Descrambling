#include <stdio.h>
#include <stdint.h>
#include <printf.h>

// Function to calculate the LFSR feedback for a single input
uint16_t lfsr_feedback(uint16_t state) {
    uint16_t bit3 = (state >> 2) & 1;
    uint16_t bit5 = (state >> 4) & 1;
    return bit3 ^ bit5;
}

// Scalar scramble function
void scramble_scalar(uint16_t *input, uint16_t *output, size_t n) {
    for (size_t i = 0; i < n; i++) {
        uint16_t feedback = lfsr_feedback(input[i]);
        output[i] = input[i] ^ (feedback << 1);
    }
}

// Scalar descramble function
void descramble_scalar(uint16_t *input, uint16_t *output, size_t n) {
    for (size_t i = 0; i < n; i++) {
        uint16_t feedback = lfsr_feedback(input[i]);
        output[i] = input[i] ^ (feedback << 1);
    }
}

int main() {
    uint16_t input_data[8] = {0xD671, 0x1234, 0xFFFF, 0x0001, 0xA5A5, 0x5A5A, 0x0F0F, 0xF0F0};
    uint16_t scrambled_data[8];
    uint16_t descrambled_data[8];

    scramble_scalar(input_data, scrambled_data, 8);
    descramble_scalar(scrambled_data, descrambled_data, 8);

    for (int i = 0; i < 8; i++) {
        printf("Input: 0x%04X, Scrambled: 0x%04X, Descrambled: 0x%04X\n",
               input_data[i], scrambled_data[i], descrambled_data[i]);
    }

    return 0;
}
