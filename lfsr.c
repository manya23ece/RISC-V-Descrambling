#include <stdio.h>
#include <stdint.h>
//#include <printf.h>
// Function to calculate the LFSR feedback
uint16_t lfsr_feedback(uint16_t state) {
    // Extract the relevant bits (3rd and 5th positions from the right, 0-based index)
    uint16_t bit3 = (state >> 2) & 1; // Bit D^3
    uint16_t bit5 = (state >> 4) & 1; // Bit D^5
    return bit3 ^ bit5; // XOR operation
}

// Function to scramble a 16-bit input
uint16_t scramble(uint16_t input) {
    uint16_t state = input; // Initialize LFSR with the input
    uint16_t feedback = lfsr_feedback(state);
    uint16_t scrambled_output = input ^ (feedback << 1); // Compute scrambled output using XOR

    return scrambled_output;
}

// Function to descramble a 16-bit scrambled output
uint16_t descramble(uint16_t scrambled_input) {
    uint16_t state = scrambled_input; // Initial condition: T = Scrambled output
    uint16_t feedback = lfsr_feedback(state);
    uint16_t descrambled_output = scrambled_input ^ (feedback << 1); // Reverse XOR operation

    return descrambled_output;
}

int main() {
    uint16_t input = 0xD671; // Example 16-bit input: 1101011001110001
    uint16_t scrambled, descrambled;

    // Perform scrambling
    scrambled = scramble(input);

    // Perform descrambling
    descrambled = descramble(scrambled);

    // Print results
   // printf("Original Input:    0x%04X (%u)\n", input, input);
    //rintf("Scrambled Output:  0x%04X (%u)\n", scrambled, scrambled);
    //printf("Descrambled Output: 0x%04X (%u)\n", descrambled, descrambled);

    // Check if descrambling restores the original input
    if (descrambled == input) {
        printf("Descrambling successful! Original data recovered.\n");
    } else {
        printf("Descrambling failed. Something went wrong.\n");
    }

    return 0;
}
