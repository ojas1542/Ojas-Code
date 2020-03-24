#ifndef __STACK_H__
#define __STACK_H__

#include <inttypes.h>
#include <stdbool.h>

#define MINIMUM 26

// API based definitions of variables and stack functions.
typedef struct Stack {
  uint32_t *items;
  uint32_t top;
  uint32_t capacity;
} Stack;

Stack *stack_create(void);                // Constructor
void stack_delete(Stack *s);              // Destructor
bool stack_empty(Stack *s);               // Check if empty
uint32_t stack_size(Stack *s);            // Returns numbers of items in stack
bool stack_push(Stack *s, uint32_t item); // Pushes item onto stack and confirms
bool stack_pop(Stack *s, uint32_t *item); // Pop item off stack and confirms
void stack_print(Stack *s);               // prints stack

#endif
