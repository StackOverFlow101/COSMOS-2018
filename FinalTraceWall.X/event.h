/* 
 * File:   event.h
 * Author: Rice and Spaghetti
 *
 * Created on July 31, 2018, 9:57 AM
 */

#ifndef EVENT_H
#define	EVENT_H

typedef enum {
    NO_EVENT,
    ENTERED_LIGHT,
    ENTERED_DARK,
    FL_BUMPER_DOWN,
    FL_BUMPER_UP,
    FR_BUMPER_DOWN,
    FR_BUMPER_UP,
    RL_BUMPER_DOWN,
    RL_BUMPER_UP,
    RR_BUMPER_DOWN,
    RR_BUMPER_UP,
    TIMER_0_EXPIRED,
}
event_t;

// A prototype for the function that handles all the event checkers: 
event_t CheckForEvents(void);

#endif