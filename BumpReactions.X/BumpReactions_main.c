/* 
 * File:   BumpReactions_main.c
 * Author: Rice and Spaghetti
 *
 * Created on July 25, 2018, 3:14 PM
 */

#include "serial.h"
#include "BOARD.h"
#include "roach.h"
#include "timers.h"

//other includes here
#include "Navigation.h"
#include "Bumpers.h"

#define INTERVAL 50
#define DEFAULT_SPPED 80

int main(int argc, char** argv) {
    SERIAL_Init();
    BOARD_Init();
    Roach_Init();
    TIMERS_Init();

    char bumperReading;

    TIMERS_InitTimer(0, INTERVAL);
    while (1) {
        if (TIMERS_IsTimerExpired(0)) {
            bumperReading = CheckForBumps();

            //Only care if bumper was pressed
            if (bumperReading & 0b10000) {

                //Check if FL bumper is pressed
                if (bumperReading & 0b000000001) {
                    ArcRight(-DEFAULT_SPPED);
                } 
                //Check if FR bumper is pressed
                else if (bumperReading & 0b10) {
                    ArcLeft(-DEFAULT_SPPED);
                }
                //Check if RL bumper is pressed
                else if (bumperReading & 0b100) {
                    ArcRight(DEFAULT_SPPED);
                }
                //Check if RR bumper is pressed
                else if (bumperReading & 0b1000) {
                    ArcLeft(DEFAULT_SPPED);
                }
            }

            TIMERS_InitTimer(0, INTERVAL);
        }
    }
}
