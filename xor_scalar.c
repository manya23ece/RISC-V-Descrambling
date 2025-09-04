#include <stdio.h>
#include <printf.h>

// Function to perform XOR operation between two integers
int xor_op(int a, int b) {
    return a ^ b;
}

// Function to print binary representation of a number
void print_binary(int val) {
    for (int i = 7; i >= 0; --i) {
        //printf("%d", (val >> i) & 1);
    }
}

int main() {
    int input[4]     = {10, 15, 8, 5};       // Binary: 1010, 1111, 1000, 0101
    int key[4]       = {13,  7, 3, 5};       // Binary: 1101, 0111, 0011, 0101
    int scrambled[4];
    int descrambled[4];

    // XOR input with key
    for (int i = 0; i < 4; ++i) {
        scrambled[i] = xor_op(input[i], key[i]);
    }

    printf("Scrambled data:\n");
    for (int i = 0; i < 4; ++i) {
        //printf("Decimal: %2d, Binary: ", scrambled[i]);
        //print_binary(scrambled[i]);
        //printf("\n");
    }

    // XOR again to get original input
    for (int i = 0; i < 4; ++i) {
        descrambled[i] = xor_op(scrambled[i], key[i]);
    }

    printf("Descrambled data:\n");
    for (int i = 0; i < 4; ++i) {
        //printf("Decimal: %2d, Binary: ", descrambled[i]);
        //print_binary(descrambled[i]);
        //printf("\n");
    }

    return 0;
}
