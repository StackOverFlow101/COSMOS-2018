/* 
 * File:   library_test_main.c
 * Author: Rice and Spaghetti
 *
 * Created on July 25, 2018, 11:29 AM
 */

#include <stdio.h>
#include <stdlib.h>

#include "serial.h"
#include "BOARD.h"
#include "roach.h"
#include "timers.h"

//other includes here
#include "Navigation.h"
#include "Bumpers.h"
#include "CheckLightSensor.h"

#define INTERVAL 100

int main(int argc, char** argv) {
    SERIAL_Init();
    BOARD_Init();
    Roach_Init();
    TIMERS_Init();

    Forward(100);
    TIMERS_InitTimer(0, 1);

    char bumperReading, currLight;
    while (1) {
        if (TIMERS_IsTimerExpired(0)) {
            bumperReading = CheckForBumps();
            currLight = CheckLightSensor();

            if (bumperReading != 0) {
                bumperReading &= 0b00001111; //Same as 0xf
                printf("Bumpers = %X\r\n", bumperReading);
            }

            if (currLight != 0) {
                printf("LightLevel = %X\r\n", currLight);
            }
            
            TIMERS_InitTimer(0, INTERVAL);
        }
    }
}

