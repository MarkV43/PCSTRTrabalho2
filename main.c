#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#include "udpclient.h"
#include "control_waterlevel.h"
#include "control_temperature.h"
#include "alarm.h"
#include "print_data.h"
#include "constants.h"
#include "read_keyboard.h"

pthread_t thread_cwl;
pthread_t thread_ct;
pthread_t thread_print;
pthread_t thread_alarm;
pthread_t thread_keyboard;


void funcao_teste() {
    printf("HAHAHA\n");
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: trabalho1 <address> <port>\n");
        exit(1);
    }

    int port = atoi(argv[2]);
    setup_sockets(port, argv[1]);

    pthread_create(&thread_keyboard, NULL, (void *)read_keyboard, NULL);
    pthread_create(&thread_cwl, NULL, (void *)control_waterlevel, NULL);
    pthread_create(&thread_ct, NULL, (void *)control_temperature, NULL);
    pthread_create(&thread_print, NULL, (void *)print_data, NULL);
    pthread_create(&thread_alarm, NULL, (void *)alarm, NULL);

    pthread_join(thread_keyboard, NULL);
    pthread_join(thread_cwl, NULL);
    pthread_join(thread_ct, NULL);
    pthread_join(thread_print, NULL);
    pthread_join(thread_alarm, NULL);
}
