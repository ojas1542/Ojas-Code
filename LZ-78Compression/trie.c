#include "trie.h"
#include "code.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

// Create trie node
TrieNode *trie_node_create(uint16_t code) {
  TrieNode *tn =
      (TrieNode *)malloc(sizeof(TrieNode)); // Allocate memory to trie node
  if (tn) {
    tn->code = code; // Set code for trie node to passed in value.
    for (int k = 0; k < ALPHABET; k++) {
      tn->children[k] = NULL; // Initialize trie children to NULL
    }
  }
  return tn; // Return trie node pointer
}

// Delete trie node
void trie_node_delete(TrieNode *n) {
  if (n) {
    free(n);  // Free memory allocated to trie node.
    n = NULL; // Set to NULL
  }
  return;
}

// Create trie
TrieNode *trie_create(void) {
  TrieNode *root =
      trie_node_create(EMPTY_CODE); // Initialize trie with root node.
  return root;                      // return ptr to root node.
}

// Reset trie to root node.
void trie_reset(TrieNode *root) {
  if (root) {
    for (uint32_t k = 0; k < ALPHABET; k++) { // Iterate over root's children
      if (root->children[k] != NULL) {        // Check if it exists
        trie_delete(
            root->children[k]);   // Delete the child including it's sub trie.
        root->children[k] = NULL; // Set child ptr to NULL
      }
    }
  }
  return;
}

// Delete trie
void trie_delete(TrieNode *n) {
  for (uint32_t k = 0; k < ALPHABET;
       k++) { // Iterate over children nodes of node passed in.
    if (n->children[k] != NULL) {  // if they exist
      trie_delete(n->children[k]); // step through their children until reaching
                                   // end of trie
    }
  }
  trie_node_delete(n); // Delete node
  n = NULL;            // Set to null
  return;
}

// Return node at index sym.
TrieNode *trie_step(TrieNode *n, uint8_t sym) { return n->children[sym]; }
