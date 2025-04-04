#include "../include/BitManipulation.h"
#include <string.h>
#include <stdint.h>
#include <stdio.h>

void print_binary(uint8_t value) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
    }
    printf("\n");
}

void test_combine_nibbles_to_byte() {
    uint8_t byte;
    uint8_t* byte_ptr = &byte;
    uint8_t high_nibble = 0x0A;
    uint8_t low_nibble = 0x05;
    combine_nibbles_to_byte(&byte, high_nibble, byte_ptr);
    printf("Combined nibbles: 0x%X\n", *byte_ptr);
    
}

void test_swap_bytes_in_word() {
    uint16_t word = 0xABCD;
    uint16_t swapped_word;
    uint16_t* swapped_word_ptr = &swapped_word;
    swap_bytes_in_word(word, swapped_word_ptr);
    printf("Swapped word: 0x%04X\n", *swapped_word_ptr);
}

void test_create_mask_for_byte() {
    uint8_t position = 3;
    uint8_t length = 4;
    uint8_t mask;
    uint8_t* mask_ptr = &mask;
    create_mask_for_byte(position, length, mask_ptr);
    printf("Mask:");
    print_binary(*mask_ptr);
}

void test_manipulate_bits_in_byte() {
    char mode_set[] = "set";
    uint8_t byte_to_manipulate = 0b00110100;
    uint8_t mask_to_apply = 0b00001111;
    uint8_t masked_byte;
    uint8_t* masked_byte_ptr = &masked_byte;
    manipulate_bits_in_byte(mode_set, byte_to_manipulate, mask_to_apply, masked_byte_ptr);
    printf("Manipulated byte(set):");
    print_binary(*masked_byte_ptr);
    char mode_clear[] = "clear";
    manipulate_bits_in_byte(mode_clear, byte_to_manipulate, mask_to_apply, masked_byte_ptr);
    printf("Manipulated byte(clear):");
    print_binary(*masked_byte_ptr);
    char mode_flip[] = "flip";
    manipulate_bits_in_byte(mode_flip, byte_to_manipulate, mask_to_apply, masked_byte_ptr);
    printf("Manipulated byte(flip):");
    print_binary(*masked_byte_ptr);

}

int main()
{
    test_combine_nibbles_to_byte();
    test_swap_bytes_in_word();
    test_create_mask_for_byte();
    test_manipulate_bits_in_byte();

    return 0;
}


