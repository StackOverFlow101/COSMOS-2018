/* 
 * File:   Navigation_main.c
 * Author: Rice and Spaghetti
 *
 * Created on July 24, 2018, 10:54 AM
 */

#include <stdio.h>
#include <stdlib.h>

#include "serial.h"
#include "BOARD.h"
#include "roach.h"
#include "timers.h"

#include "Navigation.h"

#define INTERVAL 3000 //why?

int main(int argc, char** argv) {
    SERIAL_Init();
    BOARD_Init();
    Roach_Init();
    TIMERS_Init();

    int speed = 60;

    Forward(speed);
    TIMERS_InitTimer(0, INTERVAL);
    while (TIMERS_IsTimerActive(0));

    Stop(speed);
    TIMERS_InitTimer(0, INTERVAL);
    while (TIMERS_IsTimerActive(0));

    Reverse(speed);
    TIMERS_InitTimer(0, INTERVAL);
    while (TIMERS_IsTimerActive(0));

    Stop(speed);
    TIMERS_InitTimer(0, INTERVAL);
    while (TIMERS_IsTimerActive(0));
    
    RotateRight(speed);
    TIMERS_InitTimer(0, INTERVAL);
    while (TIMERS_IsTimerActive(0));

    Stop(speed);
    TIMERS_InitTimer(0, INTERVAL);
    while (TIMERS_IsTimerActive(0));
    
    RotateLeft(speed);
    TIMERS_InitTimer(0, INTERVAL);
    while (TIMERS_IsTimerActive(0));

    Stop(speed);
    TIMERS_InitTimer(0, INTERVAL);
    while (TIMERS_IsTimerActive(0));
    
    PivotLeft(speed);
    TIMERS_InitTimer(0, INTERVAL);
    while (TIMERS_IsTimerActive(0));

    Stop(speed);
    TIMERS_InitTimer(0, INTERVAL);
    while (TIMERS_IsTimerActive(0));
    
    PivotRight(speed);
    TIMERS_InitTimer(0, INTERVAL);
    while (TIMERS_IsTimerActive(0));

    Stop(speed);
    TIMERS_InitTimer(0, INTERVAL);
    while (TIMERS_IsTimerActive(0));
    
    ArcLeft(speed);
    TIMERS_InitTimer(0, INTERVAL);
    while (TIMERS_IsTimerActive(0));

    Stop(speed);
    TIMERS_InitTimer(0, INTERVAL);
    while (TIMERS_IsTimerActive(0));
    
    ArcRight(speed);
    TIMERS_InitTimer(0, INTERVAL);
    while (TIMERS_IsTimerActive(0));

    Stop(speed);
    TIMERS_InitTimer(0, INTERVAL);
    while (TIMERS_IsTimerActive(0));
    
    while (1) {
    }
}

