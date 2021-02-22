#include "my_bsq.h"

void my_strcpy(char* dest, char* src) {
    for (int i = 0; (dest[i] = src[i]); i++);
}

int buf_has_new_line(char* buf) {
    for (int i = 0; buf[i]; i++)
        if (buf[i] == '\n') return 1;
    return 0;
}

char* my_realloc_str(char* str, int size) {
    char* out = malloc(size);
    my_strcpy(out, str);
    free(str);
    return out;
}

int copy_rest_of_previous_line(char* buf, char* line) {
    int i = 0;
    for (; buf[i] != '\0' && buf[i] != '\n'; i++)
        line[i] = buf[i];
    line[i] = '\0';
    return i;
}

int buf_to_line(char* buf, char* line, int line_index) {
    for (int i = 0; buf[i] != '\n' && buf[i] != '\0'; i++)
        line[line_index++] = buf[i];
    line[line_index] = '\0';
    return line_index;
}

void clear(char* buf) {
    for (int i = 0; buf[i]; i++)
        if (buf[i] == '\n')
        {
            int index = 0;
            while ( buf[i] != '\0' )
                buf[index++] = buf[++i];
            buf[index] = '\0';
            break;
        }
}

char* my_readline(int fd) {
    int line_index = 0;
    int line_max_size = READLINE_READ_SIZE + 1;
    char* line = malloc(sizeof(char) * line_max_size);
    static char buf[READLINE_READ_SIZE + 1];

    if (buf != 0 && buf[0] != '\0') //if buf has piece of previous line
        line_index += copy_rest_of_previous_line(buf, line);

    while ( !buf_has_new_line(buf) ) {
        int bytes_read = read(fd, buf, READLINE_READ_SIZE);
        buf[bytes_read] = '\0';
        if (bytes_read == 0 && line[0] > 0) {
            buf[0] = '\0';
            return line;
        }
        if (bytes_read < 0 || (bytes_read == 0 && line[0] <= 0)) {
            free(line);
            return 0;
        }
        if ( line_max_size <= line_index + bytes_read ) {
            line_max_size += READLINE_READ_SIZE;
            line = my_realloc_str(line, line_max_size);
        }
        line_index = buf_to_line(buf, line, line_index);
    }

    clear(buf);
    return line;
}