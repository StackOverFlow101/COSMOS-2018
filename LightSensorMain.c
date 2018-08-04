/* 
 * File:   LightSensorMain.c
 * Author: Richard Luo/Raghav Gupta
 *
 * Notes: Less light means higher lightLevel reading (1023 for coverered)
 * 
 * Created on July 17, 2018, 10:54 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "timers.h"
#include "BOARD.h"
#include "roach.h"
#include "serial.h"

#define INVERT_CONSTANT 1023
#define THRESHOLD 511

void testCode(void) {
    int lightLevel;
    while (1) {
        //read, display light level:
        lightLevel = Roach_LightLevel();
        printf("Light Level = %d\n", lightLevel);

        //Wait 0.1 second:
        TIMERS_InitTimer(0, 100);
        while (TIMERS_IsTimerActive(0));
    }
}

/**
 * Displays the light level from the sensor through the LED
 */
void showLightLED(void) {
    int lightLevel, interval, numLED, i;
    interval = INVERT_CONSTANT / 12; //There are 12 LEDs

    int LEDs = 0;

    while (1) {
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

        //Wait 0.1 second:
        TIMERS_InitTimer(0, 100);
        while (TIMERS_IsTimerActive(0));
    }
}

/**
 * Displays red if in darkness, green if in light. Darkness is any light level
 * above the threshold.
 */
void simpleLEDShow(void) {
    int color;
    while (1) {
        if (Roach_LightLevel() >= THRESHOLD) {
            color = 0b111100000000;
            Roach_LEDSSet(color);
        }
        else {
            color = 0b000011110000;
            Roach_LEDSSet(color);
        }
        
        //Wait 0.2 seconds
        TIMERS_InitTimer(0, 200);
        while (TIMERS_IsTimerActive(0));
    }
}

int main(int argc, char** argv) {
    SERIAL_Init();
    BOARD_Init();
    Roach_Init();
    TIMERS_Init();

    //testCode();
    //showLightLED();
    simpleLEDShow();
}

