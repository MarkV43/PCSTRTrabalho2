#include <time.h>
#include "constants.h"
#include "variables.h"

void control_temperature_pi() {
    // TODO inserir código de controle da temperatura
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