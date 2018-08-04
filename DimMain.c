/* 
 * File:   DimMain.c
 * Author: Richard/Matt
 *
 * NOTE: Dim means LED is off for longer than it is on
 * 
 * Created on July 18, 2018, 11:41 AM
 */

#include <stdio.h>
#include <stdlib.h>

#include "serial.h"
#include "timers.h"
#include "BOARD.h"
#include "roach.h"

#define THRESHOLD 15

int main(int argc, char** argv) {
    SERIAL_Init();
    BOARD_Init();
    TIMERS_Init();
    Roach_Init();

    int interval, factor;
    interval = 1;
    factor = 1;
    
    TIMERS_InitTimer(1, 1000);
    while (1) {
        if (TIMERS_IsTimerExpired(1)) {
            if(interval >= THRESHOLD) {
                factor = -1;
                printf("Becoming Brighter\r\n");
            }
            else if(interval <= 1) {
                factor = 1;
                printf("Becoming Dimmer\r\n");
            }
            
            interval += factor;
            TIMERS_InitTimer(1, 1000);
        }

        TIMERS_InitTimer(0, 2);
        while (TIMERS_IsTimerActive(0)) {
            Roach_LEDSSet(0b111111111111);
        }

        TIMERS_InitTimer(0, interval);
        while (TIMERS_IsTimerActive(0)) {
            Roach_LEDSSet(0);
        }
    }

}

