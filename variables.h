#ifndef TRABALHO2_VARIABLES
#define TRABALHO2_VARIABLES

#include <pthread.h>

#define clamp(n, a, b) ((n) < (a) ? (a) : ((n) > (b) ? (b) : (n)))

extern float Verr, Vint, Terr, Tint, T, Ta, Ti, No, H, Q, Ni, Na, Nf, Qr;

extern char buffer[20];

extern int screenInterval;

///////////////////////
// Mutexes
extern pthread_mutex_t mutex_Verr,
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
    mutex_screenInterval,
    mutex_exchangeMessage;

#endif // TRABALHO2_VARIABLES