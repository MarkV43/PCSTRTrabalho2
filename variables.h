#ifndef TRABALHO2_VARIABLES
#define TRABALHO2_VARIABLES

#include <pthread.h>

#define clamp(n, a, b) ((n) < (a) ? (a) : ((n) > (b) ? (b) : (n)))

extern float Verr, Vint, Terr, Tint, T, Ta, Ti, No, H, Q, Ni, Na, Nf, Qr, Tref, Href, Vref;

extern char buffer[14], buffer_read[14];

extern int screenInterval, activatealarm;

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
    mutex_readMessage,
    mutex_exchangeMessage,
    mutex_Tref,
    mutex_Vref,
    mutex_Href,
    mutex_B,
    mutex_console;

#endif // TRABALHO2_VARIABLES