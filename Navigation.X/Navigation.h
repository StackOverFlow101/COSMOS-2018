/* 
 * File:   Navigation.h
 * Author: Rice/Spaghetti
 *
 * Created on July 24, 2018, 11:20 AM
 */

#ifndef NAVIGATION_H
#define	NAVIGATION_H

/**
* @Function Forward(int speed)
* @param speed - how fast Roach should go (from -100 to 100)
* @return nothing
* @brief Use this function to make the Roach go straight Forward
* @author Rice/Spaghetti
 */
void Forward(int speed);

/**
* @Function Reverse(int speed)
* @param speed - how fast Roach should go (from -100 to 100)
* @return nothing
* @brief Use this function to make the Roach go straight Backwards
* @author Rice/Spaghetti
 */
void Reverse(int speed);

/**
* @Function Stop()
* @param nothing
* @return nothing
* @brief Use this function to make the Roach stop
* @author Rice/Spaghetti
 */
void stop();

/**
* @Function RotateRight(int speed)
* @param speed - how fast Roach should go (from -100 to 100)
* @return nothing
* @brief Use this function to make the Roach spin clockwise
* @author Rice/Spaghetti
 */
void RotateRight(int speed);

/**
* @Function RotateLeft(int speed)
* @param speed - how fast Roach should go (from -100 to 100)
* @return nothing
* @brief Use this function to make the Roach spin counterclockwise
* @author Rice/Spaghetti
 */
void RotateLeft(int speed);

/**
* @Function PivotLeft(int speed)
* @param speed - how fast Roach should go (from -100 to 100)
* @return nothing
* @brief Use this function to make the Roach pivot to the left
* @author Rice/Spaghetti
 */
void PivotLeft(int speed);

/**
* @Function PivotRight(int speed)
* @param speed - how fast Roach should go (from -100 to 100)
* @return nothing
* @brief Use this function to make the Roach pivot to the right
* @author Rice/Spaghetti
 */
void PivotRight(int speed);

/**
* @Function ArcLeft(int speed)
* @param speed - how fast Roach should go (from -100 to 100)
* @return nothing
* @brief Use this function to make the Roach move in a gentle arc to the left.
* The curvature of the arc remains the same regardless of the speed.
* @author Rice/Spaghetti
 */
void ArcLeft(int speed);

/**
* @Function ArcRight(int speed)
* @param speed - how fast Roach should go (from -100 to 100)
* @return nothing
* @brief Use this function to make the Roach move in a gentle arc to the right.
* The curvature of the arc remains the same regardless of the speed.
* @author Rice/Spaghetti
 */
void ArcRight(int speed);

#endif

