#include <stdio.h>
//#include <printf.h>
// Function to perform XOR operation between two binary numbers
int xor(int a, int b) {
    return a ^ b;  // XOR operation
}

int main() {
    // Example: Original input in decimal
    int input = 10;  // Binary: 1010
    int key = 13;    // Random key in decimal (Binary: 1101)

    // Scrambling the input using XOR
    int scrambled = xor(input, key);
    printf("Scrambled data: %d (Binary: ", scrambled);
    for (int i = 3; i >= 0; --i) {
       // printf("%d", (scrambled >> i) & 1);  // Printing binary representation
    }
    //printf(")\n");

    // Descrambling the scrambled data using the same key
    int descrambled = xor(scrambled, key);
    printf("Descrambled data: %d (Binary: ", descrambled);
    for (int i = 3; i >= 0; --i) {
      //  printf("%d", (descrambled >> i) & 1);  // Printing binary representation
    }
    //printf(")\n");

    return 0;
}
