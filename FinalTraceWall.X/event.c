#include "Bumpers.h"
#include "event.h"
#include "timers.h"
#include "roach.h"

#define THRESHOLD 770
#define HYSTERESIS 3

/**
 * @Function CheckForLightSensor
 * @brief This function is for private use in event.c
 * It determines whether the RoachBot has moved to light or darkness.
 * @return NO_EVENT if nothing happened; otherwise ENTERED_DARK or ENTERED_LIGHT
 */
event_t CheckForLightSensor(void) {    
    static char previousState;
    char currentState;

    //Check if we're in light or dark
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
/**
 * @Function CheckForBumper
 * @brief Checks whether a bumper has been pressed or released and 
 * returns an event
 * @param nothing
 * @return The event triggered (which bumper has been pressed/released)
 */
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

/**
 * @Function CheckForTimer
 * @brief Checks whether Timer 0 has expired
 * @param nothing
 * @return An event marking whether the timer has expired
 */
event_t CheckForTimer() {
    if(TIMERS_IsTimerExpired(0)) {
        return TIMER_0_EXPIRED;
    }
    
    return NO_EVENT;
}

/**
 * @Function CheckForEvents
 * @brief Checks for what event has happened
 * @param nothing
 * @return The event that has occured; returns NO_EVENT if nothing happened
 */
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

