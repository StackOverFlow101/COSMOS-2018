/* 
 * File:   Hello_World_main.c
 * Author: Richard Luo and Jerry Xu
 *
 * Created on July 12, 2018, 11:10 AM
 */

#include <stdio.h>
#include <stdlib.h>

#include "serial.h"
#include "BOARD.h"
#include "roach.h"
#include "timers.h"

/**
 * Prints all the fibonacci numbers up until the max value of an unsigned int
 */
void fib() {
    unsigned int x = 1, y = 1;
    
    printf("1\r\n");
    while (1){
        printf("%u\r\n", x);
        unsigned int z = y;
        y = x;
        x += z;
        
        //Don't want to overflow
        if(x < z) return;
    }
}

int main(int argc, char** argv) {
    
    SERIAL_Init();
    BOARD_Init();
    Roach_Init();
    
    fib();
    printf("\r\n");
    
    //Everything down here is playing with conditionals-------------------------
    
    int grade = 12;
    
    //Test which school
    switch(grade) {
        case 1 ... 5:
            printf("Elementary School!\r\n");
            break;
        case 6 ... 8:
            printf("Middle School!\r\n");
            break;
        case 9 ... 12:
            printf("High School!\r\n");
            break;
    }
    
    if (grade > 0 && grade < 6){
        printf("Elementary School!\r\n");
    }
    else if (grade > 5 && grade < 9) {
        printf("Middle School!\r\n");
    }
    else if (grade > 8 && grade <13) {
        printf("High School!\r\n");
    }
    else {
        printf("Not in school!\r\n");
    }
    
    while(1);
}

