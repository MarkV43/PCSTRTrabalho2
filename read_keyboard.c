#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "udpclient.h"
#include "constants.h"
#include "variables.h"

void read_keyboard() {
    while (1) {
        getchar();

        pthread_mutex_lock(&mutex_console);
        char cmd;
        char temp[100];

        printf("Mudar qual referência?\n");
        printf("Digite: 'T' para temperatura.\n");
        printf("Digite: 'H' para altura.\n");

        scanf("%s", temp);
        
        if (temp[0] == 'T') {
            printf("Digite a nova referência para temperatura:\n");
            printf("Exemplo:\n 30.0\n");

            scanf("%s", temp);
            getchar();

            pthread_mutex_lock(&mutex_Tref);
            Tref = strtof(temp, NULL);
            printf("Mudando H para %f\n", Tref);
            pthread_mutex_unlock(&mutex_Tref);

        } else if (temp[0] == 'H') {
            printf("Digite a nova referência para altura do tanque:\n");
            printf("Exemplo:\n 2.5\n");

            scanf("%s", temp);
            getchar();

            pthread_mutex_lock(&mutex_Href);
            Href = strtof(temp, NULL);
            printf("Mudando H para %f\n", Href);
            pthread_mutex_unlock(&mutex_Href);
        } else {

            printf("Comando não compreendido.\n");

        }

        pthread_mutex_unlock(&mutex_console);
    }
}