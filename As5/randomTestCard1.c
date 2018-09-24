#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"

#define PASSED 1
#define FAILED 0

void result(int resultFlag)
{
    if(resultFlag == 0)
        printf("FAILED\n");
    else if(resultFlag == 1)
        printf("PASSED\n");
    else
        printf("---Error in result()---\n");
}

int main()
{
    srand(time(NULL));
    int seed = rand() % 2000;
    int numPlayer = MAX_PLAYERS;
    int p, i, randHandPos;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;
    int checkPass = PASSED;

    printf("SEE COVERAGE ON LINE 6056\n");
    printf("***Testing Smithy card***\n");

    for (i = 0; i < 2000; i++)
    {
        memset(&G, 0, sizeof(struct gameState));
        initializeGame(numPlayer, k, seed, &G);

        p = rand() % MAX_PLAYERS;
        G.whoseTurn = p;
        G.deckCount[p] = rand() % MAX_DECK;
        G.discardCount[p] = rand() % MAX_DECK;
        G.handCount[p] = (rand() % MAX_HAND) + 1;

        memcpy(&testG, &G, sizeof(struct gameState)); //Save state before testing card

        randHandPos = rand() % G.handCount[p];

        playSmithy(&G, randHandPos, p);

        printf("TEST %d: num cards in hand +2: ", i); //+3 cards, -1 smithy
        checkPass = PASSED;
        if(G.handCount[p] != testG.handCount[p] + 2)
        	checkPass = FAILED;
        result(checkPass);
        if(checkPass == FAILED)
        {
        	printf("\tOriginal handCount == %d\n", testG.handCount[p]);
        	printf("\tNew handCount == %d\n", G.handCount[p]);
        }
    }

    return 0;
}