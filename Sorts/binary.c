#include "binary.h"

// Check whether elements need to be swapped.
bool swap_binary(uint32_t array[], uint32_t curr_index, uint32_t searchVal,
                 uint32_t *comparison) {
  bool swap = false;
  if (searchVal >= array[curr_index]) {
    swap = true;
  }
  *comparison = *comparison +
                1; // Comparison counter incremented everytime function is run.
  return swap; // Return if swap needs to be made. True = yes, false otherwise.
}

// Based on pseudocode by Darrell Long
void binarysort(uint32_t array[], uint32_t *comparison, uint32_t *swaps,
                uint32_t array_len) {
  for (uint32_t i = 1; i < array_len;
       i++) { // For loop iterating over all search elements.
    uint32_t searchVal = array[i]; // Set 1st index value to search value
    uint32_t left = 0;
    uint32_t right = i;

    while (left < right) { // Perform binary search on selected value to find
                           // it's place in list.
      uint32_t mid = left + ((right - left) / 2);
      if (swap_binary(array, mid, searchVal,
                      comparison)) { // Check if selected number is greater than
                                     // current iterator value. Break up search
                                     // list further appropriately.
        left = mid + 1; // Adjust search boundary if element is to be placed on
                        // the right.
      } else {
        right = mid;
      }
    }
    for (uint32_t k = i; k > left;
         k--) { // Swap values accordingly when the position
      uint32_t temp = array[k - 1];
      array[k - 1] = array[k];
      array[k] = temp;
      *swaps = *swaps + 3;
    }
  }
  return;
}
