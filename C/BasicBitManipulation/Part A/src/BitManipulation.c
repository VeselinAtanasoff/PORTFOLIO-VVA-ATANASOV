#include "../include/BitManipulation.h"
#include <stdint.h>
#include <stdbool.h>
#define BYTE_SIZE 8

uint8_t combine_nibbles_to_byte(uint8_t high_nibble, uint8_t low_nibble){
    return (high_nibble << 4) | low_nibble;
}

uint16_t swap_bytes_in_word(uint16_t word){
    return (word << 8) | (word >> 8);
}

uint8_t create_mask_for_byte(uint8_t position, uint8_t length){
    uint8_t mask = 0;
    for (uint8_t i = 0; i < length; i++){
        mask |= (1 << (position + i));
    }

    return mask;
}

bool check_bit_in_byte(uint8_t word, uint8_t position){
    uint8_t one_to_compare = 1;
    return (word & create_mask_for_byte(position, one_to_compare)) != 0;
}

uint8_t manipulate_bits_in_byte(char mode[], uint8_t byte, uint8_t mask){
    if (strcmp(mode, "set") == 0) {
        return byte | mask;
    } else if (strcmp(mode, "clear") == 0) {
        return byte & ~mask;
    } else if (strcmp(mode, "flip") == 0) {
        return byte ^ mask;
    } else {
        return 0;
    }
}

uint8_t count_ones_in_high_nibble(uint8_t byte){
    uint8_t count = 0;
    uint8_t position = 4;

    for (position; position < BYTE_SIZE; position){ // Avoid magic numbers
        if (check_bit_in_byte(byte, position)){
            count++;
        }
    }

    return count;
}
