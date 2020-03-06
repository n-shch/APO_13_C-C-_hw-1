//
// Created by nick on 27.02.2020.
//

#ifndef HW_1_PARSER_H
#define HW_1_PARSER_H

#include <testy/vector.h>
#include <stdio.h>
#include <stdlib.h>




struct date_t {
    int day;
    int month;
    int year;
    int hours;
    int min;
    int sec;
};


char *search_field(char *information_line, char *field);
void parse_commit(vec_t *vec, char *buffer);
void parse_author(vec_t *vec, char *buffer);
void parse_date(vec_t *vec, char *buffer);
void searching_for_target_email(char *authors_email, char *buffer);
void searching_for_time_frame(char *begining_of_time,char *end_of_time, char *buffer);

void print_task(const char *author, const char *time_from, const char * time_to);
void input_parse(FILE *file, vec_t *vec, char *buffer, char *authors_email, char *begining_of_time,
                 char *end_of_time);






int date_to_sec(struct date_t *date);
int date_parse(char *str, struct date_t *date);
int date_rang(struct message_t *msg);
void print_date_t(struct date_t *date);
void transfer_date_to_sec(vec_t *vec);

void hash_selection(char *begining_of_time, char *end_of_time, char *authors_email, vec_t *vec);

#endif //HW_1_PARSER_H
