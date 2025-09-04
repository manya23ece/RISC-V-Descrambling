#include <stdio.h>
#include <riscv_vector.h>
#include <printf.h>

void scramble_vector(const int *input, const int *key, int *scrambled, int bit_count, size_t n) {
    size_t vl;
    int modulo_val = 1 << bit_count; // 2^bit_count

    for (size_t i = 0; i < n; i += vl) {
        vl = vsetvl_e32m1(n - i);  // Set vector length

        vint32m1_t vin = vle32_v_i32m1(&input[i], vl);
        vint32m1_t vkey = vle32_v_i32m1(&key[i], vl);

        vint32m1_t vsum = vadd_vv_i32m1(vin, vkey, vl);
        vint32m1_t vmod = vrem_vx_i32m1(vsum, modulo_val, vl);

        vse32_v_i32m1(&scrambled[i], vmod, vl);
    }
}

void descramble_vector(const int *scrambled, const int *key, int *descrambled, int bit_count, size_t n) {
    size_t vl;
    int modulo_val = 1 << bit_count;

    for (size_t i = 0; i < n; i += vl) {
        vl = vsetvl_e32m1(n - i);

        vint32m1_t vscr = vle32_v_i32m1(&scrambled[i], vl);
        vint32m1_t vkey = vle32_v_i32m1(&key[i], vl);

        vint32m1_t vsub = vsub_vv_i32m1(vscr, vkey, vl);
        vint32m1_t vmod = vrem_vx_i32m1(vsub, modulo_val, vl);

        vbool32_t vmask = vmslt_vx_i32m1_b32(vmod, 0, vl);  // mask: vmod < 0
        vint32m1_t vcorrected = vadd_vx_i32m1(vmod, modulo_val, vl);  // add 2^bit_count to negatives

        // Correct usage: mask goes FIRST
        vint32m1_t vfinal = vmerge_vvm_i32m1(vmask, vcorrected, vmod, vl);

        vse32_v_i32m1(&descrambled[i], vfinal, vl);
    }
}



int main() {
    int input[4] = {10, 12, 3, 7};
    int key[4] = {5, 7, 2, 1};
    int scrambled[4], descrambled[4];
    int bit_count = 4;

    size_t n = 4;

    scramble_vector(input, key, scrambled, bit_count, n);
    descramble_vector(scrambled, key, descrambled, bit_count, n);

    for (size_t i = 0; i < n; i++) {
        printf("Input: %d, Key: %d, Scrambled: %d, Descrambled: %d\n",
               input[i], key[i], scrambled[i], descrambled[i]);
    }

    return 0;
}
