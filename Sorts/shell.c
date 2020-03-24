#include "shell.h"

bool swap_shell(uint32_t array[], uint32_t curr_index, uint32_t curr_gap,
                uint32_t *comparison) {
  bool swap = false;
  if (array[curr_index] <
      array[curr_index - curr_gap]) { // Check if value at current index is less
                                      // than an element within the gap of
                                      // comparison.
    swap = true;
  }
  *comparison =
      *comparison +
      1;       // Increment when function is called since comparison is made.
  return swap; // return is swap should be made.
}

// Based on pseudocode by Darrell Long
uint32_t gap(uint32_t n) {
  static uint32_t gap = -1; // Static variable to store gap generated. Next gap
                            // will be based on this stored gap when function is
                            // called.
  if ((int)gap == -1) { // Exception case for when function is called for the
                        // first time so first gap is generated based on array
                        // length passed in.
    gap = n;
    gap = (5 * gap) / 11; // Gap sequence used for this program.
  } else if (gap <= 2) {
    gap = 1;
  } else {
    gap = (5 * gap) / 11;
  }
  return gap; // return next gap.
}

// Based on pseudocode provided by Darrell Long.
void shellsort(uint32_t array[], uint32_t *comparison, uint32_t *swaps,
               uint32_t array_len) {
  uint32_t curr_gap = 0;
  do {
    curr_gap = gap(array_len);
    for (uint32_t i = curr_gap; i < array_len;
         i++) { // For loop iterating over first element to compare.
      for (uint32_t j = i; j > curr_gap - 1;
           j -= curr_gap) { // Element iteraing over all elements in the
                            // comparison gap.
        if (swap_shell(array, j, curr_gap,
                       comparison)) { // Check if swapping
                                      // condition is met. If
                                      // so, swap.
          uint32_t temp = array[j];
          array[j] = array[j - curr_gap];
          array[j - curr_gap] = temp;
          *swaps = *swaps + 3;
        }
      }
    }
  } while (curr_gap > 1); // Run till the next gap generated is less than 1.
  return;
}
