#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include "variables.h"


void print_data() {

    while(1){

        sleep(1);
        pthread_mutex_lock(&mutex_console);
        printf("VALVES CONTROL:\n");
        printf("Auxiliary tank valve:");
        pthread_mutex_lock(&mutex_Na);
        printf("%f\n", Na);
        pthread_mutex_unlock(&mutex_Na);
        printf("Fresh water valve:");
        pthread_mutex_lock(&mutex_Ni);
        printf("%f\n", Ni);
        pthread_mutex_unlock(&mutex_Ni);
        printf("Sewer outlet valve:");
        pthread_mutex_lock(&mutex_Nf);
        printf("%f\n", Nf);
        pthread_mutex_unlock(&mutex_Nf);
        printf("Heating element:");
        pthread_mutex_lock(&mutex_Q);
        printf("%f\n", Q);
        pthread_mutex_unlock(&mutex_Q);
        printf("-----------------------\n");
        printf("BOILER SENSORS:\n");
        printf("Water temperature:");
        pthread_mutex_lock(&mutex_T);
        printf("%f\n", T);
        if (activatealarm){
            printf("ALARME\n");
            printf("Estamos fazendo uma sopa!?\n Água muito quente!\n");
        }
        pthread_mutex_unlock(&mutex_T);
        printf("Water level:");
        pthread_mutex_lock(&mutex_H);
        printf("%f\n", H);
        pthread_mutex_unlock(&mutex_H);
        printf("Input water temperature:");
        pthread_mutex_lock(&mutex_Ti);
        printf("%f\n", Ti);
        pthread_mutex_unlock(&mutex_Ti);
        printf("Water usage:");
        pthread_mutex_lock(&mutex_No);
        printf("%f\n", No);
        pthread_mutex_unlock(&mutex_No);
        printf("Ambient temperature:");
        pthread_mutex_lock(&mutex_Ta);
        printf("%f\n", Ta);
        pthread_mutex_unlock(&mutex_Ta);
        pthread_mutex_lock(&mutex_Vint);
        printf("VEI: %f\n", Vint);
        pthread_mutex_unlock(&mutex_Vint);
        pthread_mutex_lock(&mutex_Tint);
        printf("TEI: %f\n", Tint);
        pthread_mutex_unlock(&mutex_Tint);
        printf("=======================\n");
        pthread_mutex_unlock(&mutex_console);
    }
}