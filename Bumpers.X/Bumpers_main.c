/* 
 * File:   Bumpers_main.c
 * Author: Rice and Spaghetti
 *
 * Created on July 24, 2018, 11:54 AM
 */

#include <stdio.h>
#include <stdlib.h>

#include "serial.h"
#include "BOARD.h"
#include "roach.h"
#include "timers.h"

#include "Bumpers.h"

#define INTERVAL 100

int main(int argc, char** argv) {
    
    BOARD_Init();
    Roach_Init();
    TIMERS_Init();

    Bumpers_Init();
    
    unsigned char reading;
    while (1) {
        //Take reading in from function
        reading = CheckForBumps();
        
        //If the reading is not 0 (something has changed)
        if (reading) {
            
            //Check the 5th bit to see if it's a press or release
            if(reading & (1 << 4)) {
                printf("Pressed\r\n");
            }
            else {
                printf("Released\r\n");
            }
            
            //Take only the 1-4th bits
            reading &= 0b00001111;
            printf("Bump = %X\n", reading);
        }
    }
}

