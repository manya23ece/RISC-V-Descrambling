#include <stdio.h>
#include <riscv_vector.h>
#include <printf.h>

void xor_vector(const int *input, const int *key, int *output, size_t len) {
    size_t vl;
    size_t i = 0;
    while (i < len) {
        // Set the vector length depending on hardware capability
        vl = vsetvl_e32m1(len - i);

        // Load input and key vectors
        vint32m1_t vec_input = vle32_v_i32m1(&input[i], vl);
        vint32m1_t vec_key   = vle32_v_i32m1(&key[i], vl);

        // XOR operation
        vint32m1_t vec_out = vxor_vv_i32m1(vec_input, vec_key, vl);

        // Store the result
        vse32_v_i32m1(&output[i], vec_out, vl);

        i += vl;
    }
}

int main() {
    int input[4]     = {10, 15, 8, 5};       // Example inputs
    int key[4]       = {13,  7, 3, 5};       // Example keys
    int scrambled[4] = {0};
    int descrambled[4] = {0};

    xor_vector(input, key, scrambled, 4);
    //printf("Scrambled: ");
    for (int i = 0; i < 4; ++i) {
        //printf("%d ", scrambled[i]);
    }
    //printf("\n");

    // Descramble (XOR again with same key)
    xor_vector(scrambled, key, descrambled, 4);
    //printf("Descrambled: ");
    for (int i = 0; i < 4; ++i) {
        //printf("%d ", descrambled[i]);
    }
   // printf("\n");

    return 0;
}
