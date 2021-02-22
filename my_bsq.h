//for main
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//for my_readline
#include <unistd.h>
#include <stdlib.h>
#ifndef READLINE_READ_SIZE
#define READLINE_READ_SIZE 500
#endif
//for my_method.c
#include <stdarg.h>

typedef struct map_char {
    int x, y;
    char** field;
}t_map_char;

typedef struct pos {
    int value, x, y;
}t_pos;

/*
** for my_bsq.c
*/
int my_strlen(char* str);
char* my_readline(int fd);
int my_atoi(const char* str);
void rows_count(t_map_char* input, int fd);
void fill_map(t_map_char* input, int fd);
void get_map(t_map_char* input, int fd);
t_map_char* fill_x(t_map_char* input, t_pos* best);
void printmap(t_map_char* input);
char bit_field_read(char bit, char width, char byte);
void bit_field_write(char bit, char width, char value, char* byte);

/*
** for my_method.c
*/
int my_min(int num, ...);
t_pos* method(t_map_char* input, t_pos* best);

/*
** for my_readline.c
*/
void my_strcpy(char* dest, char* src);
int buf_has_new_line(char* buf);
char* my_realloc_str(char* str, int size);
int copy_rest_of_previous_line(char* buf, char* line);
int buf_to_line(char* buf, char* line, int line_index);
void clear(char* buf);
char* my_readline(int fd);