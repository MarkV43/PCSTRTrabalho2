#ifndef TRABALHO2_DOUBLE_BUFFER
#define TRABALHO2_DOUBLE_BUFFER

struct Data {
    float T;
    float Tref;
    float H;
    float Href;
};

void double_buffer();

struct Data *wait_full_buffer();

void buffer_insert_value(struct Data value);

#endif //TRABALHO2_DOUBLE_BUFFER