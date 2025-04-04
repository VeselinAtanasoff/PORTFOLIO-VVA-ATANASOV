#include "../include/BitManipulation.h"
#include <string.h>
#include <stdint.h>

void combine_nibbles_to_byte(uint8_t *byte, uint8_t high_nibble, uint8_t low_nibble)
{
    *byte = (high_nibble << 4) | low_nibble;
}   

void swap_bytes_in_word(uint16_t word, uint16_t *swapped_word)
{
    *swapped_word = ((word & 0x00FF) << 8) | ((word & 0xFF00) >> 8);
}

void create_mask_for_byte(uint8_t position, uint8_t length, uint8_t *mask)
{
    *mask = 0;
    for (int i = 0; i < length; i++)
    {
        *mask |= (1 << (position + i));
    }
}

void manipulate_bits_in_byte(char mode[], uint8_t byte, uint8_t mask, uint8_t *masked_byte)
{
    if (strcmp(mode, "set") == 0)
    {
        *masked_byte = byte | mask;
    }
    else if (strcmp(mode, "clear") == 0)
    {
        *masked_byte = byte & ~mask;
    }
    else if (strcmp(mode, "flip") == 0)
    {
        *masked_byte = byte ^ mask;
    }
    else
    {
        *masked_byte = byte;
    }
}