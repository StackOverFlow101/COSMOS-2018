/* 
 * File:   Bumpers.h
 * Author: Rice and Spaghetti
 *
 * Created on July 25, 2018, 11:22 AM
 */

#ifndef BUMPERS_H
#define	BUMPERS_H

/**
 * @Function Bumpers_Init
 * @brief Timers must be initialized first. Call this method before use.
 * @param none
 * @return none
 */
void Bumpers_Init(void);

/**
 * @Function CheckForBumps(void)
 * @param nothing
 * @return which bumpers pressed, and what happened
 * @brief This function determines whether a bumper has beeen pressed or 
 * released. If the bumper has been pressed, the 5th and 6th bits are 1, and the
 * 1-4th bits denote which bumpers have been pressed. If the bumper has been
 * released, then the 6th bit is 1 and the 5th bit is 0, while the 1-4th bits
 * denote which bumpers have been pressed. Returns 0 for no change.
 * @author Rice and Spaghetti
 */
unsigned char CheckForBumps(void);

#endif

