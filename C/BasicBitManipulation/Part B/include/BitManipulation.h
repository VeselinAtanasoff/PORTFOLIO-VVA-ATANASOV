#ifndef BIT_MANIPULATION_H
#define BIT_MANIPULATION_H
#include <stdint.h>

void combine_nibbles_to_byte(uint8_t *byte, uint8_t high_nibble, uint8_t low_nibble);   
void swap_bytes_in_word(uint16_t word, uint16_t* swapped_word);
void create_mask_for_byte(uint8_t position, uint8_t length, uint8_t* mask);
void manipulate_bits_in_byte(char mode[], uint8_t byte, uint8_t mask, uint8_t* masked_byte);

#endif // BIT_MANIPULATION_H
