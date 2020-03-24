#ifndef __SHELL_H__
#define __SHELL_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

bool swap_shell(uint32_t array[], uint32_t curr_index, uint32_t curr_gap,
                uint32_t *comparison);
void shellsort(uint32_t array[], uint32_t *comparison, uint32_t *swaps,
               uint32_t array_len);
uint32_t gap(uint32_t n);

#endif
