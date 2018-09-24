#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
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

int main () {

    int seed = 1000;
    int numPlayer = 2;
    int i, p;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;
    int checkPass = PASSED;
    int otherPlayer;
    int totalCards = 25;

	printf("***Testing Smithy card***\n");

    for(p = 0; p < numPlayer; p++)
    {
        printf("Player %d:\n", p);
        memset(&G, 0, sizeof(struct gameState));
        initializeGame(numPlayer, k, seed, &G);
        G.whoseTurn = p;
        memcpy(&testG, &G, sizeof(struct gameState));

        //initializeGame(numPlayer, k, seed, &testG);

        cardEffect(smithy, 0, 0, 0, &G, 0, 0);

        checkPass = PASSED;
        printf("\tPlayer receives exactly 3 cards into their hand: ");
        if(G.handCount[p] != testG.handCount[p]+3)
            checkPass = FAILED;
        result(checkPass);
        if(checkPass == FAILED)
        {
            printf("\t\tInitial handCount == %d\n", testG.handCount[p]);
            printf("\t\thandCount after Smithy == %d\n", G.handCount[p]);
        }

        checkPass = PASSED;
        printf("\tPlayer loses 3 cards from deck: ");
        if(G.deckCount[p] != testG.deckCount[p]-3)
            checkPass = FAILED;
        result(checkPass);
        if(checkPass == FAILED)
        {
            printf("\t\tInitial deckCount == %d\n", testG.deckCount[p]);
            printf("\t\tdeckCount after Smithy == %d\n", G.deckCount[p]);
        }

        if(p)
            otherPlayer = 0;
        else
            otherPlayer = 1;

        checkPass = PASSED;
        printf("\tOther player cards unaffected: ");
        if(G.deckCount[otherPlayer] != testG.deckCount[otherPlayer])
            checkPass = FAILED;
        if(G.handCount[otherPlayer] != testG.handCount[otherPlayer])
            checkPass = FAILED;
        if(G.discardCount[otherPlayer] != testG.discardCount[otherPlayer])
            checkPass = FAILED;
        result(checkPass);
        if(checkPass == FAILED)
        {
            printf("\t\tInitial other player's deckCount == %d\n", testG.deckCount[otherPlayer]);
            printf("\t\tOther player's deckCount == %d\n", G.deckCount[otherPlayer]);

            printf("\t\tInitial other player's handCount == %d\n", testG.handCount[otherPlayer]);
            printf("\t\tOther player's handCount == %d\n", G.handCount[otherPlayer]);

            printf("\t\tInitial other player's discardCount == %d\n", testG.discardCount[otherPlayer]);
            printf("\t\tOther player's discardCount == %d\n", G.discardCount[otherPlayer]);
        }

        checkPass = PASSED;
        printf("\tNo state change occurs in victory or supply piles: ");
        for(i = 0; i < totalCards; i++) //check all card piles
        {
            if(G.supplyCount[i] != testG.supplyCount[i])
                checkPass = FAILED;
        }
        result(checkPass);
    }

    printf("***End of Smithy card Tests***\n");

    return 0;
}