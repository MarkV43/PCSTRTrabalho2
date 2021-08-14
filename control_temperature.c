#include <time.h>
#include <stdlib.h>
#include "udpclient.h"
#include "constants.h"
#include "variables.h"

void control_temperature_pi() {
    pthread_mutex_lock(&mutex_readMessage);
    exchange_message("st-0", buffer_read);
    T = strtof(buffer_read + 3, NULL);
    exchange_message("sta0", buffer_read);
    Ta = strtof(buffer_read + 3, NULL);
    pthread_mutex_unlock(&mutex_readMessage);

    pthread_mutex_lock(&mutex_Terr);
    Terr = Tref - T;
    pthread_mutex_lock(&mutex_Tint);
    Tint += Terr * 0.03f;

    pthread_mutex_lock(&mutex_Na);
    pthread_mutex_lock(&mutex_Q);

    pthread_mutex_unlock(&mutex_Terr);
    pthread_mutex_unlock(&mutex_Tint);

    Na = (Terr * pT + Tint / iT);
    if (H > 2.8) {
        Q = Na;
        if (Na < 0){
            Q = 0;
            Na = 0;
        }
    } else {
        if (Na > 10) {
            Q = (Na - 10) * S;
            Na = 10;
        } else if (Na < 0) {
            Q = 0;
            Na = 0;
        }
    }
    pthread_mutex_unlock(&mutex_Na);
    pthread_mutex_unlock(&mutex_Q);

    pthread_mutex_lock(&mutex_exchangeMessage);
    buffer[0] = 'a';
    buffer[1] = 'n';
    buffer[2] = 'i';
    gcvt(Ni, 6, buffer + 3);
    exchange_message(buffer, NULL);
    buffer[2] = 'f';
    gcvt(Nf, 6, buffer + 3);
    exchange_message(buffer, NULL);
    pthread_mutex_unlock(&mutex_exchangeMessage);
}

#ifndef CLOCK_MONOTONIC
#define CLOCK_MONOTONIC 1
#endif
#ifndef TIMER_ABSTIME
#define TIMER_ABSTIME 1
#endif

void control_temperature() {
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    t.tv_sec++;

    while (1) {
        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &t, NULL);

        t.tv_nsec += TEMP_INT_NS;
        while (t.tv_nsec >= NSEC_PER_SEC) {
            t.tv_nsec -= NSEC_PER_SEC;
            t.tv_sec++;
        }

        control_temperature_pi();
    }
}