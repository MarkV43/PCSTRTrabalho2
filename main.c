#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include "udpclient.h"

#define NSEC_PER_SEC 1e9

int main() {
    printf("Hello World!");

    struct timespec t;
    long interval = 30e6; // 30ms
    clock_gettime(CLOCK_MONOTONIC, &t);
    t.tv_sec++;

    while (1) {
        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &t, NULL);

        t.tv_nsec += interval;
        while (t.tv_nsec >= NSEC_PER_SEC) {
            t.tv_nsec -= NSEC_PER_SEC;
            t.tv_sec++;
        }


    }
}

// Water Level Control
float control_waterlevel(float *Verr, float *Vint, float H) {
    if (*Verr > 0) {
        *Vint += *Verr * 0.03f;
    }

    *Verr = *Vref - H * B;

    return {0f, 1f};
}