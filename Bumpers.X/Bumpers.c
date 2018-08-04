#include <stdio.h>
#include <timers.h>
#include "roach.h"

#define BUMPER_TIMER 10
#define INTERVAL 10

/**
 * @Function Bumpers_Init
 * @brief Timers must be initialized first. Call this method before use.
 * @param none
 * @return none
 */
void Bumpers_Init(void) {
    TIMERS_InitTimer(BUMPER_TIMER, INTERVAL);
}

/**
 * @Function CheckForBumps(void)
 * @param nothing
 * @return which bumpers pressed, and what happened
 * @brief This function determines whether a bumper has beeen pressed or 
 * released. If the bumper has been pressed, the 5th and 6th bits are 1, and the
 * 1-4th bits denote which bumpers have been pressed. If the bumper has been
 * released, then the 6th bit is 1 and the 5th bit is 0, while the 1-4th bits
 * denote which bumpers have been pressed. Returns 0 for no change. 6th bit
 * is to denote whether there is a change or not. This method is called
 * bit banging.
 * @author Rice and Spaghetti
 */
unsigned char CheckForBumps(void) {
    //Statics are automatically initialized to 0
    static unsigned char FLStates, FRStates, RLStates, RRStates, sampleNum;

    if (TIMERS_IsTimerExpired(BUMPER_TIMER)) {
        TIMERS_InitTimer(BUMPER_TIMER, INTERVAL);
        
        if (sampleNum == 4) {
            sampleNum = 0;
            
            //FL Pressed
            if (FLStates == 0b01111) {
                FLStates = 0b10000;
                return 0b110001;
            }
            //FL Released
            else if (FLStates == 0b10000) {
                FLStates = 0;
                return 0b100001;
            }
            //No change for FL
            else {
                FLStates &= 0b10000;
            }

            //FR Pressed
            if (FRStates == 0b01111) {
                FRStates = 0b10000;
                return 0b110010;
            }
            //FR Released
            else if (FRStates == 0b10000) {
                FRStates = 0;
                return 0b10010;
            }
            //No change for FR
            else {
                FRStates &= 0b10000;
            }

            //RL Pressed
            if (RLStates == 0b01111) {
                RLStates = 0b10000;
                return 0b110100;
            }
            //RL Released
            else if (RLStates == 0b10000) {
                RLStates = 0;
                return 0b10100;
            }
            //No change for RL
            else {
                RLStates &= 0b10000;
            }

            //RR pressed
            if (RRStates == 0b01111) {
                RRStates = 0b10000;
                return 0b111000;
            }
            //RR Released
            else if (RRStates == 0b10000) {
                RRStates = 0;
                return 0b101000;
            }
            else {
                RRStates &= 0b10000;
            }
            
            //None of the bumpers have changed
            return 0;
        }
        
        FLStates |= (Roach_ReadFrontLeftBumper() << sampleNum);
        FRStates |= (Roach_ReadFrontRightBumper() << sampleNum);
        RLStates |= (Roach_ReadRearLeftBumper() << sampleNum);
        RRStates |= (Roach_ReadRearRightBumper() << sampleNum);

        sampleNum++;
    }
    
    //Return NO_CHANGE if it hasn't measured 4 yet
    return 0;
}
