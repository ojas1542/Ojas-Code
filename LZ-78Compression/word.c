#include "word.h"
#include "code.h"
#include <stdio.h>
#include <stdlib.h>

// Create word
Word *word_create(uint8_t *syms, uint64_t len) {
  Word *w = (Word *)malloc(sizeof(Word));
  if (w) {
    w->len = len; // Lenght of words
    if (w->len >
        0) { // Only initialize list of symbols in word if len greater than 0
      w->syms = (uint8_t *)calloc(
          w->len, sizeof(uint8_t)); // allocate memory to symbols list
      if (w->syms) {
        for (uint64_t i = 0; i < len; i++) {
          w->syms[i] = syms[i]; // Set symbols to those passed in
        }
      }
    }
  }
  return w; // Return ptr to word.
}

// Append symbol to word
Word *word_append_sym(Word *w, uint8_t sym) {
  Word *w_appended = NULL; // New word with concatenation
  if (w && w->len != 0) {  // If word passed in exists and isn't empty.
    w_appended = word_create(
        w->syms, w->len + 1); // Create new word the length of original word+1
    if (w_appended && w_appended->syms) {
      w_appended->syms[w->len] = sym; // Copy symbol to append to word
    }
  } else {                             // if word is empty or NULL
    w_appended = word_create(&sym, 1); // Create word for symbol
  }

  return w_appended; // return appended word
}

// Delete word
void word_delete(Word *w) {
  if (w != NULL) {
    if (w->syms != NULL) {
      free(w->syms);  // Free memory allocated to word symbols.
      w->syms = NULL; // set ptr to NULL
    }
  }
}

// Create word table
WordTable *wt_create(void) {
  WordTable *wt =
      (WordTable *)calloc(MAX_CODE, sizeof(Word *)); // Allocate memory for it.
  if (wt) {
    wt[EMPTY_CODE] = word_create(0, 0); // Initialize table with empty word.
  }
  return wt; // return wordtable ptr
}

// Reset word table to empty word.
void wt_reset(WordTable *wt) {
  for (uint64_t k = 2; k < MAX_CODE; k++) { // Iterate over word table entries.
    word_delete(wt[k]);                     // Delete word in word table
    free(wt[k]);                            // Free memory allocated to word.
    wt[k] = NULL;                           // Set to NULL
  }
  return;
}

// Delete word table
void wt_delete(WordTable *wt) {
  for (uint64_t k = 0; k < MAX_CODE; k++) { // Iterate over table
    if (wt[k] != NULL) {                    // Check if word at index exists
      word_delete(wt[k]);                   // Delete word
      free(wt[k]);                          // Free memory allocated to word.
      wt[k] = NULL;                         // Set to NULL
    }
  }
  free(wt);  // Free memory allocated to wordtable
  wt = NULL; // set ptr to NULL

  return;
}
