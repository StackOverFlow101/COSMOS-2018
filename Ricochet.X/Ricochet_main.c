/* 
 * File:   Ricochet_main.c
 * Author: Rice and Spaghetti
 *
 * Created on July 30, 2018, 11:48 AM
 */

#include <stdio.h>
#include <stdlib.h>

#include "Bumpers.h"
#include "Navigation.h"
#include "serial.h"
#include "BOARD.h"
#include "roach.h"
#include "timers.h"

#define DEFAULT_SPEED 100
#define TURN_TIME 500

int main(int argc, char** argv) {
    SERIAL_Init();
    BOARD_Init();
    Roach_Init();
    TIMERS_Init();

    Forward(DEFAULT_SPEED);

    TIMERS_InitTimer(0, 1);

    char bumps;
    while (1) {
        bumps = CheckForBumps();

        if (TIMERS_IsTimerExpired(0)) {
            if (bumps == 0) {
                //Going forward
                Forward(100);
            } else {
                //Turning
                if (bumps & 0b10001) {
                    RotateRight(100);
                }
                if (bumps & 0b10010) {
                    RotateLeft(100);
                }
                
                //Comment this out if you want to follow the wall
                TIMERS_InitTimer(0, TURN_TIME);
            }
        }
    }
}