/*
 * File:   LED_Main.c
 * Author: Richard Luo/Raghav Gupta
 * 
 * Notes: Each bit for LEDSSET represents a LED. 1 denotes on, 0 denotes off.
 * 
 * Created on July 17, 2018, 10:25 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "timers.h"
#include "BOARD.h"
#include "roach.h"
#include "serial.h"

#define TIMER_A 0
#define TIMER_B 1
#define THIRD_BIT 0b001000 //The rightmost bit is the zero-th bit
#define FOURTH_BIT 0b010000

/**
 * Makes the LED lights turn on from left to right and then right to left.
 */
void LEDpong(void) {
    int i, j;

    while (1) {
        i = 1;
        for (j = 1; j < 12; j++) {
            Roach_LEDSSet(i);
            
            //Makes the next LED on the right turn on
            i <<= 1;
            TIMERS_InitTimer(TIMER_B, 500);
            while (TIMERS_IsTimerActive(TIMER_B));
        }
      
        for (j = 1; j < 12; j++) {
            Roach_LEDSSet(i);
            
            //Makes the next LED on the left turn on
            i >>= 1;
            TIMERS_InitTimer(TIMER_B, 500);
            while (TIMERS_IsTimerActive(TIMER_B));
        }
    }
}

void testCode1(void) {
    Roach_LEDSSet(0b101010101010);
    TIMERS_InitTimer(0, 1000);
    while (TIMERS_IsTimerActive(0));

    //Truncates the top 4 bits
    Roach_LEDSSet(0xBEEF);
    TIMERS_InitTimer(0, 1000);
    while (TIMERS_IsTimerActive(0));

    Roach_LEDSSet(6);
    TIMERS_InitTimer(0, 1000);
    while (TIMERS_IsTimerActive(0));

    Roach_LEDSSet('c');
    TIMERS_InitTimer(0, 1000);
    while (TIMERS_IsTimerActive(0));
}

void testCode2(void) {
    char BumperReading = 12;
    if (THIRD_BIT & BumperReading) {
        printf("Third bit high!");
    }
    else {
        printf("Third bit is low");
    }
}

void testCode3(void) {
    int Readout = 0b000000000001;
    while (1) {
        //wait one second:
        TIMERS_InitTimer(0, 1000);
        while (TIMERS_IsTimerActive(0));
        //update LED bar:
        Roach_LEDSSet(Readout);
        Readout = Readout | (Readout << 1);
    }
}

/**
 * Checks whether the third or fourth bit is one
 */
void thirdOrFourthBitHigh(void) {
    char BumperReading = 0b111111;
    if ((0 & BumperReading) || (FOURTH_BIT & BumperReading)) {
        printf("Third or fourth bit high!");
    }
    else {
        printf("Third and fourth bits are low");
    }
}

int main(int argc, char** argv) {

    SERIAL_Init();
    BOARD_Init();
    Roach_Init();
    TIMERS_Init();

    //testCode1();
    //testCode2();
    //thirdOrFourthBitHigh();
    
    LEDpong();
}
