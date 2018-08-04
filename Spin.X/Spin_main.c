/* 
 * File:   Spin_main.c
 * Author: Rice and Spaghetti
 *
 * Created on July 27, 2018, 10:02 AM
 */

#include <stdio.h>
#include <stdlib.h>

#include "serial.h"
#include "BOARD.h"
#include "roach.h"
#include "timers.h"

//Other Includes
#include "Navigation.h"

#define T_360 1812
#define MAX_SPEED 100

int main(int argc, char** argv) {
    SERIAL_Init();
    BOARD_Init();
    Roach_Init();
    TIMERS_Init();
   
    char spins_remaining = 3;
    
    TIMERS_InitTimer(0, T_360);
    RotateLeft(100);
    while(1) {
        while(TIMERS_IsTimerExpired(0)) {
            if(spins_remaining > 0) {
                TIMERS_InitTimer(0, T_360);
                RotateLeft(MAX_SPEED);
                spins_remaining--;
            }
            else {
                Stop();
            }
        }
    }
}

