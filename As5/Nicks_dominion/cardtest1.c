/* 
 * File:   cardtest1.c
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
    struct gameState G, copy_G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy};

//    printf("Starting game.\n");

    initializeGame(4, k, atoi(argv[1]), &G);

    int money = 0;
    int smithyPos = -1;
    int adventurerPos = -1;
    int i = 0;
    int j = 0;
    int l = 0;
    
    int numSmithies = 0;
    int numAdventurers = 0;
    
    int countErrors = 0;

    
    printf("\nTesting playSmithy() with seed %i\n", atoi(argv[1]));
    printf("Game Initialized! :)\n");
    
    
    int smithyTestPos = 7;
    
    printf("Player 1 cards: ");
    for(i = 0; i < G.handCount[0]; ++i){
        printf("v: %i ", G.hand[0][i]);
    }
    printf("\n");\

    //START TESTING LOOPS
    
    int previous_handCount;
    
    copy_G = G;
    
    for(int player = 0; player < 4; ++player){
        for(j = 1; j < MAX_HAND - 3; ++j){
            for(smithyTestPos = 0; smithyTestPos < j; ++smithyTestPos){

            G = copy_G;
            
            G.whoseTurn = player;
            
            previous_handCount = G.handCount[player] = j;
            //printf("Handocount: %i\n", G.handCount[0]);

            //Set all cards to copper
            for(i = 0; i < G.handCount[player]; ++i){G.hand[player][i] = copper;};

            //Set a card to be smithy
            G.hand[player][smithyTestPos] = smithy;

            //printf("Player 1 cards: ");
            for(i = 0; i < G.handCount[player]; ++i){
                //printf("v: %i ", G.hand[0][i]);
                //Verify that the cards are valid
                countErrors += asserttrue(G.hand[player][i] >= curse && G.hand[player][i] <= treasure_map);
            }
            //printf("\n");

            playSmithy(&G, smithyTestPos);

            //printf("Player 1 cards: ");
            for(i = 0; i < G.handCount[player]; ++i){
                //printf("v: %i ", G.hand[0][i]);
                //Verify that the cards are valid
                countErrors += asserttrue(G.hand[player][i] >= curse && G.hand[player][i] <= treasure_map);
            }
            //printf("\n");

            //printf("Handocount: %i\n", G.handCount[0]);
            //Test that the right number of cards were added
            //printf("comparing %i to %i\n", previous_handCount + 2, G.handCount[player]);
            countErrors += asserttrue((previous_handCount + 2) == G.handCount[player]);
            }
        }
    }
    //END THE TESTING 
    
    /*
    printf("Player 2 cards: ");
    
    for(i = 0; i < G.handCount[1]; ++i){
        printf("v: %i ", G.hand[1][i]);
    }
    */
    
    printf("\n");
    
    if(!countErrors){
        printf("__ALL TESTS PASSED!__");
    }
    else { //Some tests failed!
        printf("__%i TESTS FAILED!__", countErrors);
    }
    printf("\n\n");
    
    return (0);
}

