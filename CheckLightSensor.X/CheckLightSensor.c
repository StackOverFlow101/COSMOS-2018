#include "roach.h"

#define INVERT_CONSTANT 1023
#define THRESHOLD 511
#define HYSTERESIS 3

/**
 * @Function CheckLightSensor(void)
 * @param none
 * @return 0 light state is still the same, 1 if it goes from light to dark,
 * 2 if it goes from dark to light.
 * @brief This function reads the light level and updates the LED bar on the
 * roach to show a bar graph of this reading. Dark and light is determined by 
 * a threshold half the range.
 * @author Rice and Spaghetti
 */
char CheckLightSensor(void) {
    static char previousState;
    char currentState;

    int lightLevel, interval, numLED, i, LEDs;
    interval = INVERT_CONSTANT / 12; //There are 12 LEDs
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
        return 0;
    }
    //Means it went from dark to bright
    else if (currentState == 0) {
        previousState = currentState;
        return 2;
    }
    //Means it went from light to dark
    else {
        previousState = currentState;
        return 1;
    }
}
