/* 
 * File:   CheckLightSensor_main.c
 * Author: Rice and Spaghetti
 *
 * Created on July 24, 2018, 11:48 AM
 */

#include <stdio.h>
#include <stdlib.h>

#include "serial.h"
#include "BOARD.h"
#include "roach.h"
#include "timers.h"

#include "CheckLightSensor.h"

int main(int argc, char** argv) {
    SERIAL_Init();
    BOARD_Init();
    Roach_Init();
    TIMERS_Init();

    TIMERS_InitTimer(0, 10);

    char value;
    
    while (1) {
        if (TIMERS_IsTimerExpired(0)) {
            value = CheckLightSensor();
            
            if(value) {
                printf("Value: %d\r\n", value);
            }
            
            TIMERS_InitTimer(0, 100);
        }
    }
}

