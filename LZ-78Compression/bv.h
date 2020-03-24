#ifndef __BV_H__
#define __BV_H__

#include <inttypes.h>
#include <stdbool.h>

typedef struct BitVector {
  uint8_t *vector; // Array to hold whether each index value is prime or not.
  uint32_t length; // Lenght of array
} BitVector;

BitVector *bv_create(uint32_t bit_len); // Create bitvector.

void bv_delete(BitVector *v); // Delete bitvector.

uint32_t bv_get_len(BitVector *v); // Get bitvector length.

void bv_set_bit(BitVector *v, uint32_t i); // Set bit for given value to 1

void bv_clr_bit(BitVector *v, uint32_t i); // Set bit for given value to 0

uint8_t bv_get_bit(BitVector *v,
                   uint32_t); // Get value of bit for given index value.

void bv_set_all_bits(BitVector *v); // Set all bits in bitvector to 1

#endif
