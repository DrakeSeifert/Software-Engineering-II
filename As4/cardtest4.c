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

    printf("***Testing Mine card***\n");

    for(p = 0; p < numPlayer; p++)
    {
        printf("Player %d:\n", p);
        memset(&G, 23, sizeof(struct gameState));
        initializeGame(numPlayer, k, seed+p, &G);
        G.whoseTurn = p;

        G.hand[p][0] = mine; //First card in hand is mine
        for(i = 1; i < G.handCount[p]; i++)
        {
            G.hand[p][i] = copper; //Replace the rest with copper
        }
        memcpy(&testG, &G, sizeof(struct gameState));

        playCard(0, 0, 1, silver, &G);

        checkPass = PASSED;
        printf("\tPlayer gained additional coins and new card: ");
        if(G.coins <= testG.coins)
            checkPass = FAILED;
        result(checkPass);
        if(checkPass == FAILED)
        {
            printf("\t\tInitial coins == %d\n", testG.coins);
            printf("\t\tPost mine coins == %d\n", G.coins);

            if(!p)
            {
                printf("\t\tNote: Mine card == 11\n");
                printf("\t\tHand before mine is:\n");
                printf("\t\t\t");
                for(i = 0; i < testG.handCount[p]; i++)
                {
                    printf("%d, ", testG.hand[p][i]);
                }
                printf("\n");

                printf("\t\tHand after mine is:\n");
                printf("\t\t\t");
                for(i = 0; i < G.handCount[p]; i++)
                {
                    printf("%d, ", G.hand[p][i]);
                }
                printf("\n");
            }
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
        printf("\tNo state change occurs in non-Treasure supply piles: ");
        for(i = 0; i < totalCards; i++) //check all card piles
        {
            //skip Treasure cards
            if(i == copper || i == silver || i == gold)
                continue;
            if(G.supplyCount[i] != testG.supplyCount[i])
                checkPass = FAILED;
        }
        result(checkPass);
    }

    printf("***End of Mine card Tests***\n");

    return 0;
}