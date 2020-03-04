#include <stdio.h>
#include <testy/parser.h>

#define FILE_PATH "/home/nick/TP/text.txt"
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
    input_parse(f, vec, buffer, authors_email, begining_of_time,end_of_time);
    print_task(authors_email, begining_of_time, end_of_time);

    fclose(f);
    transfer_date_to_sec(vec);
    hash_selection(begining_of_time, end_of_time, authors_email, vec);
    vec_free(vec);
}

