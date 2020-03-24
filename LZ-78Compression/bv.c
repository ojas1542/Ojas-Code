#include "bv.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

BitVector *bv_create(uint32_t bit_len) {
  BitVector *bv = (BitVector *)malloc(
      sizeof(BitVector)); // Allocate memory to bitvector object pointer.
  if (bv != NULL) {       // Check if object is null
    bv->length = bit_len; // Set length of array to lenght value passed in.
    bit_len = (bit_len / 8) +
              1; // compute bytes to allocate given the amount of bits needed.
    bv->vector = (uint8_t *)calloc(
        bit_len, sizeof(uint8_t)); // Allocate memory of the size of bytes
                                   // determined above for the vector array
                                   // of bits.
  }
  return bv; // Return bv pointer object
}

void bv_delete(BitVector *v) {
  free(v->vector);  // Free memory allocated to vector array.
  v->vector = NULL; // Set pointer to null
  free(v);          // Free memory allocated to bitvector object pointer.
  v = NULL;         // Set bitvector object pointer to null
  return;
}

uint32_t bv_get_len(BitVector *v) {
  return v->length;
} // return amount of bits stored in bitvector.

void bv_set_bit(BitVector *v, uint32_t i) {
  uint32_t vector_index = i / 8; // Calculate index of vector array which
                                 // contains the bit associated with passed in i
                                 // value.
  uint32_t local_index = i % 8; // Calculate index of bit associated with passed
                                // in i value locally within the uint8_t.
  uint32_t shift_index =
      7 -
      local_index; // Amount by which to shift 0x1 to modify the certain bit.
  // Based on Darrell Long's code on sets from Piazza
  v->vector[vector_index] = (v->vector[vector_index] |
                             (0x1 << shift_index)); // the uint8t is ORed
                                                    // with 0x1 which is
                                                    // shifted to where the 1
                                                    // lines up with the bit
                                                    // to set.
  return;
}

void bv_clr_bit(BitVector *v, uint32_t i) {
  uint32_t vector_index = i / 8; // Calculate index of vector array which
                                 // contains the bit associated with passed in i
                                 // value.
  uint32_t local_index = i % 8; // Calculate index of bit associated with passed
                                // in i value locally within the uint8_t.
  uint32_t shift_index =
      7 -
      local_index; // Amount by which to shift 0x1 to modify the certain bit.
  // Based on Darrell's Long' code on sets from Piazza.
  v->vector[vector_index] =
      (v->vector[vector_index] &
       ~(0x1 << shift_index)); // the uint8t with the desired bit is ANDded with
                               // the opposite of 0x1 which is shifted to where
                               // the 1 lines up with the bit to clear.
  return;
}

uint8_t bv_get_bit(BitVector *v, uint32_t i) {
  // variables set below have the same purpose as the functions defined above.
  uint32_t vector_index = i / 8;
  uint32_t local_index = i % 8;
  uint32_t shift_index = 7 - local_index;
  return (((v->vector[vector_index] & (0x1 << shift_index))) >>
          shift_index); // the uint8t with the desired bit is ANDded with the
                        // 0x1 which is shifted to where the 1 lines up with the
                        // desired bit to preserve. Next the uint8t is then
                        // shifted to the right so the preserved bit is the
                        // least significant bit. So the return value is the
                        // value of the preserved bit which is 1 or 0
}

void bv_set_all_bits(BitVector *v) {
  // For loop iterating over the amount of bits in the Bitvector
  for (uint32_t i = 0; i < v->length; i++) {
    // Variables set below have the same purpose as the function bv_set_bit and
    // bv_clr_bit
    uint32_t vector_index = i / 8;
    uint32_t local_index = i % 8;
    uint32_t shift_index = 7 - local_index;

    v->vector[vector_index] =
        (v->vector[vector_index] |
         (0x1 << shift_index)); // Same operation as bv_set_bit()
  }
  return;
}
