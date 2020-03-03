//
// Created by nick on 27.02.2020.
//

#include "../include/vector.h"
#include "stdlib.h"
#include <stdio.h>

struct vec_t *new_vec() {
    return calloc(sizeof(struct vec_t), 1);
}

void vec_push(struct message_t *msg, struct vec_t *vec) {
    vec->msgs = realloc(vec->msgs, ++vec->len * sizeof(msg));
    vec->msgs[vec->len - 1] = msg;
}

int vec_size(struct vec_t *vec) {
    return vec->len;

}
void vec_print(struct vec_t *vec) {
    for (int i = 0; i < vec_size(vec) - 1; i++) {
        printf("%s\n", vec->msgs[i]->commit);
        printf("%s\n", vec->msgs[i]->author);
        printf("%s\n", vec->msgs[i]->date);
//        printf("%d\n", vec->msgs[i]->total_time);
    }
}

void vec_free(struct vec_t *vec) {
    for (int i = 0; i < vec_size(vec); i++) {
        msg_free(vec->msgs[i]);
    }
    free(vec->msgs);
    free(vec);
}