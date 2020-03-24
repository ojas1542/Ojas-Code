#include "bubble.h"

// Checks for swapping condition.
bool swap_bubble(uint32_t array[], uint32_t curr_index, uint32_t *comparison) {
  bool swap = false;
  if (array[curr_index] <
      array[curr_index - 1]) { // Checks for swapping condition
    swap = true;
  }
  *comparison = *comparison + 1; // Increment swap counter regardless of the
                                 // whether it's true or false to count for
                                 // comparison made.
  return swap; // Returns true if swapping condition true so the swap can
               // actually be done.
}

// Based on pseducode by Darrell Long
void bubblesort(uint32_t array[], uint32_t *comparison, uint32_t *swaps,
                uint32_t array_len) {
  for (uint32_t i = 0; i < array_len - 1; i++) { // Iterator over runs of search
    for (uint32_t j = array_len - 1; j > i;
         j--) { // For loop iterating over all potential swaps
      if (swap_bubble(array, j,
                      comparison)) { // Check if condition for swap it true
                                     // based on defined function.
        // Swap elements
        uint32_t temp = array[j];
        array[j] = array[j - 1];
        array[j - 1] = temp;
        *swaps = *swaps + 3;
      }
    }
  }

  return;
}
