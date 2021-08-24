#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "udpclient.h"
#include "constants.h"
#include "variables.h"

void alarm_loop() {
    // Read all values
    printf("ALARM\n");

    pthread_mutex_lock(&mutex_exchangeMessage);

    exchange_message("sta0", buffer_read);

    pthread_mutex_lock(&mutex_Ta);
    printf("ALARM Ta %s\n", buffer_read);
    Ta = strtof(buffer_read + 3, NULL);
    pthread_mutex_unlock(&mutex_Ta);

    exchange_message("st-0", buffer_read);

    pthread_mutex_lock(&mutex_T);
    printf("ALARM T  %s\n", buffer_read);
    T = strtof(buffer_read + 3, NULL);
    pthread_mutex_unlock(&mutex_T);

    exchange_message("sti0", buffer_read);

    pthread_mutex_lock(&mutex_Ti);
    printf("ALARM Ti %s\n", buffer_read);
    Ti = strtof(buffer_read + 3, NULL);
    pthread_mutex_unlock(&mutex_Ti);

    exchange_message("sno0", buffer_read);

    pthread_mutex_lock(&mutex_No);
    printf("ALARM No %s\n", buffer_read);
    No = strtof(buffer_read + 3, NULL);
    pthread_mutex_unlock(&mutex_No);

    exchange_message("sh-0", buffer_read);

    pthread_mutex_lock(&mutex_H);
    printf("ALARM H  %s\n", buffer_read);
    H = strtof(buffer_read + 3, NULL);
    pthread_mutex_unlock(&mutex_H);

    pthread_mutex_unlock(&mutex_exchangeMessage);
}

#ifndef CLOCK_MONOTONIC
#define CLOCK_MONOTONIC 1
#endif
#ifndef TIMER_ABSTIME
#define TIMER_ABSTIME 1
#endif

void alarm() {
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    t.tv_sec++;

    while (1) {
        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &t, NULL);

        t.tv_nsec += ALARM_INT_NS;
        while (t.tv_nsec >= NSEC_PER_SEC) {
            t.tv_nsec -= NSEC_PER_SEC;
            t.tv_sec++;
        }

        alarm_loop();
    }
}