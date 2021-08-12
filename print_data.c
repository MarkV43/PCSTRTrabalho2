#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include "variables.h"


void print_data() {

    while(1){

        sleep(1);
        printf("VALVES CONTROL:\n");
        printf("Auxiliary tank valve:");
        printf("%f\n", Na);
        printf("Fresh water valve:");
        printf("%f\n", Ni);
        printf("Sewer outlet valve:");
        printf("%f\n", Nf);
        printf("Heating element:");
        printf("%f\n", Q);
        printf("-----------------------\n");
        printf("BOILER SENSORS:\n");
        printf("Water temperature:");
        printf("%f\n", T);
        printf("Water level:");
        printf("%f\n", H);
        printf("Input water temperature:");
        printf("%f\n", Ti);
        printf("Water usage:");
        printf("%f\n", No);
        printf("Ambient temperature:");
        printf("%f\n", Ta);
        printf("VEI: %f\n", Vint);
        printf("TEI: %f\n", Tint);
        printf("=======================\n");
    }
}