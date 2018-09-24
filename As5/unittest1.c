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

    int i, p, bonus;
    int seed = 1000;
    int numPlayer = 2;
    int maxBonus = 10;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                remodel, smithy, village, baron, great_hall};

    struct gameState G;
    int maxHandCount = 5;
    int checkPass = PASSED;

    int copperVal = 1;
    int silverVal = 2;
    int goldVal = 3;

	printf("***Testing updateCoins()***\n");
	
	for(p = 0; p < numPlayer; p++)
	{
		printf("Player %d:\n", p);
		//Initialize game
		memset(&G, 23, sizeof(struct gameState));
		initializeGame(numPlayer, k, seed, &G);
		G.handCount[p] = maxHandCount;

		//Check copper
		for(i = 0; i < G.handCount[p]; i++)
		{
			G.hand[p][i] = copper;
		}

		updateCoins(p, &G, 0); //Test w/o bonus initally

		printf("\tCopper is of the correct value: ");
		if(G.coins == copperVal * maxHandCount)
			result(PASSED);
		else
			result(FAILED);

		printf("\tBonus points work with copper: ");
		checkPass = PASSED;
		for(bonus = 1; bonus <= maxBonus; bonus++)
		{
			updateCoins(p, &G, bonus);
			if(G.coins != (copperVal * maxHandCount) + bonus)
			{
				int val = (copperVal * maxHandCount) + bonus;
				printf("\tExpected val: %d, actual: %d\n", val, G.coins);
				checkPass = FAILED;
			}
		}
		result(checkPass);

		//Check silver
		for(i = 0; i < G.handCount[p]; i++)
		{
			G.hand[p][i] = silver;
		}

		updateCoins(p, &G, 0); //Test w/o bonus initally

		printf("\tSilver is of the correct value: ");
		if(G.coins == silverVal * maxHandCount)
			result(PASSED);
		else
			result(FAILED);

		printf("\tBonus points work with silver: ");
		checkPass = PASSED;
		for(bonus = 1; bonus <= maxBonus; bonus++)
		{
			updateCoins(p, &G, bonus);
			if(G.coins != (silverVal * maxHandCount) + bonus)
				checkPass = FAILED;
		}
		result(checkPass);

		//Check gold
		for(i = 0; i < G.handCount[p]; i++)
		{
			G.hand[p][i] = gold;
		}

		updateCoins(p, &G, 0); //Test w/o bonus initally

		printf("\tGold is of the correct value: ");
		if(G.coins == goldVal * maxHandCount)
			result(PASSED);
		else
			result(FAILED);

		printf("\tBonus points work with gold: ");
		checkPass = PASSED;
		for(bonus = 1; bonus <= maxBonus; bonus++)
		{
			updateCoins(p, &G, bonus);
			if(G.coins != (goldVal * maxHandCount) + bonus)
				checkPass = FAILED;
		}
		result(checkPass);
	}

	printf("***End of updateCoins() Tests***\n");

	return 0;
}