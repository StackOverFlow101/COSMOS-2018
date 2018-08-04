/* 
 * File:   TimerMain.c
 * Author: Richard and Selina
 *
 * Created on July 13, 2018, 11:11 AM
 */

#include <stdio.h>
#include <stdlib.h>

#include "serial.h"
#include "BOARD.h"
#include "roach.h"
#include "timers.h"

#define TIMER_A 0
#define TIMER_B 1

/*
 * 
 */
int main(int argc, char** argv) {
    SERIAL_Init();
    BOARD_Init();
    Roach_Init();
    TIMERS_Init();
    
    printf("Running timers test!\r\n");
    
    //Timer's shouldn't match up
    TIMERS_InitTimer(TIMER_B, 500);
    TIMERS_InitTimer(TIMER_A, 250);
    
    while(1){
        if(TIMERS_IsTimerExpired(TIMER_B)) {
            printf("B");
            TIMERS_InitTimer(TIMER_B, 3000);
        }
        
        if(TIMERS_IsTimerExpired(TIMER_A)) {
            printf("A");
            TIMERS_InitTimer(TIMER_A, 2000);
        }
    }
}

