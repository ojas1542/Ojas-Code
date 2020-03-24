#ifndef __QUICK_H__
#define __QUICK_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

bool swap_high(uint32_t array[], uint32_t high_index, uint32_t pivot,
               uint32_t *comparison);
bool swap_low(uint32_t array[], uint32_t low_index, uint32_t pivot,
              uint32_t *comparison);
uint32_t Partition(uint32_t array[], uint32_t left, uint32_t right,
                   uint32_t *comparison, uint32_t *swaps);
void quicksort(uint32_t array[], uint32_t left, uint32_t right,
               uint32_t *comparision, uint32_t *swaps, uint32_t array_len);

#endif
