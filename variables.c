#include <pthread.h>

float Verr, Vint = 0,
            Tint = 0;

// sensors
float T, Ta, Ti, No, H;
// actuators
float Q, Ni, Na, Nf;
// others
float Qr;
// references
float Href = 2.5f,
      Vref = 0,
      Tref = 30;

char buffer[14] = "a__";

char buffer_read[14];

int screenInterval = 0;

int activatealarm = 0;

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
    mutex_screenInterval,
    mutex_readMessage,
    mutex_exchangeMessage,
    mutex_Tref,
    mutex_Vref,
    mutex_Href,
    mutex_B,
    mutex_console;