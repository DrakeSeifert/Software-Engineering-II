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

    int i, p, r;
    int seed = 1000;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                remodel, smithy, village, baron, great_hall};

    struct gameState G;
    int supplyPos;
    int toFlag; //3rd parameter for gainCard()
    int toFlagMax = 2;
    int numCardsMax = 40;
    int cardCount = 25; //get number of cards in enum CARD
    int initialCount; //intial number of cards in players deck/hand/discard
    int checkPass = PASSED;

	printf("***Testing gainCard()***\n");

    //gainCard(int supplyPos, struct gameState *state,
    //         int toFlag, int player)

    for(p = 0; p < numPlayer; p++)
    {
        printf("Player %d:\n", p);
        for(toFlag = 0; toFlag <= toFlagMax; toFlag++)
        {
            printf("(toFlag, the 3rd parameter of gainCard is now %d)\n", toFlag);
            memset(&G, 23, sizeof(struct gameState));
            initializeGame(numPlayer, k, seed, &G);

            checkPass = PASSED;
            printf("\tReturns failure for invalid card: ");
            if(gainCard(-1, &G, toFlag, p) != -1)
                checkPass = FAILED;
            result(checkPass);

            //reset gameState
            memset(&G, 23, sizeof(struct gameState));
            initializeGame(numPlayer, k, seed, &G);

            //Test all cards
            for(supplyPos = 0; supplyPos < cardCount; supplyPos++)
            {
                r = gainCard(supplyPos, &G, toFlag, p);
                if(r == -1)
                    checkPass = FAILED;
            }
            printf("\tWorks for all cards in game: ");
            result(checkPass);

            printf("\tDoesn't allow entry for cards that don't exist: ");
            r = gainCard(100, &G, toFlag, p);
            if(r == -1)
                checkPass = PASSED;
            else
                checkPass = FAILED;
            result(checkPass);

            //reset gameState
            memset(&G, 23, sizeof(struct gameState));
            initializeGame(numPlayer, k, seed, &G);

            switch(toFlag)
            {
                case 0:
                    initialCount = G.discardCount[p];
                    break;
                case 1:
                    initialCount = G.deckCount[p];
                    break;

                case 2:
                    initialCount = G.handCount[p];
                    break;
            }

            supplyPos = 4; //more copper cards than any other
            checkPass = PASSED;
            for(i = 0; i < numCardsMax; i++)
            {
                r = gainCard(supplyPos, &G, toFlag, p);
                if(r == -1)
                    checkPass = FAILED;
            }
            printf("\tFunctions after multiple calls: ");
            result(checkPass);

            checkPass = PASSED;
            switch(toFlag)
            {
                case 0:
                    printf("\tPlayer Discard count is correct: ");
                    if(G.discardCount[p] != initialCount+numCardsMax)
                        checkPass = FAILED;
                    result(checkPass);
                    break;
                case 1:
                    printf("\tPlayer Deck count is correct: ");
                    if(G.deckCount[p] != initialCount+numCardsMax)
                        checkPass = FAILED;
                    result(checkPass);
                    break;
                case 2:
                    printf("\tPlayer Hand count is correct: ");
                    if(G.handCount[p] != initialCount+numCardsMax)
                        checkPass = FAILED;
                    result(checkPass);
                    break;
            }
        }
    }

    printf("***End of gainCard() Tests***\n");

	return 0;
}