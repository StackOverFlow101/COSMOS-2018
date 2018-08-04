/* 
 * File:   stop_dark_main.c
 * Author: Rice and Spaghetti
 *
 * Created on July 26, 2018, 9:09 AM
 */

#include <stdio.h>
#include <stdlib.h>

#include "serial.h"
#include "BOARD.h"
#include "roach.h"
#include "timers.h"

//other includes here
#include "Navigation.h"
#include "CheckLightSensor.h"

#define CHANGE_TIMER 0
#define CHECK_TIMER 1
#define CHANGE_INTERVAL 2000
#define CHECK_INTERVAL 50
#define DEFAULT_SPEED 80

int main(int argc, char** argv) {
    SERIAL_Init();
    BOARD_Init();
    Roach_Init();
    TIMERS_Init();

    char counter, flag;
    counter = 0;
    flag = 0;

    //Separate timers for checking the light sensor and changing direction
    TIMERS_InitTimer(CHANGE_TIMER, CHANGE_INTERVAL);
    TIMERS_InitTimer(CHECK_TIMER, CHECK_INTERVAL);
    while (1) {
        //If the Roach has not met darkness yet and we need to change direction
        if (TIMERS_IsTimerExpired(CHANGE_TIMER) &&  flag == 0) {
            TIMERS_InitTimer(CHANGE_TIMER, CHANGE_INTERVAL);
            switch (counter) {
                case 0: ArcLeft(DEFAULT_SPEED);
                    break;
                case 1: ArcRight(DEFAULT_SPEED);
                    break;
                case 2: ArcLeft(-DEFAULT_SPEED);
                    break;
                case 3: ArcRight(-DEFAULT_SPEED);
                    break;
            }
            
            //This makes counter go from 0 to 3 and back to 0
            counter = (counter + 1) % 4;
        }
        
        //Check if Roach is in darkness
        if(TIMERS_IsTimerExpired(CHECK_TIMER) && CheckLightSensor() == 1) {
            Stop();
            flag = 1;
        }
    }
}

