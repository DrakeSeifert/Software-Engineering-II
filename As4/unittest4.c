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
    int r;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int checkPass = PASSED;

	printf("***Testing isGameOver()***\n");

    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayer, k, seed, &G);

    checkPass = PASSED;
    printf("\tInitial game setup does not end game: ");
    r = isGameOver(&G);
    if(r)
        checkPass = FAILED;
    result(checkPass);

    checkPass = PASSED;
    printf("\tGame ends when province cards run out: ");
    G.supplyCount[province] = 0;
    r = isGameOver(&G);
    if(!r)
        checkPass = FAILED;
    result(checkPass);

    checkPass = PASSED;
    printf("\tGame doesn't end when 1 supply pile is out: ");
    G.supplyCount[province] = 8;
    G.supplyCount[village] = 0;
    r = isGameOver(&G);
    if(r)
        checkPass = FAILED;
    result(checkPass);

    checkPass = PASSED;
    printf("\tGame doesn't end when 2 supply piles are out: ");
    G.supplyCount[smithy] = 0;
    r = isGameOver(&G);
    if(r)
        checkPass = FAILED;
    result(checkPass);

    checkPass = PASSED;
    printf("\tGame ends when there are 3 supply piles out: ");
    G.supplyCount[adventurer] = 0;
    if(!r)
        checkPass = FAILED;
    result(checkPass);
    printf("\t\tG.supplyCount[village] == %d\n", G.supplyCount[village]);
    printf("\t\tG.supplyCount[smithy] == %d\n", G.supplyCount[smithy]);
    printf("\t\tG.supplyCount[adventurer] == %d\n\n", G.supplyCount[adventurer]);

    checkPass = PASSED;
    printf("\tGame ends when there are more than 3 supply piles out: ");
    G.supplyCount[mine] = 0;
    if(!r)
        checkPass = FAILED;
    result(checkPass);
    printf("\t\tG.supplyCount[village] == %d\n", G.supplyCount[village]);
    printf("\t\tG.supplyCount[smithy] == %d\n", G.supplyCount[smithy]);
    printf("\t\tG.supplyCount[adventurer] == %d\n", G.supplyCount[adventurer]);
    printf("\t\tG.supplyCount[mine] == %d\n", G.supplyCount[mine]);

    printf("***End of isGameOver() Tests***\n");

	return 0;
}