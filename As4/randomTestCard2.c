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

    printf("SEE COVERAGE ON LINE 10051\n");
    printf("***Testing Village card***\n");

    for (i = 0; i < 2000; i++)
    {
        printf("TEST %d\n", i);
        memset(&G, 0, sizeof(struct gameState));
        initializeGame(numPlayer, k, seed, &G);

        p = rand() % MAX_PLAYERS;
        G.whoseTurn = p;
        G.deckCount[p] = rand() % MAX_DECK;
        G.discardCount[p] = rand() % MAX_DECK;
        G.handCount[p] = (rand() % MAX_HAND) + 1;

        memcpy(&testG, &G, sizeof(struct gameState)); //Save state before testing card

        randHandPos = rand() % G.handCount[p];

        playVillage(p, &G, randHandPos);

        printf("\tNumber of cards in hand unchanged: ");
        checkPass = PASSED;
        if(G.handCount[p] != testG.handCount[p])
            checkPass = FAILED;
        result(checkPass);
        if(checkPass == FAILED)
        {
            printf("\t\tOriginal handCount == %d\n", testG.handCount[p]);
            printf("\t\tNew handCount == %d\n", G.handCount[p]);
        }

        printf("\tPlayer has +2 actions: ");
        checkPass = PASSED;
        if(G.numActions != testG.numActions + 2)
            checkPass = FAILED;
        result(checkPass);
        if(checkPass == FAILED)
        {
            printf("\t\tOriginal numActions == %d\n", testG.numActions);
            printf("\t\tNew numActions == %d\n", G.numActions);
        }
    }

    return 0;
}