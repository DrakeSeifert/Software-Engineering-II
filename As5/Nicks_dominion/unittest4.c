/* 
 * File:   unittest4.c
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
    int j = 0;
    int l = 0;
    
    int numSmithies = 0;
    int numAdventurers = 0;
    
    int countErrors = 0;

    
    printf("\nTesting isGameOver() with seed %i\n", atoi(argv[1]));
    printf("Game Initialized! :)\n");
    
    //For this function, we're testing the whoseTurn() function
    //We're required to give it an initialized game.
    
    printf("Initial province count: %i\n", G.supplyCount[province]);
    
    //Check the province end case
    for (i = 8; i > -1; --i){
        G.supplyCount[province] = i;
        if(i !=0 ){
            countErrors += asserttrue(isGameOver(&G) == 0);
        } else if (i == 0) {
            countErrors += asserttrue(isGameOver(&G) == 1);
        }
    }
    
    G.supplyCount[province] = 8; //Restore the province count
    
    //Loop through the last card to determine how many cards are left.
    //If three piles are out, then check to see if the game is ended...
    for(i = 0; i < (treasure_map - 3); ++i){
        //Reset a constant number of cards
        for(j = 0; j < treasure_map + 1; ++j){
            G.supplyCount[j] = 3;
        }
        G.supplyCount[i] = 0;
        G.supplyCount[i + 1] = 0;
        G.supplyCount[i + 2] = 0;
        
        if(i == province)
            continue;
        
        countErrors += asserttrue(isGameOver(&G) == 1);
        //printf("Returned value: %i\n", isGameOver(&G));
    }
    

    
    //The game SHOULDN'T end with only two empty
    for(i = 0; i < (treasure_map - 2); ++i){
        //Reset a constant number of cards
        for(j = 0; j < treasure_map + 1; ++j){
            G.supplyCount[j] = 3;
        }
        G.supplyCount[i] = 0;
        G.supplyCount[i + 1] = 0;
        
        G.supplyCount[province] = 3;
        if(i == province)
            continue;
        
//        for(l = 0; l < 25; ++l){printf("v:%i ", G.supplyCount[l]);}
//        printf("Returned value: %i\n", isGameOver(&G));        
        countErrors += asserttrue(isGameOver(&G) == 0);
//        if(asserttrue(isGameOver(&G) == 0)){
//            printf("Errored at i: %i\n", i);
//        }
    }
    
    //It also SHOULDN'T end with only one empty
    for(i = 0; i < (treasure_map - 1); ++i){
        //Reset a constant number of cards
        for(j = 0; j < treasure_map + 1; ++j){
            G.supplyCount[j] = 3;
        }
        G.supplyCount[i] = 0;
        
        if(i == province)
            continue;
        
        countErrors += asserttrue(isGameOver(&G) == 0);
        //printf("Returned value: %i\n", isGameOver(&G));
    }
    
    for(j = 0; j < treasure_map + 1; ++j){
            G.supplyCount[j] = 3;
    }
    //printf("Returned value: %i\n", isGameOver(&G));
    
    if(!countErrors){
        printf("__ALL TESTS PASSED!__");
    }
    else { //Some tests failed!
        printf("__%i TESTS FAILED!__", countErrors);
    }
    printf("\n\n");
    
    return (0);
}

