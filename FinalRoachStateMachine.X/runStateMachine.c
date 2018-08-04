/*
 * File:   runStateMachine.c
 * Author: Rice and Spaghetti
 *
 * Created on July 31, 2018, 10:06 AM
 */

#include <stdio.h>

#include "event.h"
#include "timers.h"
#include "runStateMachine.h"
#include "roach.h"
#include "Navigation.h"

#define EVADE_TIME 300
#define SPEED 100

void RunStateMachine(event_t currentEvent) {
    static state_t currentState = HIDING;
    static char flag;
    
    //Check the state
    switch (currentState) {
        case RUNNING:
        {
            switch (currentEvent) {
                case ENTERED_DARK:
                    TIMERS_StopTimer(0);
                    Stop();
                    currentState = HIDING;
                    break;
                case FL_BUMPER_DOWN:
                    PivotRight(SPEED);
                    
                    TIMERS_InitTimer(0, EVADE_TIME);
                    currentState = EVADING;
                    break;
                case FR_BUMPER_DOWN:
                    PivotLeft(SPEED);
                    
                    TIMERS_InitTimer(0, EVADE_TIME);
                    currentState = EVADING;
                    break;
            }
            break;
        }
        case EVADING:
        {            
            switch (currentEvent) {
                case TIMER_0_EXPIRED:
                    Forward(SPEED);
                    currentState = RUNNING;
                    break;
            }
            break;
        }
        case HIDING:
        {
            switch (currentEvent) {
                case ENTERED_LIGHT:
                    Forward(SPEED);
                    currentState = RUNNING;
                    break;
            }
            break;
        }
    }
}
