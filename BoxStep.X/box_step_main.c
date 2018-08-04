/* 
 * File:   box_step_main.c
 * Author: Rice and Spaghetti
 *
 * Callibrated for Roach "GRANNY WEATHERWAX"
 * 
 * Created on July 27, 2018, 11:20 AM
 */

#include <stdio.h>
#include <stdlib.h>

#include "serial.h"
#include "BOARD.h"
#include "roach.h"
#include "timers.h"

//other includes here
#include "Navigation.h"

#define DEFAULT_SPEED 100
#define ROTATE_TIME 610
#define MOVE_TIME 1100

#define T_360 2500 //change as appropriate
#define T_FOOT 1500 //change as appropriate
#define MAX_SPEED 100

void testCode() {
    char steps_remaining = 8;
    TIMERS_InitTimer(0, 1);
    while (1) {
        if (TIMERS_IsTimerExpired(0)) {
            switch (steps_remaining) {
                case 8:
                case 6:
                case 4:
                case 2:
                    TIMERS_InitTimer(0, T_FOOT);
                    Forward(MAX_SPEED);
                    steps_remaining--;
                    break;
                case 7:
                case 5:
                case 3:
                case 1:
                    TIMERS_InitTimer(0, T_360 / 4);
                    RotateLeft(MAX_SPEED);
                    steps_remaining--;
                    break;
                case 0:
                    Stop();
            }
        }
    }
}

void makeSquare() {
    char flag; //0 for moving straight, 1 for turning
    flag = 0;

    Forward(DEFAULT_SPEED);
    TIMERS_InitTimer(0, MOVE_TIME);

    while (1) {
        if (TIMERS_IsTimerExpired(0)) {
            if (flag == 0) {
                RotateLeft(DEFAULT_SPEED);
                TIMERS_InitTimer(0, ROTATE_TIME);
            } else {
                Forward(DEFAULT_SPEED);
                TIMERS_InitTimer(0, MOVE_TIME);
            }
            flag = (flag + 1) % 2;
        }
    }
}

void makeTriangle() {
    makePolygon(3);
}

void makePolygon(int numSides) {
    char steps_remaining = 8;
    TIMERS_InitTimer(0, 1);
    while (1) {
        if (TIMERS_IsTimerExpired(0)) {
            switch (steps_remaining) {
                case 8:
                case 6:
                case 4:
                case 2:
                    TIMERS_InitTimer(0, T_FOOT);
                    Forward(MAX_SPEED);
                    steps_remaining--;
                    break;
                case 7:
                case 5:
                case 3:
                case 1:
                    TIMERS_InitTimer(0, T_360 / numSides);
                    RotateLeft(MAX_SPEED);
                    steps_remaining--;
                    break;
                case 0:
                    steps_remaining = 8;
            }
        }
    }
}

int main(int argc, char** argv) {
    SERIAL_Init();
    BOARD_Init();
    Roach_Init();
    TIMERS_Init();

    //makeSquare();
    //testCode();
    //makeTriangle();
    makePolygon(5);
}

