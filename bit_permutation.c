#include <stdio.h>
//#include <printf.h>
// Function to scramble the input data using a predefined bit permutation
void scramble(int input[], int scrambled[], int bit_count, int new_positions[]) {
    for (int i = 0; i < bit_count; i++) {
        scrambled[i] = input[new_positions[i] - 1];  // Scramble based on new positions
    }
}

// Function to descramble the scrambled data using the reverse bit permutation
void descramble(int scrambled[], int descrambled[], int bit_count, int reverse_positions[]) {
    for (int i = 0; i < bit_count; i++) {
        descrambled[i] = scrambled[reverse_positions[i] - 1];  // Descramble based on reverse positions
    }
}

int main() {
    // Example: Original data as binary input
    int bit_count = 4;  // Number of bits in the binary data
    int input[] = {1, 0, 1, 0};  // Binary sequence (1010)

    // Predefined new bit positions for scrambling
    int new_positions[] = {3, 1, 4, 2};  // Mapping from original positions: [1,2,3,4] -> [3,1,4,2]

    // Compute reverse positions for descrambling
    int reverse_positions[bit_count];
    for (int i = 0; i < bit_count; i++) {
        reverse_positions[new_positions[i] - 1] = i + 1;
    }

    int scrambled[bit_count], descrambled[bit_count];

    // Scramble the input data
    scramble(input, scrambled, bit_count, new_positions);

    // Print scrambled data
  //  printf("Scrambled data: ");
    for (int i = 0; i < bit_count; i++) {
    //    printf("%d", scrambled[i]);
    }
    //printf("\n");

    // Descramble the scrambled data
    descramble(scrambled, descrambled, bit_count, reverse_positions);

    // Print descrambled data
    //printf("Descrambled data: ");
    for (int i = 0; i < bit_count; i++) {
      //  printf("%d", descrambled[i]);
    }
    //printf("\n");

    return 0;
}
