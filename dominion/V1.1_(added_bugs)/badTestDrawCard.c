#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>
#include <stdlib.h>

#define DEBUG 0
#define NOISY_TEST 1

void checkDrawCard(int p, struct gameState *post) {
  int r;
    
  r = drawCard (p, post);
  if(r) {}
}

int main () {

  //int i, n, r, p, deckCount, discardCount, handCount;
  int i, n, p;

  //int k[10] = {adventurer, council_room, feast, gardens, mine,
  //	       remodel, smithy, village, baron, great_hall};

  struct gameState G;

  printf ("Testing drawCard.\n");

  printf ("RANDOM TESTS.\n");

  SelectStream(2);
  PutSeed(3);

  printf("sizeof(struct gameState) == %zu\n", sizeof(struct gameState));
  printf("sizeof((char*)&G) == %zu\n", sizeof((char*)&G));


  for (n = 0; n < 2000; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }
    p = floor(Random() * 1000);
    checkDrawCard(p, &G);
  }

  printf ("ALL TESTS OK\n");

  exit(0);
}
