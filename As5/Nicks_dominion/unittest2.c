/* 
 * File:   unittest2.c
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

#define NUM_PLAYERS 2

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
    
    printf("\nTesting updateCoins() with seed %i\n", atoi(argv[1]));
    printf("Game Initialized! :)\n");
    
    //For this function, we're testing the whoseTurn() function
    //We're required to give it an initialized game.
    
    //After init, it should be equal to zero
    //So we check for all players (by default 2)
    for(i = 0; i < NUM_PLAYERS; ++i){
      countErrors += asserttrue(updateCoins(i, &G, 0) == 0);
    //  printf("initial updateCoins for p%i: %i\n", i, updateCoins(i, &G, 0));
    }
   
    
    //We want to test the bonus functionality while we still have a blank game
    //We'll test 100 values of bonus (because it'll never reasonably go over 100)
    //Using the 2nd player because they don't have anything in their hand
    for(j = 0; j < BONUS_TO_TEST; ++j){
        updateCoins(1, &G, j);  //Update the coin counts
        countErrors += asserttrue(G.coins == j);  //Check the coun counts
    }
    
    for(i = 0; i < NUM_PLAYERS; ++i){
    //  printf("Handcount p%i: %i \n", i, G.handCount[i]);
    }
    
    
    //TEST COPPER
    for(j = 0; j < BONUS_TO_TEST; ++j){
        //Set hand to all coppers
        for(i = 0; i < G.handCount[player]; ++i){
            G.hand[player][i] = copper;
        }

        //Output hand contents
        player = 0;
        //printf("Hand contents of p%i:", player);
        for(i = 0; i < G.handCount[player]; ++i){
        //    printf(" c: %i", G. hand[player][i]);
        }

        //update player with no bonus
        updateCoins(player, &G, j);
        //printf("\nHand should sum to copper*5 + %i: %i\n", j, G.coins);
        countErrors += asserttrue(G.coins == (1*5 + j));
        
        //printf("\n");
    }
    
    //TEST SILVER
    for(j = 0; j < BONUS_TO_TEST; ++j){
        //Set hand to all silver
        for(i = 0; i < G.handCount[player]; ++i){
            G.hand[player][i] = silver;
        }

        //Output hand contents
        player = 0;
        //printf("Hand contents of p%i:", player);
        for(i = 0; i < G.handCount[player]; ++i){
        //    printf(" c: %i", G. hand[player][i]);
        }

        //update player with no bonus
        updateCoins(player, &G, j);
        //printf("\nHand should sum to 2*5 + %i: %i\n", j, G.coins);
        countErrors += asserttrue(G.coins == (2*5 + j));
        
        //printf("\n");
    }
    
    
    //TEST GOLD
    for(j = 0; j < BONUS_TO_TEST; ++j){
        //Set hand to all Gold
        for(i = 0; i < G.handCount[player]; ++i){
            G.hand[player][i] = gold;
        }

        //Output hand contents
        player = 0;
        //printf("Hand contents of p%i:", player);
        for(i = 0; i < G.handCount[player]; ++i){
        //    printf(" c: %i", G. hand[player][i]);
        }

        //update player with no bonus
        updateCoins(player, &G, j);
        //printf("\nHand should sum to 3*5 + %i: %i\n", j, G.coins);
        countErrors += asserttrue(G.coins == (3*5 + j));
        
        //printf("\n");
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

