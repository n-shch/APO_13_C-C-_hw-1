//
// Created by nick on 27.02.2020.
//
#define _GNU_SOURCE

#include "testy/vector.h"
#include <stdio.h>
#include <stdlib.h>
#include "testy/parser.h"
#include <string.h>

enum Month {
    Jan = 1,
    Feb,
    Mar,
    Apr,
    May,
    Jun,
    Jul,
    Aug,
    Sep,
    Oct,
    Nov,
    Dec
};


//поиск подстроки в строке, возвращение указателя на начало подстроки с ИНФОРМАЦИЕЙ
char *search_field(char *information_line, char *field) {
    char *found = strstr(information_line, field);
    if (found) {
        found += strlen(field);
        return found;
    } else {
        return NULL;
    }
}

//если в строке содержится хэш коммита, записываем его в единицу структуры_вектора
void parse_commit(vec_t *vec, char *buffer) {
    char *found = search_field(buffer, "commit");
    if (found) {
        vec->msgs = realloc(vec->msgs, ++vec->len * sizeof(vec->msgs));
        vec->msgs[vec->len-1] = calloc(sizeof(struct message_t), 1);
        asprintf(&vec->msgs[vec->len - 1]->commit,"%.*s",40, found+1);
    }
}


//если в строке содержится автор, записываем его в единицу структуры_вектора
void parse_author(vec_t *vec, char *buffer) {
    char *found = search_field(buffer, "Author: ");
    if (found) {
        char *begin = strstr(found,"<");
        char *end = strstr(found, ">");
        if (begin && end) {
            asprintf(&vec->msgs[vec->len - 1]->author,"%.*s", (int)(end - begin - 1), begin + 1);
        }
    }
}

//если в строке содержится дата, записываем ее в единицу структуры_вектора
void parse_date(vec_t *vec, char *buffer) {
    char *found = search_field(buffer, "Date: ");
    if (found) {
        asprintf(&vec->msgs[vec->len - 1]->date,"%.*s", 20, found + 6);
    }
}

//ищем целевой email-адрес, записываем его в переменную
void searching_for_target_email(char *authors_email, char *buffer) {
    char *found = search_field(buffer, "author's email:");
    if (found) {
        char *begin = strstr(found,"<");
        char *end = strstr(found, ">");
        if (begin && end) {
            sprintf(authors_email, "%.*s", (int)(end - begin - 1), begin + 1);
        }
    }
}


//ищем временные рамки, записываем их в соответствующие переменные
void searching_for_time_frame(char *begining_of_time,char *end_of_time, char *buffer) {
    char *found = search_field(buffer, "time interval:");
    if (found) {
        found += 5;
        char *end = strstr(found, "+");
        sprintf(begining_of_time,"%.*s",(int)(end - found), found);
        char *begin = strstr(found, "-");
        end = strstr(begin, "+");
        begin +=6;
        sprintf(end_of_time,"%.*s", (int)(end - begin), begin);
    }
}


void print_task(char *author, char *time_from, char * time_to) {
    if ((!author) || (!time_from) || (!time_to)) {
        return;
    }
    printf("Author's email:%s\nTime begin: %s\nTime end:   %s\n", author, time_from, time_to);
    printf("----------------------------------------\n");
}
//считываем строки, парсим их, заполняем поля вектора
void input_parse(FILE *file,vec_t *vec, char *buffer, char *authors_email, char *begining_of_time,
                 char *end_of_time) {
    if (!file) {
        return;
    }
    while (fgets(buffer, 120, file) != NULL) {
        parse_commit(vec, buffer);
        parse_author(vec, buffer);
        parse_date(vec, buffer);
        searching_for_target_email(authors_email, buffer);
        searching_for_time_frame(begining_of_time,end_of_time, buffer);
    }
}

//перевод даты в секунды (для того, чтобы сравнивать с временными рамками)
int date_to_sec(struct date_t *date) {
    int total_time =
            (((date->year)%100) * 365 * 24 * 3600) +
                    (date->month * 31 * 24 * 3600) +
                    (date->day * 24 * 3600) +
                    (date->hours * 3600) +
                    (date->min * 60) +
                    (date->sec
                    );
    return total_time;
}

