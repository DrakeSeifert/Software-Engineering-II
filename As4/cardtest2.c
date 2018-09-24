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
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;
    int checkPass = PASSED;
    int i, p, otherPlayer;
    int totalCards = 25;

	printf("***Testing Adventurer card***\n");

    for(p = 0; p < numPlayer; p++)
    {
        printf("Player %d:\n", p);
        memset(&G, 0, sizeof(struct gameState));
        initializeGame(numPlayer, k, seed+p, &G);
        G.whoseTurn = p;
        memcpy(&testG, &G, sizeof(struct gameState));

        G.hand[p][0] = adventurer;
        playCard(0, 0, 0, 0, &G);

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

        //reset
        /*       
        memset(&G, 0, sizeof(struct gameState));
        initializeGame(numPlayer, k, seed, &G);
        memcpy(&testG, &G, sizeof(struct gameState));

        checkPass = PASSED;
        printf("\tGame still functions if player has less than 2 treasure cards in deck: ");
        for(i = 0; i < G.deckCount[p]; i++)
        {
            if(G.deck[p][i] == copper)
            {
                printf("\t\tSwitching out copper with estate in deck\n");
                G.deck[p][i] = estate;
            }
        }
        for(i = 0; i < G.handCount[p]; i++)
        {
            if(G.hand[p][i] == copper)
            {
                printf("\t\tSwitching out copper with estate in hand\n");
                G.hand[p][i] = estate;
            }
        }

        cardEffect(adventurer, 0, 0, 0, &G, 0, 0);
        if(G.handCount != testG.handCount)
            checkPass = FAILED;
        if(G.deckCount != testG.deckCount)
            checkPass = FAILED;
        result(checkPass);
        if(checkPass == FAILED)
        {
            printf("Initial handCount == %d\n", testG.handCount[p]);
            printf("Post Adventurer handCount == %d\n", G.handCount[p]);

            printf("Initial deckCount == %d\n", testG.deckCount[p]);
            printf("Post Adventurer deckCount == %d\n", G.deckCount[p]);
        }
        */
        //The above code crashes the program as I suspected it would
        printf("\tGame doesn't crash if player has less than 2 treasure cards in deck: ");
        result(FAILED);

    }

    printf("***End of Adventurer card Tests***\n");

    return 0;
}