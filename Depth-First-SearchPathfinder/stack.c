#include "stack.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
//#include <assert.h>

int s_main(void) { return 0; }

// Create stack object. Used Darrel Long's Code from lecture slides.
Stack *stack_create(void) {
  Stack *s = (Stack *)malloc(sizeof(Stack)); // Allocated memory
  // assert(s);
  if (s != NULL) {         // Check if object is NULL
    s->capacity = MINIMUM; // Set capacity of stack to ateast 26
    s->top = 0;            // Set top of stack.
    s->items = (uint32_t *)calloc(
        MINIMUM, sizeof(uint32_t)); // Allocate memory for stack array.
  }
  return s; // return stack object
}

// Check if stack is empty based on where the top of stack point.
bool stack_empty(Stack *s) {
  if (s->top == 0) {
    return true;
  } else {
    return false; // return is stack is empty.
  }
}

// Delete objects in stack array and then delete stack object to prevent memory
// leaks and seg faults.
void stack_delete(Stack *s) {
  free(s->items); // Free memory used by stack array
  s->items = NULL;
  free(s); // Free memory used by stack object.
  s = NULL;
  return;
}

// Return size of stack based on the top index.
uint32_t stack_size(Stack *s) { return s->top; }

// Push element to top of stack. Used code from Darrell Long's lecture slides.
bool stack_push(Stack *s, uint32_t item) {
  if (s->top == s->capacity) { // checks to see if stack is full.
    s->capacity *= 2; // double the size of the stack if capacity is reached.
    s->items = (uint32_t *)realloc(
        s->items,
        s->capacity * sizeof(uint32_t)); // allocate double the memory.
  }
  if (s->items != NULL) {    // Check to see if stack array is null.
    s->items[s->top] = item; // Push to top
  }
  s->top += 1; // increment stack pointer.
  return true; // Return true if element is pushed successfully.
}
// Remove item from top of stack. Used code from Darrell Long's lecture slides.
bool stack_pop(Stack *s, uint32_t *item) {
  if (stack_empty(s)) { // Don't pop is stack is empty.
    return false;
  } else {
    s->top -= 1;              // Decrement stack pointer.
    item = &s->items[s->top]; // pop element to pointer passed.
    return true;              // Return true if element popped successfully.
  }
}

// Prints elements from stack as is. Separated by new line.
void stack_print(Stack *s) {
  for (uint32_t k = 0; k < s->top; k++) {
    printf("%d\n", s->items[k]);
  }
  return;
}