//Парсинг строки с датой в структуру с целочисленными полями - единицами измерений даты
int date_parse(char *str, struct date_t *date) {
    char *tmp;
    asprintf(&tmp, "%.*s", 3, str);
    if (!strcmp(tmp, "Jan")) {
        date->month = Jan;
    }
    if (!strcmp(tmp, "Feb")) {
        date->month = Feb;
    }
    if (!strcmp(tmp, "Mar")) {
        date->month = Mar;
    }
    if (!strcmp(tmp, "Apr")) {
        date->month = Apr;
    }
    if (!strcmp(tmp, "May")) {
        date->month = May;
    }
    if (!strcmp(tmp, "Jun")) {
        date->month = Jun;
    }
    if (!strcmp(tmp, "Jul")) {
        date->month = Jul;
    }
    if (!strcmp(tmp, "Aug")) {
        date->month = Aug;
    }
    if (!strcmp(tmp, "Sep")) {
        date->month = Sep;
    }
    if (!strcmp(tmp, "Oct")) {
        date->month = Oct;
    }
    if (!strcmp(tmp, "Nov")) {
        date->month = Nov;
    }
    if (!strcmp(tmp, "Dec")) {
        date->month = Dec;
    }
    str += 4;
    char day[2];
    sprintf(day,"%.*s", 2,str);
    date->day = atoi(day);
    if (date->day / 10 == 0) {
        str += 2;
    } else {
        str += 3;
    }
//    hours
    sprintf(day, "%.*s", 2, str);
    date->hours = atoi(day);
//    minutes
    str += 3;
    sprintf(day, "%.*s", 2, str);
    date->min = atoi(day);
//    seconds
    str += 3;
    sprintf(day, "%.*s", 2, str);
    date->sec = atoi(day);
    str+= 3;
    char year[4];
    sprintf(year, "%.*s", 4, str);
    date->year = atoi(year);
    free(tmp);
    return 0;
}

void print_date_t(struct date_t *date) {
    printf("Day:%d\nMonth:%d\nYear:%d\nTime %d:%d:%d\n",
            date->day,
            date->month,
            date->year,
            date->hours,
            date->min,
            date->sec
            );
}

//заполнение единицы структуры вектора секундным аналогом времени
int date_rang(struct message_t *msg) {
    struct date_t *tmp = calloc(sizeof(struct date_t), 1);
    date_parse(msg->date,tmp);
    msg->total_time = date_to_sec(tmp);
    free(tmp);
    return 0;
}

void transfer_date_to_sec(vec_t *vec) {
    for (int i = 0; i < vec_size(vec) - 1; i++) {
        date_rang(vec->msgs[i]);
    }
}

//пробегаемся по вектору, ищем совпадения по автору и по попаданию дат во временной промежуток
void hash_selection(char *begining_of_time, char *end_of_time, char *authors_email,vec_t *vec) {
    struct date_t *tmp = calloc(sizeof(struct date_t), 1);
    date_parse(begining_of_time,tmp);
    int begining_of_time_sec;
    begining_of_time_sec = date_to_sec(tmp);
    date_parse(end_of_time,tmp);
    int end_of_time_sec;
    end_of_time_sec = date_to_sec(tmp);
    free(tmp);
//    printf("from: %d\nto  : %d\n", begining_of_time_sec, end_of_time_sec);

    for (int i = 0; i < vec_size(vec) - 1; i++) {
        if ((!strcmp(vec->msgs[i]->author,authors_email)) &&
        (vec->msgs[i]->total_time >= begining_of_time_sec) &&
        (vec->msgs[i]->total_time <= end_of_time_sec)) {
            printf("%s\n", vec->msgs[i]->author);
            printf("%s\n", vec->msgs[i]->date);
            printf("%s\n", vec->msgs[i]->commit);
            printf("----------------------------------------\n");
        }
    }
}


int func(int a) {
    return a;
}