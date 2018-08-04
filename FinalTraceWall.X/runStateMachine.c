/*
 * File:   runStateMachine.c
 * Author: Rice and Spaghetti
 *
 * This code runs the state machine given a specific event. This code has
 * been calibrated for the specific roach Snape.
 * 
 * Created on July 31, 2018, 10:06 AM
 */

#include "event.h"
#include "timers.h"
#include "runStateMachine.h"
#include "roach.h"
#include "Navigation.h"

#define SPEED 100
#define TURN_SPEED 92

/*
 * @Function RunStateMachine
 * @brief Given a specific event, this function responds and changes its
 * state accordingly.
 * @param The event that has occured
 * @return nothing
 */
void RunStateMachine(event_t currentEvent) {
    static state_t currentState = HIDING;

    //Check the state
    if (Roach_ReadBumpers() == 0b0011) {
        if(currentEvent == FL_BUMPER_DOWN) {
            RotateLeft(TURN_SPEED);
        }
        else {
            RotateRight(TURN_SPEED);
        }
        Roach_LEDSSet(0b1111);
    }
    else {
        Roach_LEDSSet(0xfff);
        switch (currentState) {
            case RUNNING:
                switch (currentEvent) {
                    case ENTERED_DARK:
                        Stop();
                        currentState = HIDING;
                        break;
                    default:
                        Forward(SPEED);
                }
                break;
            case HIDING:
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

