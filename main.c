#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include "udpclient.h"
#include "control_waterlevel.h"
#include "control_temperature.h"
#include "constants.h"

pthread_t thread_cwl;
pthread_t thread_ct;


int main() {
    printf("Hello World!");

    pthread_create(&thread_cwl, NULL, (void *)control_waterlevel, NULL);
    pthread_create(&thread_ct, NULL, (void *)control_temperature, NULL);

    pthread_join(thread_cwl, NULL);
    pthread_join(thread_ct, NULL);
}
