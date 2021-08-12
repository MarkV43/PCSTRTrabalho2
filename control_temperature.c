#include <time.h>
#include "constants.h"
#include "variables.h"

void control_temperature_pi() {

    Terr = Tref - T;

    Tint += Terr * 0.03f;
    if (Verr > 0)
        Vint += Verr * 0.03f;

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

    // Não esquecer de dar Mutex Lock
}

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