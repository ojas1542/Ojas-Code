#include "hash.h"

HashTable *ht_create(uint32_t length) {
  HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
  if (ht) {
    ht->salt[0] = 0x85ae998311115ae3;
    ht->salt[1] = 0xb6fac2ae33a40089;
    ht->length = length;
    ht->heads = (ListNode **)calloc(
        length, sizeof(ListNode *)); // List of linked list heads
  }
  return ht;
}

// delete hash table
void ht_delete(HashTable *h) {
  // Delete linked lists
  for (uint32_t k = 0; k < h->length; k++) {
    if (h->heads[k] != NULL) {
      ll_delete(h->heads[k]);
    }
  }
  free(h->heads); // Free ptr to linked list heads.
  h->heads = NULL;
  free(h); // Free hash table ptr.
  h = NULL;
}

// Look up key in hash table
ListNode *ht_lookup(HashTable *h, char *key) {
  uint32_t hash_val =
      hash(h->salt, key) % h->length; // Hash word associated with Goodspeak
  ListNode *search = ll_lookup(&h->heads[hash_val], key);
  return search; // Return NULL if word not found
}

// Insert in hash table
void ht_insert(HashTable *h, GoodSpeak *gs) {
  uint32_t hash_val = hash(h->salt, gs->oldspeak) %
                      h->length; // Hash word associated with Goodspeak
  ListNode *search =
      ll_lookup(&h->heads[hash_val],
                gs_oldspeak(gs)); // Check if word already in hastable
  if (search == NULL) {
    ll_insert(&h->heads[hash_val],
              gs); // If not in hastable, then insert through linked list.
  }
}

// Count all hash indices with a non NULL head node.
uint32_t ht_count(HashTable *h) {
  uint32_t count = 0;
  for (uint32_t k = 0; k < h->length; k++) {
    if (h->heads[k] != NULL) { // check if head at hash index is not NULL
      count++;
    }
  }
  return count; // Return number of non-NULL hash indices with a head node.
}

// Print hashtable
void ht_print(HashTable *h) {
  for (uint32_t k = 0; k < h->length; k++) {
    ListNode *temp = h->heads[k];
    while (temp != NULL) { // If linked list exists
      printf("Hash Value: %u Key: %s ", k,
             temp->gs->oldspeak); // Print all nodes hashed to each key
      temp = temp->next;
    }
    if (temp == NULL && h->heads[k] != NULL) {
      printf("\n");
    } // NEw line for every new hash index.
  }
}
