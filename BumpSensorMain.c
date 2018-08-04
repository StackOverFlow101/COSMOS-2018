/* 
 * File:   BumpSensorMain.c
 * Author: Richard Luo/Raghav Gupta
 *
 * Created on July 17, 2018, 11:40 AM
 */

#include <stdio.h>
#include <stdlib.h>

#include "roach.h"
#include "timers.h"
#include "BOARD.h"
#include "serial.h"

/**
 * Prints to the terminal which bumper has been pressed
 */
void printBumperPress(void) {
    while (1) {
        if (Roach_ReadFrontLeftBumper()) {
            printf("Front Left\r\n");
        }
        if (Roach_ReadFrontRightBumper()) {
            printf("Front Right\r\n");
        }
        if (Roach_ReadRearLeftBumper()) {
            printf("Rear Left\r\n");
        }
        if (Roach_ReadRearRightBumper()) {
            printf("Rear Right\r\n");
        }

        //Wait 0.1 seconds
        TIMERS_InitTimer(0, 100);
        while (TIMERS_IsTimerActive(0)) {
        }
    }
}

/**
 * Uses the first four LEDs to show which bumper has been pressed.
 * The first LED is front left, the second LED is front right,
 * the third LED is rear left, the fourth LED is rear right
 */
void showBumperLED(void) {
    unsigned char bumpers = 0;

    while (1) {
        //Get reading and display on LEDs
        bumpers = Roach_ReadBumpers();
        Roach_LEDSSet(bumpers);

        //Wait 0.1 seconds
        TIMERS_InitTimer(0, 100);
        while (TIMERS_IsTimerActive(0)) {
        }
    }
}

/**
 * This code will show bouncing since the signals are not perfectly
 * synchronized
 */
void testCode(void) {
    char lastBump;
    char thisBump;
    
    while (1) {
        //check bumpers 
        thisBump = Roach_ReadBumpers();
        if (thisBump != lastBump) {
            printf("Bump=%X\n", thisBump);
        }
        lastBump = thisBump;
        //wait for 0.1 second: 
        TIMERS_InitTimer(0, 100);
        //while (TIMERS_IsTimerActive(0));
    }
}

int main(int argc, char** argv) {
    SERIAL_Init();
    BOARD_Init();
    Roach_Init();
    TIMERS_Init();

    //printBumperPress();
    testCode();
    //showBumperLED();
}

