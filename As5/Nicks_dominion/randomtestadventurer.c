/* 
 * File:   cardtest1.c
 * Author: Nick
 *
 * Created on February 1, 2017, 9:06 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testingtools.h"

#define D_PRINT(x)  (printf(x))  //Debug printing!

#define TIMES_TO_LOOP 100
#define TARGET_SECONDS 10

/*
 * 
 */
int main(int argc, char** argv) {
    struct gameState G, copy_G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy};


    printf("Starting game.\n");

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

    time_t timer;
    struct tm y2k = {0};
    double seconds;

    y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
    y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;

    time(&timer);  /* get current time; same as: timer = time(NULL)  */

    seconds = difftime(timer,mktime(&y2k));
    int startTime = seconds;
    
    printf("\nTesting playAdventurer() with seed %i\n", atoi(argv[1]));
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
    
    int loop = 0;    
    int player = 0;
    
    

    
    const int PLAYERS_TO_TEST = 4;
    
    do{
    
    //for(loop = 0; loop < TIMES_TO_LOOP; ++loop){
        ++loop;
    
        player = (int) (Random() * PLAYERS_TO_TEST);
        //printf("Testing player %i", player);
        j = (int) (Random() * (MAX_HAND - 3));
        //printf(" - with hand size: %i\n", j);

        //Start the test with a fresh copy of the game
       G.whoseTurn = player;
            
        previous_handCount = G.handCount[player] = j;
        //printf("Handocount: %i\n", G.handCount[0]);

        //printf("Player %i cards: ", player + 1);
        for(i = 0; i < G.handCount[player]; ++i){
            //printf("v: %i ", G.hand[player][i]);
            //Verify that the cards are valid
            countErrors += asserttrue(G.hand[player][i] >= curse && G.hand[player][i] <= treasure_map);
        }
        //printf("\n");

        playAdventurer(&G);

        //printf("Player %i cards: ", player + 1);
        for(i = 0; i < G.handCount[player]; ++i){
            //printf("v: %i ", G.hand[player][i]);
            //Verify that the cards are valid
            countErrors += asserttrue(G.hand[player][i] >= curse && G.hand[player][i] <= treasure_map);
        }
        //printf("\n");

        //printf("Handocount: %i\n", G.handCount[0]);
        //Test that the right number of cards were added
        //printf("comparing %i to %i\n", previous_handCount + 2, G.handCount[player]);
        countErrors += asserttrue((previous_handCount + 2) == G.handCount[player]);

        //Test that the final two cards are in fat treasure cards
        countErrors += asserttrue(G.hand[player][previous_handCount + 0] >= copper && G.hand[player][previous_handCount + 0] <= gold);
        countErrors += asserttrue(G.hand[player][previous_handCount + 1] >= copper && G.hand[player][previous_handCount + 1] <= gold);

        //END OF FIRST TEST

        //For this second test, we are checking if the deck count is zero
        G = copy_G;

        G.whoseTurn = player;
        previous_handCount = G.handCount[player] = j;
        //printf("Handocount: %i\n", G.handCount[0]);

        //Set the deck count to zero
        G.deckCount[player] = 0;
        for(l = 0; l < 5; ++l){
            G.discard[player][l] = gold;
            ++G.discardCount[player];
        }

        playAdventurer(&G);

        //Check for valid cards
        for(i = 0; i < G.handCount[player]; ++i){
            //printf("v: %i ", G.hand[player][i]);
            //Verify that the cards are valid
            countErrors += asserttrue(G.hand[player][i] >= curse && G.hand[player][i] <= treasure_map);
        }

        //Test that the right number of cards were added
        //printf("comparing %i to %i\n", previous_handCount + 2, G.handCount[player]);
        countErrors += asserttrue((previous_handCount + 2) == G.handCount[player]);

        //Test that the final two cards are in fact treasure cards
        countErrors += asserttrue(G.hand[player][previous_handCount + 0] >= copper && G.hand[player][previous_handCount + 0] <= gold);
        countErrors += asserttrue(G.hand[player][previous_handCount + 1] >= copper && G.hand[player][previous_handCount + 1] <= gold);


        timer = time(NULL);  /* get current time; same as: timer = time(NULL)  */
        seconds = difftime(timer,mktime(&y2k));
    }while(seconds < (startTime + TARGET_SECONDS));

    /*
    printf("Player 2 cards: ");
    
    for(i = 0; i < G.handCount[1]; ++i){
        printf("v: %i ", G.hand[1][i]);
    }
    */
    
    printf("\n");
    
    printf("Tested card %i times in %i seconds. \n", loop, TARGET_SECONDS);
    
    if(!countErrors){
        printf("__ALL TESTS PASSED!__");
    }
    else { //Some tests failed!
        printf("__%i TESTS FAILED!__", countErrors, loop);
    }
    printf("\n\n");
    
    return (0);
}

