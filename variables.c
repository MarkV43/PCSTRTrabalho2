#include <pthread.h>

float Verr, Vint = 0,
            Terr, Tint = 0;

// sensors
float T, Ta, Ti, No, H;
// actuators
float Q, Ni, Na, Nf;
// others
float Qr;

char buffer[20] = "a__";

int screenInterval = 0;

///////////////////////
// Mutexes
pthread_mutex_t mutex_Verr,
    mutex_Vint,
    mutex_Terr,
    mutex_Tint,
    mutex_T,
    mutex_Ta,
    mutex_Ti,
    mutex_No,
    mutex_H,
    mutex_Q,
    mutex_Ni,
    mutex_Na,
    mutex_Nf,
    mutex_Qr,
    mutex_buffer,
    mutex_screenInterval;