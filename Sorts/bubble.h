#ifndef __BUBBLE_H__
#define __BUBBLE_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

bool swap_bubble(uint32_t array[], uint32_t curr_index, uint32_t *comparison);
void bubblesort(uint32_t array[], uint32_t *comparison, uint32_t *swaps,
                uint32_t array_len);

#endif
