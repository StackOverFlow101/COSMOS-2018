/* 
 * File:   TestHarnessMain.c
 * Author: Richard Luo/Raghav Gupta
 *
 * This is a test harness for all the hardware on the Roach. This lets us
 * quickly and easily test each piece of hardware.
 * 
 * Created on July 18, 2018, 11:16 AM
 */

#include <stdio.h>
#include <stdlib.h>

#include "serial.h"
#include "timers.h"
#include "BOARD.h"
#include "roach.h"

#define INVERT_CONSTANT 1023
#define THRESHOLD 511
#define maxSpeed 100
#define minSpeed -100

void showLightLED(void);
void bumperToMotor(void);

/**
 * Runs the code to test all the hardware.
 * Does not use blocking code
 */
void run(void) {
    TIMERS_InitTimer(0, 100);
    while (1) {
        if (TIMERS_IsTimerExpired(0)) {
            //Use LEDs to display light sensor
            showLightLED();
            
            //Tests the bumper and motors
            bumperToMotor();
            
            TIMERS_InitTimer(0, 100);
        }
    }
}

/*
 * If front left bumper is hit, left motor goes forwards
 * If front right bumper is hit, right motor goes forwards
 * If back left bumper is hit, left motor goes backwards
 * If back right bumper is hit, right motor goes backwards
 * 
 * A motor stops if its respective front and back bumpers are pressed
 * A motor keeps going until one if its other control bumpers is pressed
 */
void bumperToMotor(void) {
    if (Roach_ReadFrontLeftBumper()) {
        Roach_LeftMtrSpeed(maxSpeed);
    }
    if (Roach_ReadFrontRightBumper()) {
        Roach_RightMtrSpeed(maxSpeed);
    }
    if (Roach_ReadRearLeftBumper()) {
        Roach_LeftMtrSpeed(minSpeed);
    }
    if (Roach_ReadRearRightBumper()) {
        Roach_RightMtrSpeed(minSpeed);
    }

    if (Roach_ReadRearLeftBumper() && Roach_ReadFrontLeftBumper()) {
        Roach_LeftMtrSpeed(0);
    }
    if (Roach_ReadRearRightBumper() && Roach_ReadFrontRightBumper()) {
        Roach_RightMtrSpeed(0);
    }
}

/**
 * Displays the light level from the sensor through the LED
 */
void showLightLED(void) {
    int lightLevel, interval, numLED, i;
    interval = INVERT_CONSTANT / 12; //There are 12 LEDs

    int LEDs = 0;

    LEDs = 0;

    //Read, invert, and scale the light level
    lightLevel = INVERT_CONSTANT - Roach_LightLevel();
    numLED = lightLevel / interval;
    
    //Convert the levels to the LED sequence
    if (numLED != 0) LEDs = 0b000000000001;
    for (i = 1; i < numLED; i++) {
        LEDs <<= 1;
        LEDs++;
    }

    Roach_LEDSSet(LEDs);
}

int main(int argc, char** argv) {
    SERIAL_Init();
    BOARD_Init();
    TIMERS_Init();
    Roach_Init();

    run();
}

