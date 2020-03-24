#include "binary.h"
#include "bubble.h"
#include "quick.h"
#include "shell.h"
#include <ctype.h>
#include <getopt.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define OPTIONS "Absqip:r:n:"

// Bool variables to keep track of which sorts to run.
bool bubble = false;
bool quick = false;
bool binary = false;
bool shell = false;
// Variables to store potential arguments passed with -n -p or -r. Initialized
// with default values.
uint32_t inputPrintElements = 100;
uint32_t inputRandSeed = 8222022;
uint32_t inputNumElements = 100;

// Create and allocate and array of size n
uint32_t *createArray(uint32_t n) {
  uint32_t *array = (uint32_t *)calloc(n, sizeof(uint32_t));
  return array; // Return array creater.
}

// Free memory allocated to array created.
void deleteArray(uint32_t *array) {
  free(array);
  array = NULL;
  return;
}

// Generate 30 bit random numbers
void setrandomGen(uint32_t array_len, uint32_t *array, uint32_t seed) {
  srand(seed);
  uint32_t mask =
      0x3FFFFFFF; // This number will mask all bits but the 31st and 32nd.
  for (uint32_t k = 0; k < array_len; k++) {
    uint32_t rNum = rand(); // Generate random num
    uint32_t masked_value =
        rNum & mask; // Mask with the mask number defined above. Only upto 30th
                     // bit is preserved. Mask and random number are ANDed.
    array[k] = masked_value; // Set value in array.
  }
  return;
}

// Print sorting algorithims based on flags passed in.
void PrintElements(bool bubble, bool binary, bool quick, bool shell,
                   uint32_t *comparison, uint32_t *swaps, uint32_t array_len,
                   uint32_t array[], uint32_t numprint, uint32_t seed) {
  setrandomGen(array_len, array, seed); // Set array to random numbers
  if (binary) { // bool variable is only true if it's respective flag or -A is
                // passed in.
    printf("Binary Insertion Sort\n");
    binarysort(array, comparison, swaps, array_len); // run sort algorithim
    printf("%u elements, %u moves, %u compares\n", array_len, *swaps,
           *comparison);
    if (numprint >
        array_len) { // If user enters a number to print that is
                     // greater than the size of array. Only print all
                     // elements of array.
      numprint = array_len;
    }
    for (uint32_t i = 0; i < numprint;
         i++) { // Iterate over number of indices to print.
      if (i % 7 ==
          0) { // Space before first column in printing. If-statement
               // serves same purpose when called in sorting algorithims
               // below.
        printf("    ");
      }
      printf("%u    ", array[i]);
      if ((i + 1) % 7 == 0) { // 7 columns of per line. If-statement serves same
                              // purpose when called in sorting algorithims
                              // below.
        printf("\n");
      }
    }
    printf("\n");
    *swaps = 0;      // Reset swaps count for next potential sort. Serves same
                     // purpose when called in the next sorting algorithims.
    *comparison = 0; // Reset comparison count for next potential sort. Serves
                     // same purpose when called in the next sorting
                     // algorithims.
  }
  setrandomGen(array_len, array,
               seed); // Set array back to original random
                      // numebr order. Serves same purpose when
                      // called for the sorts below.

  // Comments above apply to sorts below.
  if (quick) {
    printf("Quick sort\n");
    quicksort(array, 0, array_len - 1, comparison, swaps, array_len);
    printf("%u elements, %u moves, %u compares\n", array_len, *swaps,
           *comparison);
    if (numprint > array_len) {
      numprint = array_len;
    }

    for (uint32_t i = 0; i < numprint; i++) {
      if (i % 7 == 0) {
        printf("    ");
      }

      printf("%u    ", array[i]);
      if ((i + 1) % 7 == 0) {
        printf("\n");
      }
    }
    printf("\n");
    *swaps = 0;
    *comparison = 0;
  }
  setrandomGen(array_len, array, seed);

  if (shell) {
    printf("Shell sort\n");
    shellsort(array, comparison, swaps, array_len);
    printf("%u elements, %u moves, %u compares\n", array_len, *swaps,
           *comparison);
    if (numprint > array_len) {
      numprint = array_len;
    }

    for (uint32_t i = 0; i < numprint; i++) {
      if (i % 7 == 0) {
        printf("    ");
      }

      printf("%u    ", array[i]);
      if ((i + 1) % 7 == 0) {
        printf("\n");
      }
    }
    *swaps = 0;
    *comparison = 0;
    printf("\n");
  }
  setrandomGen(array_len, array, seed);

  if (bubble) {
    printf("Bubble sort\n");
    bubblesort(array, comparison, swaps, array_len);
    printf("%u elements, %u moves, %u compares\n", array_len, *swaps,
           *comparison);
    if (numprint > array_len) {
      numprint = array_len;
    }

    for (uint32_t i = 0; i < numprint; i++) {
      if (i % 7 == 0) {
        printf("    ");
      }

      printf("%u    ", array[i]);
      if ((i + 1) % 7 == 0) {
        printf("\n");
      }
    }
  }
  *swaps = 0;
  *comparison = 0;
  printf("\n");
  return;
}

int main(int argc, char **argv) {
  int choice = 0;
  while ((choice = getopt(argc, argv, OPTIONS)) != -1) {
    switch (choice) {
    // Flag for running all sorts.
    case 'A':
      bubble = true;
      quick = true;
      shell = true;
      binary = true;
      break;
    // Run bubble sort.
    case 'b':
      bubble = true;
      break;
    case 's':
      // Run shell sort.
      shell = true;
      break;
    case 'q':
      // Run quick sort.
      quick = true;
      break;
    case 'i':
      // Run binary insertion sort.
      binary = true;
      break;
    case 'p':
      // Store number of elements to print if passed in.
      inputPrintElements = (uint32_t)atoi(optarg);
      break;
    case 'r':
      // Store random seed if passed in
      inputRandSeed = (uint32_t)atoi(optarg);
      break;
    case 'n':
      // Store size of array if passed in .
      inputNumElements = (uint32_t)atoi(optarg);
      break;
    default:
      printf("Use README file for help with choosing options appropriately.\n");
      break;
    }
  }

  uint32_t *array = createArray(
      inputNumElements);   // Create instance of array with supplied size.
  uint32_t comparison = 0; // Comparison counter.
  uint32_t swaps = 0;      // Swap counter

  // Sort and print algorithims accordingly
  PrintElements(bubble, binary, quick, shell, &comparison, &swaps,
                inputNumElements, array, inputPrintElements, inputRandSeed);

  // Delete array instance
  deleteArray(array);
  return 0;
}
