#ifndef BITMANIPULATION_H
#define BITMANIPULATION_H
#include <stdint.h>
#include <stdbool.h>

uint8_t combine_nibbles_to_byte(uint8_t high_nibble, uint8_t low_nibble);
uint16_t swap_bytes_in_word(uint16_t word);
uint8_t create_mask_for_byte(uint8_t position, uint8_t length);
bool check_bit_in_byte(uint8_t word, uint8_t position);
uint8_t manipulate_bits_in_byte(char mode[], uint8_t byte, uint8_t mask);
uint8_t count_ones_in_high_nibble(uint8_t byte);

#endif