#ifndef __BINARY_H__
#define __BINARY_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

bool swap_binary(uint32_t array[], uint32_t curr_index, uint32_t search_val,
                 uint32_t *comparison);
void binarysort(uint32_t array[], uint32_t *comparison, uint32_t *swaps,
                uint32_t array_len);

#endif
