#include "ll.h"

uint32_t lookups = 0; // seeks
uint32_t links = 0;   // linked list nodes travelled

ListNode *ll_node_create(GoodSpeak *gs) {
  ListNode *ln = (ListNode *)malloc(sizeof(ListNode));
  if (ln != NULL) {
    ln->gs =
        gs_create(gs->oldspeak, gs->newspeak); // Create goodspeak ptr for node.
    ln->next = NULL; // Set next node ptr to NULL by default.
  }
  return ln;
}

// delete node
void ll_node_delete(ListNode *n) {
  if (n != NULL) { // if node exists, free associated goodspeak ptr
    if (n->gs != NULL) {
      gs_delete(n->gs);
    }
    free(n); // free node ptr.
    n = NULL;
  }
  return;
}

// Delete linked list.
void ll_delete(ListNode *head) {
  ListNode *search = head; // Save head of node.
  while (search != NULL) { // Check if node is NULL
    ListNode *dup_node =
        search; // Save to another node to iterate over each node in list.
    search = search->next;    // Move to next node for next iteration.
    ll_node_delete(dup_node); // Delete current node.
  }
  return;
}

// Insert to linked list.
ListNode *ll_insert(ListNode **head, GoodSpeak *gs) {
  if (ll_lookup(head, gs_oldspeak(gs)) ==
      NULL) { // check if node already in linked list.
    ListNode *new_node = ll_node_create(gs); // Create node for new GoodSpeak
    if (*head != NULL &&
        new_node != NULL) {   // If not the first node in linked list.
      new_node->next = *head; // Set next node to current head
      *head = new_node;       // New node is the new head.
      return *head;           // return head of linked list
    } else {                  // If first node in linked list.
      new_node->next = NULL;  // Set next node to NULL
      *head = new_node;       // Set new node as head of linked list
      return *head;           // return head of linked list.
    }
  }
  return NULL;
}

// Search linked list.
ListNode *ll_lookup(ListNode **head, char *key) {
  lookups++;                    // Count number of seeks
  ListNode *head_saved = *head; // save current head value
  ListNode *node_prev = NULL;   // save node before node with key
  ListNode *node_return = NULL;
  if (*head && key) {
    ListNode *search = *head;
    while (search != NULL && strcmp(search->gs->oldspeak, key) !=
                                 0) { // iterate till node with key is found
      if (search->next != NULL) {
        if (strcmp(search->next->gs->oldspeak, key) ==
            0) { // If the next nodes oldspeak is the key passed in, then save
                 // the previous_node
          node_prev = search;
        }
      }
      search = search->next;
      links++; // Count nodes traversed.
    }
    node_return = search;
    if (node_prev != NULL && search != NULL && search != head_saved &&
        move_to_front) { // If move to front is true
      ListNode *temp_next =
          search->next;          // Save node that is next to node with key
      *head = search;            // set new_node as head
      search->next = head_saved; // next next of new head as old head
      node_prev->next =
          temp_next; // reattach node before the node with key
                     // match with the node after the node with key
    }
  }
  return node_return;
}

// Print old speak word associated with node
void ll_node_print(ListNode *n) {
  if (n != NULL) {
    printf("%s", n->gs->oldspeak); // Print if node isn't null
  }
  return;
}

// Print linked list.
void ll_print(ListNode *head) {
  while (head !=
         NULL) { // While node isn't NULL, print node and moved to next node.
    ll_node_print(head);
    printf("\n");
    head = head->next;
  }
  return;
}
