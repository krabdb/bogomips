//
//  main.c
//  bogomips
//
//  Created by Дима on 18.02.14.
//  Copyright (c) 2014 Дима. All rights reserved.
//
//
//  Standalone BogoMips program
//
//  Based on code Linux kernel code in init/main.c and
//  include/linux/delay.h
//
//  For more information on interpreting the results, see the BogoMIPS
//  Mini-HOWTO document.

//  version: 1.3
//  author: Jeff Tranter (Jeff_Tranter@Mitel.COM)

#include <stdio.h>
#include <time.h>

// portable version
static void delay(unsigned long loops)
{
    unsigned long i;
    for (i = loops; i > 0 ; i--)
        ;
}

int main(int argc, const char * argv[])
{
    unsigned long loops_per_sec = 1;
    unsigned long ticks;
    
    printf("Calibrating delay loop.. ");
    fflush(stdout);
    
    while ((loops_per_sec <<= 1)) {
        ticks = clock();
        delay(loops_per_sec);
//        delay2(loops_per_sec);
        ticks = clock() - ticks;
        printf("bp %lu\t%lu\n", loops_per_sec, ticks);
        fflush(stdout);
        if (ticks >= CLOCKS_PER_SEC) {
            loops_per_sec = (loops_per_sec / ticks) * CLOCKS_PER_SEC;
            printf("bp %lu\n", loops_per_sec);
            printf("ok - %lu.%02lu BogoMips\n",
                   loops_per_sec/500000,
                   (loops_per_sec/5000) % 100
                   );
            return 0;
        }
    }
    printf("failed\n");
    return -1;
}

