CC = gcc
CFLAGS = -g3 -fsanitize=address -Wall -Werror -Wextra
INCLUDES = -I./
SRCS = my_bsq.c my_readline.c my_method.c
OBJS = $(SRCS:.c=.o)
MAIN = my_bsq
INPUT = 10 10 5

.PHONY: depend clean

all:    generate $(MAIN) clean_o
	@echo  Simple compiler named $(MAIN) has been compiled

generate: 
	perl generate.pl $(INPUT)

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) #$(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean_o:
	$(RM) *.o

clean:
	$(RM) *.o $(MAIN) input