#include "gs.h"
#include <stdlib.h>
#include <string.h>

GoodSpeak *gs_create(char *oldspeak, char *newspeak) {
  GoodSpeak *gs =
      (GoodSpeak *)malloc(sizeof(GoodSpeak)); // Allocate space for Goodspeak
  if (gs != NULL) {
    if (oldspeak != NULL) {
      gs->oldspeak = (char *)calloc(1, strlen(oldspeak) +
                                           1); // allocate memory for oldspeak
      if (gs->oldspeak != NULL) {
        strcpy(gs->oldspeak, oldspeak); // copy to struct
      }
    } else {
      gs->oldspeak = NULL;
    }
    if (newspeak != NULL) {
      gs->newspeak = (char *)calloc(1, strlen(newspeak) +
                                           1); // Allocate memory for newspeak
      if (gs->newspeak != NULL) {
        strcpy(gs->newspeak, newspeak); // copy to struct
      }
    } else {
      gs->newspeak = NULL;
    }
  }
  return gs; // Return goodspeak struct ptr
}
// Delete goodspeak struct
void gs_delete(GoodSpeak *g) {
  free(g->newspeak); // Free memory for newspeak
  free(g->oldspeak); // Free memory for oldspeak
  free(g);           // Free ptr to goodspeak
  g = NULL;
  return;
}

// return oldspeak
char *gs_oldspeak(GoodSpeak *g) { return g->oldspeak; }
// return newspeak
char *gs_newspeak(GoodSpeak *g) { return g->newspeak; }
