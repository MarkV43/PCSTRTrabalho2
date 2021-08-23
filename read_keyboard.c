#include <time.h>
#include <stdlib.h>
#include "udpclient.h"
#include "constants.h"
#include "variables.h"

void read_keyboard(){

    char cmd;
    char temp[100];

    printf("Mudar qual referência?\n");
    printf("Digite: 'T' para temperatura.\n");
    printf("Digite: 'H' para altura.\n");

    cmd = getchar();
    
    if (cmd == "T"){
        printf("Digite a nova referência para temperatura:\n");
        printf("Exemplo:\n 30.0\n");

        gets(temp);

        pthread_mutex_lock(&mutex_Tref);
        Tref = strtof(temp, NULL);
        pthread_mutex_unlock(&mutex_Tref);

    } else if (cmd == "H")
    {
        printf("Digite a nova referência para altura do tanque:\n");
        printf("Exemplo:\n 2.5\n");

        gets(temp);

        pthread_mutex_lock(&mutex_Href);
        Href = strtof(temp, NULL);
        pthread_mutex_unlock(&mutex_Href);

    } else {

        printf("Comando não compreendido.\n");

    }
    
}