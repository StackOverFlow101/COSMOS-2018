/* 
 * File:   FinalTraceWall_main.c
 * Author: Rice and Spaghetti
 *
 * The way this specific solution works is that the RoachBot traces the wall.
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

    Bumpers_Init();

    event_t currentEvent = ENTERED_LIGHT;

    while (1) {
        if (currentEvent != NO_EVENT) {
            RunStateMachine(currentEvent);
        }
        
        //If an event happens run the state machine
        currentEvent = CheckForEvents();
    }
}

