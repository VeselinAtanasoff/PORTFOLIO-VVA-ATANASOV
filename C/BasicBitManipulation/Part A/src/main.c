#include "../include/BitManipulation.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

void print_binary(uint8_t value) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
    }
    printf("\n");
}

void test_combine_nibbles_to_byte() {
    uint8_t high_nibble = 0x0A;
    uint8_t low_nibble = 0x05;
    uint8_t byte = combine_nibbles_to_byte(high_nibble, low_nibble);
    printf("Combine nibbles to byte: %X\n", byte);
}

void test_swap_bytes_in_word() {
    uint16_t word = 0x0A05;
    uint16_t swapped_word = swap_bytes_in_word(word);
    printf("Swap bytes in word: %X\n", swapped_word);
}

void test_create_mask_for_byte() {
    uint8_t position = 3;
    uint8_t length = 4;
    uint8_t mask = create_mask_for_byte(position, length);
    printf("Create mask for byte: ");
    print_binary(mask);
}

void test_manipulate_bits_in_byte() {
    uint8_t binary_byte = 0b11101010;
    uint8_t position = 3;
    uint8_t length = 4;
    uint8_t mask = create_mask_for_byte(position, length);
    uint8_t manipulated_byte_set = manipulate_bits_in_byte("set", binary_byte, mask);
    uint8_t manipulated_byte_clear = manipulate_bits_in_byte("clear", binary_byte, mask);
    uint8_t manipulated_byte_flip = manipulate_bits_in_byte("flip", binary_byte, mask);
    printf("Manipulate bits in byte (set): ");
    print_binary(manipulated_byte_set);
    printf("Manipulate bits in byte (clear): ");
    print_binary(manipulated_byte_clear);
    printf("Manipulate bits in byte (flip): ");
    print_binary(manipulated_byte_flip);
}

void test_check_bit_in_byte() {
    uint8_t mask = 0b00001000;
    uint8_t boolPosition = 1;
    if (check_bit_in_byte(mask, boolPosition))
        printf("Bit at position %d is 1\n", boolPosition);
    else
        printf("Bit at position %d is 0\n", boolPosition);
}

void test_count_ones_in_high_nibble() {
    uint8_t binary_byte = 0b11101010;
    int count = count_ones_in_high_nibble(binary_byte);
    printf("Count ones in high nibble: %d\n", count);
}

int main(int argc, char const *argv[]) {
    test_combine_nibbles_to_byte();
    test_swap_bytes_in_word();
    test_create_mask_for_byte();
    test_manipulate_bits_in_byte();
    test_check_bit_in_byte();
    test_count_ones_in_high_nibble();
    return 0;
}
