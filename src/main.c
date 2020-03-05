#include <stdio.h>
#include <testy/parser.h>

#define FILE_PATH "../text.txt"
int main() {
    FILE *f = fopen(FILE_PATH, "r");
    if (!f) {
        printf("some error occurred\n");
        return 0;
    } else {
        printf("file was opened successfully\n");
    }

    char buffer[255];
    char authors_email[255];
    char begining_of_time[255];
    char end_of_time[255];
    struct vec_t *vec = new_vec();



//    по условию, программа помимо информации вида той, что выводит команда gitlog,
//    ждет на входе таргетированный email-адресс и
//    временные рамки для поиска.
//    я решил сделать так, чтобы поля с этой информацией
//    были помечены следующим образом:
//    author's email: <chessmate13@mail.ru>
//    time interval: Sun Nov 17 13:55:08 2019 +0000 - Sun Dec 1 13:24:51 2019 +0300


//    по условию, чтение осуществляется с stdin, но я оставил здесь f просто для
//    удобства демонстрации работы программы с большим объемом информации
//    можно подставить вместо f -> stdin , тогда программа будет иметь функционал
//    той задачи, которая дана в условии



    input_parse(f, vec, buffer, authors_email, begining_of_time,end_of_time);
    print_task(authors_email, begining_of_time, end_of_time);

    fclose(f);
    transfer_date_to_sec(vec);
    hash_selection(begining_of_time, end_of_time, authors_email, vec);
    vec_free(vec);
}

