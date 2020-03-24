#include "quick.h"

// Check if element should be swapped in to the partitioned list with values
// greater than pivot value.
bool swap_high(uint32_t array[], uint32_t high_index, uint32_t pivot,
               uint32_t *comparison) {
  bool swap = false;
  if (array[high_index] >=
      pivot) { // Check if element is greater than or equal to pivot
    swap = true;
  }
  *comparison = *comparison + 1; // Increment counter everytime function is run.
                                 // Serves same purpose as for swap_low()
                                 // defintion below.
  return swap; // return if element should be swapped. //serves same function as
               // for swap_low() definition below.
}

// Check if element should be swapped in to the partitioned list with values
// less than pivot value.
bool swap_low(uint32_t array[], uint32_t low_index, uint32_t pivot,
              uint32_t *comparison) {
  bool swap = false;
  if (array[low_index] < pivot) { // Check if element is less than pivot.
    swap = true;
  }
  *comparison = *comparison + 1;
  return swap;
}

// Paritition list with respect to values greater than or equal to and less than
// the pivot value. Based on pseducode by Darrell Long
uint32_t Partition(uint32_t array[], uint32_t left, uint32_t right,
                   uint32_t *comparison, uint32_t *swaps) {
  uint32_t pivot = array[left];  // Pivot value selected as leftmost element.
  uint32_t low_index = left + 1; // Set low index of partition
  uint32_t high_index = right;   // Set high index of partition.

  // nested while loop to determine the the high and low index.
  // Counter decrements by 1 till value at high index is greater than equal
  // pivot value and high index determined comes after low index.
  while (1 != 0) {
    while (low_index <= high_index &&
           swap_high(array, high_index, pivot,
                     comparison)) { // array[high_index] >= pivot
      high_index -= 1;
    }
    // Counter increment till value at low index is less than pivot value and
    // low index comes before high index.
    while (low_index <= high_index &&
           swap_low(array, low_index, pivot,
                    comparison)) { // array[low_index] <= pivot
      low_index += 1;
    }
    if (low_index <= high_index) { // If partition is set properly with the low
                                   // index coming before high index then swap.
      uint32_t temp = array[low_index];
      array[low_index] = array[high_index];
      array[high_index] = temp;
      *swaps = *swaps + 3;
    } else { // If no more paritions of at least size 1 can be made, then
             // terminate loop.
      break;
    }
  }

  // Swap rest of the values accoridingly when all possible partitions are made.
  uint32_t temp1 = array[left];
  array[left] = array[high_index];
  array[high_index] = temp1;
  *swaps = *swaps + 3;
  return high_index; // Return high index of partition made.
}

// quick sort function that runs partition accordingly.
// Based on pseudocode by Darrell Long
void quicksort(uint32_t array[], uint32_t left, uint32_t right,
               uint32_t *comparison, uint32_t *swaps, uint32_t array_len) {
  if (left < right) { // if array indices are passed in correctly, the run
                      // partitioning.
    uint32_t partition_index = Partition(array, left, right, comparison,
                                         swaps); // Create partitioning.
    if (partition_index >= 1) { // Only call quicksort recursively if
                                // partition_index is still a number greater
                                // than equal to 1 so program doesn't try
                                // looking for invalid index.
      quicksort(array, left, partition_index - 1, comparison, swaps, array_len);
    }
    if (partition_index <=
        array_len - 1) { // Only call quicksort recursively if partition_index
                         // is still a number less than array length - 1 so
                         // program doesn't try accesing memory at an index not
                         // allocated to it's array
      quicksort(array, partition_index + 1, right, comparison, swaps,
                array_len);
    }
  }
  return;
}
