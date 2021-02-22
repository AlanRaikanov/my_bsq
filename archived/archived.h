//for main
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//for my_readline
#include <unistd.h>
#include <stdlib.h>
#ifndef READLINE_READ_SIZE
#define READLINE_READ_SIZE 50
#endif
//for my_method.c
#include <stdarg.h>

typedef struct map_char
{
    int x, y;
    char** field;
}t_map_char;

typedef struct map_int
{
    int x, y;
    int** field;
}t_map_int;

typedef struct pos {
    int value, x, y;
}t_pos;

/*
** for main.c
*/
int my_min(int num, ...);
int my_strlen(char* str);
char* my_readline(int fd);
int my_atoi(const char* str);
void rows_count(t_map_char* input, t_map_int* output, int fd);
void fill_map(t_map_char* input, int fd);
void rows_length(t_map_char* input, t_map_int* output);
void get_map(t_map_char* input, int fd);
t_map_char* fill_x(t_map_char* input, t_pos* best);
void printout(t_map_char* input);

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