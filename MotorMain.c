/* 
 * File:   MotorMain.c
 * Author: Richard and Raghav
 * 
 * Notes: Minimum speed for motor starting at 
 * rest when wheels are in the air is 40
 * Going from 100 down (intervals of 0.1 second), the motors appear to cut off
 * at around 15 seconds;
 * 
 * Created on July 17, 2018, 9:46 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "timers.h"
#include "BOARD.h"
#include "roach.h"
#include "serial.h"

#define TIMER_A 0
#define maxForward 100
#define maxBackward -100

/*
 * Makes the motors run forwards and then backwards in 1 second intervals.
 */
void moveForwardBack(void) {
    int time, backwards;

    time = 1000;
    backwards = 0;

    //Initialize the timer and start the motors
    TIMERS_InitTimer(TIMER_A, time);
    Roach_LeftMtrSpeed(maxForward);
    Roach_RightMtrSpeed(maxForward);

    while (1) {
        //If the interval is over, we change the direction and restart the timer
        if (TIMERS_IsTimerExpired(TIMER_A)) {
            TIMERS_InitTimer(TIMER_A, time);
            
            //If backwards switch to forwards and vice versa
            if (backwards == 0) {
                Roach_LeftMtrSpeed(maxBackward);
                Roach_RightMtrSpeed(maxBackward);
            }
            else {
                Roach_LeftMtrSpeed(maxForward);
                Roach_RightMtrSpeed(maxForward);
            }
            backwards = (backwards + 1) % 2;
        }
    }
}

/**
 * Makes the motors move forward and then gradually slows down until
 * they go max speed backwards. Repeats from max speed backwards and gradually
 * slows down to max speed forward. Delay interval of 0.1 seconds.
 */
void moveGradualForwardBack(void) {
    while (1) {
        int time, i;
        time = 100; //Represents the delay between changes in speed
        
        for (i = 100; i >= -100; i--) {
            Roach_LeftMtrSpeed(i);
            Roach_RightMtrSpeed(i);
            printf("SPEED: %d", i);
            
            TIMERS_InitTimer(TIMER_A, time);
            while (TIMERS_IsTimerActive(TIMER_A)) {}
        }

        /*
        TIMERS_InitTimer(TIMER_A, time);
        while (TIMERS_IsTimerActive(TIMER_A)) {}
         */
        
        for (i = -100; i <= 100; i++) {
            Roach_LeftMtrSpeed(i);
            Roach_RightMtrSpeed(i);
            printf("SPEED: %d", i);
            
            TIMERS_InitTimer(TIMER_A, time);
            while (TIMERS_IsTimerActive(TIMER_A)) {}
        }
    }
}

int main(int argc, char** argv) {
    SERIAL_Init();
    BOARD_Init();
    Roach_Init();
    TIMERS_Init();

    //moveForwardBack();
    moveGradualForwardBack();
    

}

