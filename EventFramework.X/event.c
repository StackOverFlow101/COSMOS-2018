#include "Bumpers.h"
#include "event.h"
#include "timers.h"
#include "roach.h"

#include <stdio.h>
#define THRESHOLD 511
#define HYSTERESIS 3

event_t CheckForLightSensor(void) {    
    static char previousState;
    char currentState;

    if(Roach_LightLevel() > THRESHOLD + HYSTERESIS) {
        currentState = 1;
    }
    else if(Roach_LightLevel() < THRESHOLD - HYSTERESIS) {
        currentState = 0;
    }
    else {
        currentState = previousState;
    }
    
    if (currentState == previousState) {
        return NO_EVENT;
    }
    //Means it went from dark to bright
    else if (currentState == 0) {
        previousState = currentState;
        return ENTERED_LIGHT;
    }
    //Means it went from light to dark
    else {
        previousState = currentState;
        return ENTERED_DARK;
    }
}

event_t CheckForBumper(void) {
    unsigned char bumps = CheckForBumps();
    
    //Check for pressed
    if(bumps & 1 << 4) {
        if(bumps & 1) return FL_BUMPER_DOWN;
        if(bumps & 0b10) return FR_BUMPER_DOWN;
        if(bumps & 0b100) return RL_BUMPER_DOWN;
        if(bumps & 0b1000) return RR_BUMPER_DOWN;
    }
    //Means it was released
    else {
        if(bumps & 1) return FL_BUMPER_UP;
        if(bumps & 0b10) return FR_BUMPER_UP;
        if(bumps & 0b100) return RL_BUMPER_UP;
        if(bumps & 0b1000) return RR_BUMPER_UP;
    }
    
    return NO_EVENT;
}

event_t CheckForTimer() {
    if(TIMERS_IsTimerExpired(0)) {
        return TIMER_0_EXPIRED;
    }
    
    return NO_EVENT;
}

event_t CheckForEvents(void) {
    event_t thisEvent = NO_EVENT;
    
    //Checking for light sensor
    thisEvent = CheckForLightSensor();
    if (thisEvent != NO_EVENT) {
        return thisEvent;
    }
    
    
    //Checking for Bumper
    thisEvent = CheckForBumper();
    if (thisEvent != NO_EVENT) {
        return thisEvent;
    }
    
    //Checking for Timer 0
    thisEvent = CheckForTimer();
    if (thisEvent != NO_EVENT) {
        return thisEvent;
    }
    
    return NO_EVENT;
}