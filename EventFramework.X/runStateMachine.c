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

#define COUNTDOWN_TIME 12
#define SECOND 1000

void RunStateMachine(event_t currentEvent) {
    static state_t currentState = DISARMED;

    //Specific for Bomb
    static char count = COUNTDOWN_TIME;
    static uint16_t LEDs = 0b111111111111; //12 LEDs, but 8 bits in a char

    Roach_LEDSSet(LEDs);

    //Which state are we in? 
    printf("\nState: %d\tEvent: %d\r\n", currentState, currentEvent);

    //Check the state
    switch (currentState) {
        case DISARMED:
        {
            switch (currentEvent) {
                case TIMER_0_EXPIRED:
                    TIMERS_InitTimer(0, SECOND);
                    currentState = COUNTING_DOWN;
                    break;
                case DISARM:
                    count = COUNTDOWN_TIME;
                    TIMERS_StopTimer(0);
                    TIMERS_ClearTimerExpired(0);
                    break;
            }
            break;
        }
        case COUNTING_DOWN:
        {
            switch (currentEvent) {
                case TIMER_0_EXPIRED:
                    if (count == 0) {
                        currentState = BOOM;
                        TIMERS_InitTimer(0, 1); //Head straight to BOOM
                    } else {
                        count--;
                        LEDs >>= 1;
                        Roach_LEDSSet(LEDs);
                    }
                    TIMERS_InitTimer(0, SECOND);
            }
            break;
        }
        case BOOM:
        {
            printf("BOOM!\r\n");
            currentState = DISARMED;
            currentEvent = DISARM;

            count = COUNTDOWN_TIME;
            TIMERS_StopTimer(0);
            TIMERS_ClearTimerExpired(0);

            break;
        }
    }
}