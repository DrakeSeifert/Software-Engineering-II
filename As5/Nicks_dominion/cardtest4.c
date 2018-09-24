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

#define NUM_PLAYERS 4

/*
 * 
 */
int main(int argc, char** argv) {
    struct gameState G, copy_G;
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
    
    int numSmithies = 0;
    int numAdventurers = 0;
    
    int countErrors = 0;

    
    printf("\nTesting playCouncil_Room() with seed %i\n", atoi(argv[1]));
    printf("Game Initialized! :)\n");
    
    //For this function, we're testing the whoseTurn() function
    //We're required to give it an initialized game.
    
    //printf("Player 1 cards: ");
    //for(i = 0; i < G.handCount[0]; ++i){
    //    printf("v: %i ", G.hand[0][i]);
    //}
    //printf("\n");\

    //START TESTING LOOPS
    
    
    
    int previous_handCount, initialActions, initialBuys, initialPlayer;
    
    int initialHandcounts[NUM_PLAYERS];
    
    copy_G = G;
    
    int player = 0;
    
    j = 1;
    
    for(player = 0; player < 4; ++player){
    //    for(j = 1; j < MAX_HAND - 3; ++j){
            G = copy_G;
            
            G.whoseTurn = player;
            
            
            //Artificially give the players a deck to work with
            G.deckCount[player] = MAX_DECK;
            
            //previous_handCount = G.handCount[player] = j;
            initialActions = G.numActions;
            initialBuys = G.numBuys;
            
            //internal to test suite
            //initialPlayer = player;
            
            //Store the initial handcounts for all the players
            for(int playerIndex = 0; playerIndex < NUM_PLAYERS; ++playerIndex){
                initialHandcounts[playerIndex] = G.handCount[playerIndex];
                printf("Stored %i ", G.handCount[playerIndex]);
            }
            printf("Handocount for p%i: %i\n", player, G.handCount[player]);
            

            for(int playerOutput = 0; playerOutput < NUM_PLAYERS; ++playerOutput){
                printf("Player %i cards: ", playerOutput + 1);
                for(i = 0; i < G.handCount[playerOutput]; ++i){
                    printf("v: %i ", G.hand[playerOutput][i]);
                    //Verify that the cards are valid
                    countErrors += asserttrue(G.hand[playerOutput][i] >= curse && G.hand[playerOutput][i] <= treasure_map);
                }
                printf("\n");
            }
            
            //player = initialPlayer;

            playCouncil_Room(&G, 2);

            for(int playerOutput = 0; playerOutput < NUM_PLAYERS; ++playerOutput){
                printf("Player %i cards: ", playerOutput + 1);
                for(i = 0; i < G.handCount[playerOutput]; ++i){
                    printf("v: %i ", G.hand[playerOutput][i]);
                    //Verify that the cards are valid
                    countErrors += asserttrue(G.hand[playerOutput][i] >= curse && G.hand[playerOutput][i] <= treasure_map);
                }
                printf("\n");
            }

            //printf("Handocount: %i\n", G.handCount[0]);
            //Test that the hand size is the same (add a card, and discard a card)
            //countErrors += asserttrue((previous_handCount ) == G.handCount[player]);
            
            //Check the final handcounts for the players
            for(int playerIndex = 0; playerIndex < NUM_PLAYERS; ++playerIndex){
                if(playerIndex != player){  //If we are not looking at the current player
                    //Then the hand size should have increased by one
                    countErrors += asserttrue((initialHandcounts[playerIndex] + 1) == G.handCount[playerIndex]);
                    printf("Compared %i and %i ", initialHandcounts[playerIndex] + 1, G.handCount[playerIndex]);
                }
                else { //Then we are looking at the current player, whose hand should have increased 4
                    countErrors += asserttrue(initialHandcounts[playerIndex] + 3 == G.handCount[playerIndex]);
                    printf("Compared %i and %i ", initialHandcounts[playerIndex] + 3, G.handCount[playerIndex]);
                }
            }
            
            
            //Check that the number of buys have increased
            countErrors += asserttrue(G.numBuys == (initialBuys + 1));
       
            
            //END OF FIRST TEST
            
    //    }
    }
    //END THE TESTING 
    
    
    
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

