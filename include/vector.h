//
// Created by nick on 27.02.2020.
//

#ifndef HW_1_VECTOR_H
#define HW_1_VECTOR_H

#include <glob.h>
#include "parser.h"
#include "stdio.h"
struct vec_t {
    struct message_t **msgs;
    size_t len;
};

struct vec_t *new_vec();
void vec_push(struct message_t *msg, struct vec_t *vec);
int vec_size(struct vec_t *vec);
void vec_print(struct vec_t *vec);
void vec_free(struct vec_t *vec);

#endif //HW_1_VECTOR_H
