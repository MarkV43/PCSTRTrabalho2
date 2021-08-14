#include <time.h>
#include <stdlib.h>
#include "udpclient.h"
#include "constants.h"
#include "variables.h"

void control_waterlevel_pi() {

    pthread_mutex_lock(&mutex_Verr);
    Verr = Vref - (H * B);
    pthread_mutex_unlock(&mutex_Verr);

    if (Verr > 0) {
        pthread_mutex_lock(&mutex_Vint);
        Vint += Verr * 0.03f;
        pthread_mutex_unlock(&mutex_Vint);
    }

    //integral proportional water level control

    pthread_mutex_lock(&mutex_Ni);
    Ni = clamp(Verr * pV + Vint / iV, 0, 100);
    pthread_mutex_unlock(&mutex_Ni);

    //makes sure the water level never reaches 3 meters
    pthread_mutex_lock(&mutex_Nf);
    if (H > 2.9) {
        Nf = clamp(-Verr * NfV / B, 0, 100);
    } else {
        Nf = 0;
    }
    pthread_mutex_unlock(&mutex_Nf);

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

void control_waterlevel() {
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    t.tv_sec++;

    while (1) {
        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &t, NULL);

        t.tv_nsec += LEVEL_INT_NS;
        while (t.tv_nsec >= NSEC_PER_SEC) {
            t.tv_nsec -= NSEC_PER_SEC;
            t.tv_sec++;
        }

        control_waterlevel_pi();
    }
}