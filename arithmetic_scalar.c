#include <stdio.h>
#include <math.h>
#include <printf.h>
// Scalar function to scramble input data
int scramble(int input, int key, int bit_count) {
    int addition = input + key;
    int modulo = addition % (1 << bit_count);  // 2^bit_count
    return modulo;
}

// Scalar function to descramble scrambled data
int descramble(int scrambled, int key, int bit_count) {
    int subtraction = scrambled - key;
    int modulo = subtraction % (1 << bit_count);

    if (modulo < 0) {
        modulo += (1 << bit_count);
    }

    return modulo;
}

// Scalar version for arrays of data
void scramble_scalar(const int *input, const int *key, int *scrambled, int bit_count, size_t n) {
    int modulo_val = 1 << bit_count;

    for (size_t i = 0; i < n; i++) {
        scrambled[i] = (input[i] + key[i]) % modulo_val;
    }
}

void descramble_scalar(const int *scrambled, const int *key, int *descrambled, int bit_count, size_t n) {
    int modulo_val = 1 << bit_count;

    for (size_t i = 0; i < n; i++) {
        int sub = scrambled[i] - key[i];
        int mod = sub % modulo_val;

        if (mod < 0) {
            mod += modulo_val;
        }

        descrambled[i] = mod;
    }
}

int main() {
    int input[] = {10, 12, 3, 7};   // Example inputs
    int key[] = {5, 7, 2, 1};       // Example keys
    int bit_count = 4;              // Using 4-bit data
    size_t n = sizeof(input) / sizeof(input[0]);

    int scrambled[sizeof(input)/sizeof(input[0])];
    int descrambled[sizeof(input)/sizeof(input[0])];

    // Scramble inputs
    scramble_scalar(input, key, scrambled, bit_count, n);

    // Descramble to recover original inputs
    descramble_scalar(scrambled, key, descrambled, bit_count, n);

    // Print results
    for (size_t i = 0; i < n; i++) {
        printf("Input: %2d, Key: %2d, Scrambled: %2d, Descrambled: %2d\n",
               input[i], key[i], scrambled[i], descrambled[i]);
    }

    return 0;
}
