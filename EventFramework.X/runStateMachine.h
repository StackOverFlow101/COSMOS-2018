/* 
 * File:   runStateMachine.h
 * Author: Rice and Spaghetti
 *
 * Created on July 31, 2018, 10:07 AM
 */

#ifndef RUNSTATEMACHINE_H
#define RUNSTATEMACHINE_H

#include "event.h"

// A list of your states goes here:

typedef enum {
    DISARMED,
    COUNTING_DOWN,
    BOOM
} state_t;

// A prototype for the function that handles the whole state machine:
void RunStateMachine(event_t this_event);

#endif

