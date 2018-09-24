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
    int p, r;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                remodel, smithy, village, baron, great_hall};
    struct gameState G;

    int initDeckCount, initHandCount;
    int checkPass = PASSED;
    int otherPlayer;

	printf("***Testing drawCard()***\n");
	
    for(p = 0; p < numPlayer; p++)
    {
        printf("Player %d:\n", p);
        memset(&G, 23, sizeof(struct gameState));
        initializeGame(numPlayer, k, seed, &G);

        //int drawCard(int player, struct gameState *state)
        if(p == 0)
            otherPlayer = 1;
        else
            otherPlayer = 0;

        initDeckCount = G.deckCount[p];
        initHandCount = G.handCount[p];

        checkPass = PASSED;
        r = drawCard(p, &G);
        printf("\tPlayer draws a card into their hand: ");
        if(G.handCount[p] != initHandCount+1)
            checkPass = FAILED;
        result(checkPass);

        checkPass = PASSED;
        printf("\tPlayer deck decremented: ");
        if(G.deckCount[p] != initDeckCount-1)
            checkPass = FAILED;
        result(checkPass);

        checkPass = PASSED;
        printf("\tOther player info unchanged: ");
        if(G.deckCount[p] == G.deckCount[otherPlayer])
            checkPass = FAILED;
        if(G.handCount[p] == G.handCount[otherPlayer])
            checkPass = FAILED;
        result(checkPass);

        //reset gameState
        memset(&G, 23, sizeof(struct gameState));
        initializeGame(numPlayer, k, seed, &G);
        printf("(Similar tests, now with empty player deck)\n");

        G.deckCount[p] = 0; //Delete player deck

        discardCard(4, p, &G, 0); //Add cards to discard pile
        discardCard(3, p, &G, 0);

        initDeckCount = G.deckCount[p];
        initHandCount = G.handCount[p];

        checkPass = PASSED;
        r = drawCard(p, &G);
        printf("\tPlayer draws a card into their hand: ");
        if(G.handCount[p] != initHandCount+1)
            checkPass = FAILED;
        result(checkPass);

        checkPass = PASSED;
        printf("\tPlayer deck shuffles in discards, then loses one: ");
        if(G.deckCount[p] != 1) //2 cards in discard shuffled into deck, then decremented == 1
            checkPass = FAILED;
        result(checkPass);

        checkPass = PASSED;
        printf("\tOther player info unchanged: ");
        if(G.deckCount[p] == G.deckCount[otherPlayer])
            checkPass = FAILED;
        if(G.handCount[p] == G.handCount[otherPlayer])
            checkPass = FAILED;
        result(checkPass);

        G.discardCount[p] = 0; //Delete discard pile
        checkPass = PASSED;
        printf("\tPlayer unable to draw with empty deck/discard pile: ");
        r = drawCard(p, &G);
        if(r != -1)
            checkPass = FAILED;
        result(checkPass);
    }

    printf("***End of drawCard() Tests***\n");

	return 0;
}