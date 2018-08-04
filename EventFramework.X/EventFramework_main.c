/* 
 * File:   EventFramework_main.c
 * Author: Rice and Spaghetti
 *
 * Created on July 31, 2018, 9:54 AM
 */

#include <stdio.h>
#include <stdlib.h>

#include "BOARD.h"
#include "serial.h"
#include "roach.h"
#include "TIMERS.h"

//Other includes
#include "Navigation.h"
#include "Bumpers.h"
#include "CheckLightSensor.h"
#include "event.h"
#include "runStateMachine.h"

int main(int argc, char** argv) {
    //Init code (BOARD, Roach, Timers)
    BOARD_Init();
    Roach_Init();
    TIMERS_Init();


    TIMERS_InitTimer(0, 1);
    event_t currentEvent = NO_EVENT;

    while (1) {
        //If an event happens run the state machine
        currentEvent = CheckForEvents();

        if (currentEvent != NO_EVENT) {
            RunStateMachine(currentEvent);
        }
    }
}

