//
// Created by nick on 27.02.2020.
//

#ifndef HW_1_VECTOR_H
#define HW_1_VECTOR_H

#include <glob.h>
#include "stdio.h"


struct message_t {
    char *commit;
    char *author;
    char *date;
    int total_time;
};

typedef struct vec_t {
    struct message_t **msgs;
    size_t len;
} vec_t;

vec_t *new_vec();
void vec_push(struct message_t *msg, vec_t *vec);
int vec_size(vec_t *vec);
void vec_print(vec_t *vec);
void vec_free(vec_t *vec);

#endif //HW_1_VECTOR_H
