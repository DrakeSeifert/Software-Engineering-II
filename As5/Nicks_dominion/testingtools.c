/*
 * Nick McComb
 * www.nickmccomb.net
 * 
 * Written Winter 2017 for CS362
 * 
 * 
 **/

#include "testingtools.h"

uint8_t asserttrue(uint8_t value){
    
    if(!value){
        printf("TEST FAILED!\n");
        return 1;
    }
    
    return 0;
}