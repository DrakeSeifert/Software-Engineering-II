/* 
 * File:   unittest3.c
 * Author: Nick
 *
 * Created on February 1, 2017, 9:06 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testingtools.h"

#define D_PRINT(x)  (printf(x))  //Debug printing!

#define NUM_PLAYERS MAX_PLAYERS

#define BONUS_TO_TEST 100

/*
 * 
 */
int main(int argc, char** argv) {
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy};

//    printf("Starting game.\n");

    initializeGame(NUM_PLAYERS, k, atoi(argv[1]), &G);

    
    
    int money = 0;
    int smithyPos = -1;
    int adventurerPos = -1;
    int i = 0;
    int j = 0;
    int l = 0;

    for(i = 0; i < NUM_PLAYERS; ++i){
      printf("Handcount p%i: %i \n", i, G.handCount[i]);
    }
    
    int numSmithies = 0;
    int numAdventurers = 0;
    
    int countErrors = 0;

    int player = 0;
    
    printf("\nTesting getCost() with seed %i\n", atoi(argv[1]));
    printf("Game Initialized! :)\n");
    
    //Test all of the test implementations in the getCost function.
    //These values were all taken from http://wiki.dominionstrategy.com/index.php/Main_Page,
    //NOT copied from the dominion.c file
    
    //100% statement coverage follows:
    
    countErrors += asserttrue(getCost(curse) == 0);
    
    countErrors += asserttrue(getCost(estate) == 2);
    
    countErrors += asserttrue(getCost(duchy) == 5);
    
    countErrors += asserttrue(getCost(province) == 8);
    
    countErrors += asserttrue(getCost(copper) == 0);
    
    countErrors += asserttrue(getCost(silver) == 3);
    
    countErrors += asserttrue(getCost(gold) == 6);
    
    countErrors += asserttrue(getCost(adventurer) == 6);
    
    countErrors += asserttrue(getCost(council_room) == 5);
    
    countErrors += asserttrue(getCost(feast) == 4);
    
    countErrors += asserttrue(getCost(gardens) == 4);
    
    countErrors += asserttrue(getCost(mine) == 5);
    
    countErrors += asserttrue(getCost(remodel) == 4);
    
    countErrors += asserttrue(getCost(smithy) == 4);
    
    countErrors += asserttrue(getCost(village) == 3);
    
    countErrors += asserttrue(getCost(baron) == 4);
    
    countErrors += asserttrue(getCost(great_hall) == 3);
    
    countErrors += asserttrue(getCost(minion) == 5);
    
    countErrors += asserttrue(getCost(steward) == 3);

    countErrors += asserttrue(getCost(tribute) == 5);
    
    countErrors += asserttrue(getCost(ambassador) == 3);
    
    countErrors += asserttrue(getCost(cutpurse) == 4);
    
    countErrors += asserttrue(getCost(embargo) == 2);
    
    countErrors += asserttrue(getCost(outpost) == 5);
    
    countErrors += asserttrue(getCost(salvager) == 4);
    
    countErrors += asserttrue(getCost(sea_hag) == 4);
    
    countErrors += asserttrue(getCost(treasure_map) == 4);

    //Use a deliberately invalid value
    countErrors += asserttrue(getCost(47) == -1);
    
    if(!countErrors){
        printf("__ALL TESTS PASSED!__");
    }
    else { //Some tests failed!
        printf("__%i TESTS FAILED!__", countErrors);
    }
    printf("\n\n");
    
    return (0);
}

