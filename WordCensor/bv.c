#include "bv.h"

struct BitVector {
  uint8_t *vector; // Array to hold whether each index value is prime or not.
  uint32_t length; // Lenght of array
};

BitVector *bv_create(uint32_t bit_len) {
  BitVector *bv = (BitVector *)malloc(sizeof(BitVector));
  if (bv != NULL) {
    bv->length = bit_len + 1;
    bit_len = (bit_len / 8) + 1;
    bv->vector = (uint8_t *)calloc(bit_len + 1, sizeof(uint8_t));
  }
  return bv;
}

void bv_delete(BitVector *v) {
  free(v->vector);
  v->vector = NULL;
  free(v);
  v = NULL;
  return;
}

uint32_t bv_length(BitVector *v) { return v->length; }

void bv_set_bit(BitVector *v, uint32_t i) {
  uint32_t vector_index = i / 8;
  uint32_t local_index = i % 8;
  uint32_t shift_index = 7 - local_index;
  // Used Darrell Long's code from Piazza
  v->vector[vector_index] = (v->vector[vector_index] | (0x1 << shift_index));
  return;
}

void bv_clr_bit(BitVector *v, uint32_t i) {
  uint32_t vector_index = i / 8;
  uint32_t local_index = i % 8;
  uint32_t shift_index = 7 - local_index;
  // Used Darrell's Long' code from Piazza.
  v->vector[vector_index] = (v->vector[vector_index] & ~(0x1 << shift_index));
  return;
}

uint8_t bv_get_bit(BitVector *v, uint32_t i) {
  uint32_t vector_index = i / 8;
  uint32_t local_index = i % 8;
  uint32_t shift_index = 7 - local_index;
  return (((v->vector[vector_index] & (0x1 << shift_index))) >> shift_index);
}

void bv_print(BitVector *b) {
  for (uint32_t i = 0; i < bv_length(b); i++) {
    uint32_t bit = bv_get_bit(b, i);
    printf("%u", bit);
  }
}
