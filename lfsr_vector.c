#include <stdio.h>
#include <stdint.h>
#include <riscv_vector.h>
#include <printf.h>

// Vectorized LFSR feedback: (bit3 ^ bit5)
vuint16m1_t lfsr_feedback_vec(vuint16m1_t state, size_t vl) {
    vuint16m1_t bit3 = vand_vx_u16m1(vsrl_vx_u16m1(state, 2, vl), 1, vl);
    vuint16m1_t bit5 = vand_vx_u16m1(vsrl_vx_u16m1(state, 4, vl), 1, vl);
    return vxor_vv_u16m1(bit3, bit5, vl);
}

// Vectorized scramble function
void scramble_vec(uint16_t *input, uint16_t *output, size_t n) {
    size_t vl;
    for (size_t i = 0; i < n; i += vl) {
        vl = vsetvl_e16m1(n - i);
        vuint16m1_t vin = vle16_v_u16m1(&input[i], vl);
        vuint16m1_t feedback = lfsr_feedback_vec(vin, vl);
        vuint16m1_t shifted_feedback = vsll_vx_u16m1(feedback, 1, vl);
        vuint16m1_t scrambled = vxor_vv_u16m1(vin, shifted_feedback, vl);
        vse16_v_u16m1(&output[i], scrambled, vl);
    }
}

// Vectorized descramble function
void descramble_vec(uint16_t *input, uint16_t *output, size_t n) {
    size_t vl;
    for (size_t i = 0; i < n; i += vl) {
        vl = vsetvl_e16m1(n - i);
        vuint16m1_t vin = vle16_v_u16m1(&input[i], vl);
        vuint16m1_t feedback = lfsr_feedback_vec(vin, vl);
        vuint16m1_t shifted_feedback = vsll_vx_u16m1(feedback, 1, vl);
        vuint16m1_t descrambled = vxor_vv_u16m1(vin, shifted_feedback, vl);
        vse16_v_u16m1(&output[i], descrambled, vl);
    }
}

int main() {
    uint16_t input_data[8] = {0xD671, 0x1234, 0xFFFF, 0x0001, 0xA5A5, 0x5A5A, 0x0F0F, 0xF0F0};
    uint16_t scrambled_data[8];
    uint16_t descrambled_data[8];

    scramble_vec(input_data, scrambled_data, 8);
    descramble_vec(scrambled_data, descrambled_data, 8);

    for (int i = 0; i < 8; i++) {
        printf("Input: 0x%04X, Scrambled: 0x%04X, Descrambled: 0x%04X\n",
               input_data[i], scrambled_data[i], descrambled_data[i]);
    }

    return 0;
}
