/* 
 * File:   DebouncingMain.c
 * Author: Richard/Matt
 *
 * Handles debouncing without blocking code.
 * 
 * Created on July 19, 2018, 10:34 AM
 */

#include <stdio.h>
#include <stdlib.h>

#include "roach.h"
#include "timers.h"
#include "BOARD.h"
#include "serial.h"

#define WAIT_INTERVAL 5
#define NO_CHANGE 0
#define PRESSED 1
#define RELEASED 2

/**
 * @Function changeFL(void)
 * @return NO_CHANGE, PRESSED, or RELEASED
 * @brief Determines whether there is a change in state for the FrontLeft bumper
 */
unsigned char changeFL(void) {
    static unsigned char previous;
    unsigned char current = Roach_ReadFrontLeftBumper();

    //Check if there is a change
    if (current == previous) {
        previous = current;
        return NO_CHANGE;
    } else {
        //Check for pressed or released
        if (current == 1) {
            previous = current;
            return PRESSED;
        } else if (current == 0) {
            previous = current;
            return RELEASED;
        }
    }
}

/**
 * @Function changeFR(void)
 * @return NO_CHANGE, PRESSED, or RELEASED
 * @brief Determines whether there is a change in state for the FrontRight bumper
 */
unsigned char changeFR(void) {
    static unsigned char previous;
    unsigned char current = Roach_ReadFrontRightBumper();

    //Check if there is a change
    if (current == previous) {
        previous = current;
        return NO_CHANGE;
    } else {
        //Check for pressed or released
        if (current == 1) {
            previous = current;
            return PRESSED;
        } else if (current == 0) {
            previous = current;
            return RELEASED;
        }
    }
}

/**
 * @Function changeRL(void)
 * @return NO_CHANGE, PRESSED, or RELEASED
 * @brief Determines whether there is a change in state for the RearLeft bumper
 */
unsigned char changeRL(void) {
    static unsigned char previous;
    unsigned char current = Roach_ReadRearLeftBumper();

    //Check if there is a change
    if (current == previous) {
        previous = current;
        return NO_CHANGE;
    } else {
        //Check for pressed or released
        if (current == 1) {
            previous = current;
            return PRESSED;
        } else if (current == 0) {
            previous = current;
            return RELEASED;
        }
    }
}

/**
 * @Function changeRR(void)
 * @return NO_CHANGE, PRESSED, or RELEASED
 * @brief Determines whether there is a change in state for the RearRight bumper
 */
unsigned char changeRR(void) {
    static unsigned char previous;
    unsigned char current = Roach_ReadRearRightBumper();

    //Check if there is a change
    if (current == previous) {
        previous = current;
        return NO_CHANGE;
    } else {
        //Check for pressed or released
        if (current == 1) {
            previous = current;
            return PRESSED;
        } else if (current == 0) {
            previous = current;
            return RELEASED;
        }
    }
}

/**
 * @Function debounce
 * @param none
 * @return none
 * @brief Detects the bumper presses and filters out the bounces. Works by
 * registering the first event and then ignoring the next readings for the next
 * WAIT_INTERVAL milliseconds
 */
void debounce(void) {
    char lastBump, thisBump;
    char frontLeft, frontRight, rearLeft, rearRight;

    TIMERS_InitTimer(0, 1);
    while (1) {
        //Check bumpers 
        thisBump = Roach_ReadBumpers();
        if (TIMERS_IsTimerExpired(0) && thisBump != lastBump) {
            frontLeft = changeFL();
            frontRight = changeFR();
            rearLeft = changeRL();
            rearRight = changeRR();

            if (frontLeft == 1) printf("Front Left Bumper Pressed!\r\n");
            else if (frontLeft == 2) printf("Front Left Bumper Released!\r\n");

            if (frontRight == 1) printf("Front Right Bumper Pressed!\r\n");
            else if (frontRight == 2) printf("Front Right Bumper Released!\r\n");

            if (rearLeft == 1) printf("Rear Left Bumper Pressed!\r\n");
            else if (rearLeft == 2) printf("Rear Left Bumper Released!\r\n");

            if (rearRight == 1) printf("Rear Right Bumper Pressed!\r\n");
            else if (rearRight == 2) printf("Rear Right Bumper Released!\r\n");

            TIMERS_InitTimer(0, WAIT_INTERVAL);
        }
        lastBump = thisBump;
    }
}

/**
 * @Function debounceBits(void)
 * @param none
 * @return none
 * @brief Detects the bumper presses and filters out the bounces. Works by
 * checking for 3 consecutive different state changes before registering
 * the event. Uses bit fields.
 */
void debounceBits(void) {
    unsigned char FLStates, FRStates, RLStates, RRStates, sampleNum;

    FLStates = 0;
    FRStates = 0;
    RLStates = 0;
    RRStates = 0;
    
    sampleNum = 0;
    TIMERS_InitTimer(0, WAIT_INTERVAL);
    while (1) {
        if(TIMERS_IsExpired(0)) {
            if (sampleNum == 4) {
                if (FLStates == 0b01111) {
                    printf("Front Left Pressed!\r\n");
                    FLStates = 0b10000;
                } else if (FLStates == 0b10000) {
                    printf("Front Left Released!\r\n");
                    FLStates = 0;
                } else {
                    FLStates &= 0b10000;
                }
            
                if (FRStates == 0b01111) {
                    printf("Front Right Pressed!\r\n");
                    FRStates = 0b10000;
                } else if (FRStates == 0b10000) {
                    printf("Front Right Released!\r\n");
                    FRStates = 0;
                } else {
                    FRStates &= 0b10000;
                }
            
                if (RLStates == 0b01111) {
                    printf("Rear Left Pressed!\r\n");
                    RLStates = 0b10000;
                } else if (RLStates == 0b10000) {
                    printf("Rear Left Released!\r\n");
                    RLStates = 0;
                } else {
                    RLStates &= 0b10000;
                }
            
                if (RRStates == 0b01111) {
                    printf("Rear Right Pressed!\r\n");
                    RRStates = 0b10000;
                } else if (RRStates == 0b10000) {
                    printf("Rear Right Released!\r\n");
                    RRStates = 0;
                } else {
                    RRStates &= 0b10000;
                }

                sampleNum = 0;
            }

            FLStates |= (Roach_ReadFrontLeftBumper() << sampleNum);
            FRStates |= (Roach_ReadFrontRightBumper() << sampleNum);
            RLStates |= (Roach_ReadRearLeftBumper() << sampleNum);
            RRStates |= (Roach_ReadRearRightBumper() << sampleNum);

        
            sampleNum++;
            TIMERS_InitTimer(0, WAIT_INTERVAL);
        }
    }
}

int main(int argc, char** argv) {
    SERIAL_Init();
    BOARD_Init();
    Roach_Init();
    TIMERS_Init();

    //debounce();
    debounceBits();
}
