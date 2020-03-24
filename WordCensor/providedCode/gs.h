#ifndef __GS_H__
#define __GS_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct GoodSpeak GoodSpeak;
struct GoodSpeak{
  char *oldspeak;
  char *newspeak;
};

GoodSpeak *gs_create(char *oldspeak, char *newspeak);

void gs_delete(GoodSpeak *g);

char *gs_oldspeak(GoodSpeak *g);

char *gs_newspeak(GoodSpeak *g);

#endif
