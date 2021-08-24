#include <pthread.h>
#include <stdio.h>

#define TAMBUF 100

struct Data {
    float T;
    float Tref;
    float H;
    float Href;
};

static struct Data buffer_0[TAMBUF];
static struct Data buffer_1[TAMBUF];

static int in_use = 0;
static int next_insertion = 0;
static int store = -1;

static pthread_mutex_t mutex_buffer = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t buffer_full = PTHREAD_COND_INITIALIZER;

struct Data *wait_full_buffer() {
    struct Data *buffer;
    pthread_mutex_lock(&mutex_buffer);
    while(store == -1) {
        pthread_cond_wait(&buffer_full, &mutex_buffer);
    }
    if (store == 0) {
        buffer = buffer_0;
    } else {
        buffer = buffer_1;
    }

    store = -1;
    pthread_mutex_unlock(&mutex_buffer);
    return buffer;
}

void double_buffer() {
    FILE *fp = fopen("./data.txt", "w");
    fclose(fp);
    
    while (1) {
        struct Data *buffer = wait_full_buffer();

        FILE *fp = fopen("./data.txt", "a");

        for (int i = 0; i < TAMBUF; i++) {
            struct Data data = buffer[i];
            fprintf(fp, "%f %f %f %f \n", data.T, data.Tref, data.H, data.Href);
        }

        fclose(fp);
    }
}

void buffer_insert_value(struct Data value) {
    pthread_mutex_lock(&mutex_buffer);

    if (in_use == 0) {
        buffer_0[next_insertion] = value;
    } else {
        buffer_1[next_insertion] = value;
    }

    next_insertion++;

    if (next_insertion == TAMBUF) {
        store = in_use;
        in_use = 1 - in_use;
        next_insertion = 0;
        pthread_cond_signal(&buffer_full);
    }

    pthread_mutex_unlock(&mutex_buffer);
}