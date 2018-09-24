/* 
 * File:   unittest1.c
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

/*
 * 
 */
int main(int argc, char** argv) {
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy};

//    printf("Starting game.\n");

    initializeGame(2, k, atoi(argv[1]), &G);

    int money = 0;
    int smithyPos = -1;
    int adventurerPos = -1;
    int i = 0;

    int numSmithies = 0;
    int numAdventurers = 0;
    
    int countErrors = 0;

    
    printf("\nTesting whoseTurn() with seed %i\n", atoi(argv[1]));
    printf("Game Initialized! :)\n");
    
    //For this function, we're testing the whoseTurn() function
    //We're required to give it an initialized game.
    
    //After init, it should be equal to zero
    countErrors += asserttrue(whoseTurn(&G) == 0);
    printf("initial whoseTurn: %i\n", whoseTurn(&G));
    
    //Check the whoseTurn number 
    for (i = 0; i < MAX_PLAYERS; ++i){
      G.whoseTurn = i; //Set the turn as the 3rd player
      //Check if it updated
      countErrors += asserttrue(whoseTurn(&G) == i);
    }
    
    
    if(!countErrors){
        printf("__ALL TESTS PASSED!__");
    }
    else { //Some tests failed!
        printf("__%i TESTS FAILED!__", countErrors);
    }
    printf("\n\n");
    
    return (0);
}

