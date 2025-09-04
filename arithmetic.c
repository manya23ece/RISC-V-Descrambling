#include <stdio.h>
#include <math.h>
//#include <printf.h>
// Function to scramble the input data
int scramble(int input, int key, int bit_count) {
    int addition = input + key;  // Add input and key
    int modulo = addition % (int)pow(2, bit_count);  // Take modulo 2^bit_count
    return modulo;  // Return scrambled result
}

// Function to descramble the scrambled data
int descramble(int scrambled, int key, int bit_count) {
    int subtraction = scrambled - key;  // Subtract key from scrambled data
    int modulo = subtraction % (int)pow(2, bit_count);  // Take modulo 2^bit_count

    // Ensure positive modulo result
    if (modulo < 0) {
        modulo += (int)pow(2, bit_count);
    }
    return modulo;  // Return original data
}

int main() {
    int input = 10;  // Example input in decimal (1010 in binary)
    int key = 5;     // Random key in decimal
    int bit_count = 4;  // Number of bits used (e.g., 4 bits for input)

    // Scrambling
    int scrambled = scramble(input, key, bit_count);
  //  printf("Scrambled data: %d (Binary: ", scrambled);
    for (int i = bit_count - 1; i >= 0; --i) {
    //    printf("%d", (scrambled >> i) & 1);
    }
    //printf(")\n");

    // Descrambling
    int descrambled = descramble(scrambled, key, bit_count);
    //printf("Descrambled data: %d (Binary: ", descrambled);
    for (int i = bit_count - 1; i >= 0; --i) {
      //  printf("%d", (descrambled >> i) & 1);
    }
    //printf(")\n");

    return 0;
}
