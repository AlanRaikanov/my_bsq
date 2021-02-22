#include "my_bsq.h"
#include <stdio.h>
#include <stdlib.h>

void bit_field_write(char bit, char width, char value, char* byte) {
    unsigned char mask = 0;
    while (width--) {
        mask = mask << 1;
        mask |= 1;
    }
    value = value << bit;
    mask = mask << bit;
    mask ^= 0xFF;
    *byte &= mask;
    *byte |= value;
}

char* fill_bit_line(char* input_line, char* tmp) {
    input_line = malloc(sizeof(char) * (my_strlen(tmp) / 4 + 2));
    int k = 0;
    int i = 0;
    for (; tmp[k]; i++) {
        // input_line[i] = 0;
        for (int j = 0; j < 4 && tmp[k]; j++, k++) {
            char tmp_value = 0;
            if (tmp[k] == '.') {
                tmp_value = 1;
            }
            bit_field_write(2*j, 2, tmp_value, &input_line[i]);
        }
    }
    input_line[i] = 0;
    return input_line;
}

int my_strlen(char* str) {
    int i = 0;
    while (str[i]) {
        i++;
    }
    return i;
}

int my_atoi(const char* str) {
    int res = 0;
    int sign = 1;
    int i = 0;

    if (str[0] == '-') {
        sign = -1;
        i++;
    }

    for (; str[i] != '\0'; ++i) {
        res = res * 10 + str[i] - '0';
    }

    return sign * res;
}

void rows_count(t_map_char* input, int fd) { 
    char* first_line = my_readline(fd);
    input->y = my_atoi(first_line);
    free(first_line);
}

void fill_map(t_map_char* input, int fd) {
    input->field = malloc(sizeof(char*) * input->y);
    for (int i = 0; i < input->y; i++) {
        char* tmp = my_readline(fd);
        input->field[i] = fill_bit_line(input->field[i], tmp);
        printf("%s", tmp); // temporary!!!!!!!!!!!!!!!!!!!!!!!!!!
        if (i == 0) {
            input->x = my_strlen(tmp);
            // printf("\n%d\n", input->x); // Temporary!!!!!!!!!!!
        }
        free(tmp);
    }
}

void get_map(t_map_char* input, int fd) {
    rows_count(input, fd);
    fill_map(input, fd);
}

t_map_char* fill_x(t_map_char* input, t_pos* best) {
    for (int i = 0; i < best->value; i++) {
        for (int j = 0; j < best->value; j++) {
            input->field[best->y - i][best->x - j] = 'x';
        }
    }
    return input;
}

char bit_field_read(char bit, char width, char byte) {
    unsigned char mask;

    mask = 0;
    while (width--) {
        mask = mask << 1;
        mask |= 1;
    }

    byte = byte >> bit;
    return(byte & mask);
}

char get_letter(char bit, char byte) {
    switch (bit_field_read(bit, 2, byte)) {
    case 0:
        return 'o';
    case 1:
        return '.';
    default:
        return 'x';
    }
    return 0;
}

void printmap(t_map_char* input) {
    for (int a = 0; a < input->y; a++) { 
        int d = 0;
        char tmp[input->x + 1];
        for (int b = 0; d < input->x; b++) {
            for (char c = 0; c < 4 && d < input->x; c++, d++) {
                tmp[d] = get_letter(2*c, input->field[a][b]);
            }
        }
        tmp[input->x] = 0;
        printf("%s\n", tmp);
    }
}

int main() {
    t_map_char* input = malloc(sizeof(t_map_char));

    int fd = open("input", O_RDONLY);

    get_map(input, fd);

    close(fd);

    t_pos* best = malloc(sizeof(t_pos));

    method(input, best);

    printf("\nLargest square: x - %d, y - %d, value - %d\n", best->x, best->y, best->value);

    // fill_x(input, best);

    printmap(input);

    free(best);
    for (int i = 0; i < input->y; i++) {
        free(input->field[i]);
    }
    free(input->field);
    free(input);
    // free map

    return 0;
}