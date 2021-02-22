#include "main.h"

int my_min(int num, ...)
{
    va_list ap;
    int i = 0;
    int min = 0;
    va_start(ap, num);
    if (num >= 1)
    {
        min = va_arg(ap, int);
        i++;
    }
    while (i < num)
    {
        int tmp = va_arg(ap, int);
        if (tmp < min)
        {
            min = tmp;
        }
        i++;
    }
    va_end(ap);
    return min;
}

int my_strlen(char* str)
{
    int i = 0;
    while (str[i])
    {
        i++;
    }
    return i;
}

int my_atoi(const char* str)
{
    int res = 0;
    int sign = 1;
    int i = 0;

    if (str[0] == '-')
    {
        sign = -1;
        i++;
    }

    for (; str[i] != '\0'; ++i)
    {
        res = res * 10 + str[i] - '0';
    }
 
    return sign * res;
}

void rows_count(t_map_char* input, t_map_int* output, int fd)
{
    char* first_line = my_readline(fd);
    input->y = my_atoi(first_line);
    output->y = input->y;
    free(first_line);
}

void rows_length(t_map_char* input, t_map_int* output)
{
    input->x = my_strlen(input->field[1]);
    output->x = input->x;
}

int main()
{
    t_map_char* input = malloc(sizeof(t_map_char));
    input->field = malloc(sizeof(char*) * 2);
    t_map_int* output = malloc(sizeof(t_map_int));
    output->field = malloc(sizeof(int*) * 2);
    t_pos* best = malloc(sizeof(t_pos));
    best->value = 0;
    best->y = 0;
    best->x = 0;

    int fd = open("input", O_RDONLY);

	rows_count(input, output, fd);

    for (int i = 0; i < input->y; i++)
    {
        if (i == 0)
        {
            input->field[1] = my_readline(fd);

            rows_length(input, output);

            input->field[0] = malloc(sizeof(int) * (input->x + 1));
            output->field[0] = malloc(sizeof(int) * (output->x + 1));
            output->field[1] = malloc(sizeof(int) * (output->x + 1));

            for (int j = 0; j < input->x; j++)
            {
                if (input->field[1][j] == '.')
                {
                    output->field[1][j] = 1;
                }
                else
                {
                    output->field[1][j] = 0;
                }

                if (output->field[1][j] > best->value)
                {
                    best->value = output->field[1][j];
                    best->y = i;
                    best->x = j;
                }
            }
        }
        else
        {
            free(input->field[0]);
            input->field[0] = input->field[1];
            free(output->field[0]);
            output->field[0] = output->field[1];

            input->field[1] = my_readline(fd);
            output->field[1] = malloc(sizeof(int) * (output->x + 1));

            for (int j = 0; j < input->x; j++)
            {
                if (j == 0)
                {
                    if (input->field[1][j] == '.')
                    {
                        output->field[1][j] = 1;
                    }
                    else
                    {
                        output->field[1][j] = 0;
                    }
                }
                else
                {
                    if (input->field[1][j] == '.')
                    {
                        output->field[1][j] = 1 + my_min(3, output->field[1][j - 1], output->field[0][j], output->field[0][j - 1]);
                    }
                    else
                    {
                        output->field[1][j] = 0;
                    }
                }

                if (output->field[1][j] > best->value)
                {
                    best->value = output->field[1][j];
                    best->y = i;
                    best->x = j;
                }
            }
        }
    }

    free(input->field[0]);
    free(input->field[1]);
    free(output->field[0]);
    free(output->field[1]);
    free(output->field);
    free(output);

    close(fd);

    fd = open("input", O_RDONLY);

    char* tmp = my_readline(fd);
    free(tmp);

    for (int i = 0; i < input->y; i++)
    {
        input->field[0] = my_readline(fd);
        for (int j = 0; j < input->x; j++)
        {
            if (i <= best->y && i > best->y - best->value)
            {
                if (j <= best->x && j > best->x - best->value)
                {
                    input->field[0][j] = 'x';
                }
            }
        }
        printf("%s\n", input->field[0]);
        free(input->field[0]);
    }

    close(fd);

    free(input->field);
    free(input);
    free(best);
}