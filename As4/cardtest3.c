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

	printf("***Testing Village card***\n");

    for(p = 0; p < numPlayer; p++)
    {
        printf("Player %d:\n", p);
        memset(&G, 23, sizeof(struct gameState));
        initializeGame(numPlayer, k, seed, &G);
        G.whoseTurn = p;
        memcpy(&testG, &G, sizeof(struct gameState));

        G.hand[p][0] = village;
        playCard(0, 0, 0, 0, &G);

        checkPass = PASSED;
        printf("\tPlayer has +1 card: ");
        if(G.handCount[p] != testG.handCount[p]+1)
            checkPass = FAILED;
        result(checkPass);
        if(checkPass == FAILED)
        {
            printf("\t\tInitial player handCount == %d\n", testG.handCount[p]);
            printf("\t\tPost Village handCount == %d\n", G.handCount[p]);
        }

        checkPass = PASSED;
        printf("\tPlayer gained +1 Actions: ");
        if(G.numActions != testG.numActions+1)
            checkPass = FAILED;
        result(checkPass);
        if(checkPass == FAILED)
        {
            printf("\t\tInitial Action count == %d\n", testG.numActions);
            printf("\t\tPost Village Action count == %d\n", G.numActions);
        }

        checkPass = PASSED;
        printf("\tVillage card removed from player hand: ");
        for(i = 0; i < G.handCount[p]; i++)
        {
            if(G.hand[p][i] == village)
                checkPass = FAILED;
        }
        result(checkPass);
        if(checkPass == FAILED)
        {
            printf("\t\tNote: Village card == 14\n");
            printf("\t\tPlayer hand is:\n");
            printf("\t\t\t");
            for(i = 0; i < G.handCount[p]; i++)
            {
                printf("%d, ", G.hand[p][i]);
            }
            printf("\n");
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

    printf("***End of Village card Tests***\n");

    return 0;
}