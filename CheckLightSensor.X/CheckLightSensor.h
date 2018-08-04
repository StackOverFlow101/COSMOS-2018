/* 
 * File:   CheckLightSensor.h
 * Author: Rice and Spaghetti
 *
 * Created on July 24, 2018, 11:47 AM
 */

#ifndef CHECKLIGHTSENSOR_H
#define	CHECKLIGHTSENSOR_H

/**
 * @Function CheckLightSensor(void)
 * @param none
 * @return 0 if roach is in the darkness, 1 if the roach is in the light.
 * @brief This function reads the light level and updates the LED bar on the
 * roach to show a bar graph of this reading. It also returns a 0 or 1 to
 * indicate whether the roach is in light or shadow.
 * @author Rice and Spaghetti
 */
char CheckLightSensor(void);

#endif

