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
    int p, i, j;
    int randHandPos;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;
    int checkPass = PASSED;

    //printf("SEE COVERAGE ON LINE 6056\n");
    printf("***Testing Adventurer card***\n");

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

        int count = 0;
        for(j = 0; j < G.deckCount[p]; j++)
        {
            if( G.deck[p][j] == copper ||
                G.deck[p][j] == silver ||
                G.deck[p][j] == gold)
            {
                count++;
            }
        }

        if(count < 2)
        {
            printf("LESS THAN 2 TREASURES, RESTARTING SO PROGRAM DOESN'T CRASH\n");
            i--;
            continue;
        }

        randHandPos = rand() % G.handCount[p];  
        G.hand[p][randHandPos] = adventurer;
        playCard(randHandPos, 0, 0, 0, &G);
        

        //int playAdventurer(int drawntreasure, struct gameState *state
        //,int currentPlayer, int temphand[MAX_HAND], int z);

        /*
        int temphand[MAX_HAND];

        playAdventurer(0, &G, p, temphand, 0);*/

        checkPass = PASSED;
        printf("\tPlayer has exactly 2 extra cards in hand: ");
        if(G.handCount[p] != testG.handCount[p]+2)
            checkPass = FAILED;
        result(checkPass);
        if(checkPass == FAILED)
        {
            printf("\t\tInitial handCount == %d\n", testG.handCount[p]);
            printf("\t\tPost Adventurer handCount == %d\n", G.handCount[p]);
        }

        checkPass = PASSED;
        printf("\tPlayer has at least 2 more coins than previously: ");
        if(G.coins < testG.coins+2)
            checkPass = FAILED;
        result(checkPass);
        if(checkPass == FAILED)
        {
            printf("\t\tInitial coins == %d\n", testG.coins);
            printf("\t\tPost Adventurer coins == %d\n", G.coins);
        }
         
        checkPass = PASSED;
        printf("\tPlayer loses one action point: ");
        if(G.numActions != testG.numActions-1)
            checkPass = FAILED;
        result(checkPass);
        if(checkPass == FAILED)
        {
            printf("\t\tInitial numActions == %d\n", testG.numActions);
            printf("\t\tPost Adventurer numActions == %d\n", G.numActions);
        }

    }

    return 0;
}