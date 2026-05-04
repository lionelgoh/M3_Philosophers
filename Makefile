# Author: Lionel Goh

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude

SRCDIR = ./src
SRCS = $(SRCDIR)/main.c\
		$(SRCDIR)/parse.c\
		$(SRCDIR)/init.c\
		$(SRCDIR)/time.c\
		$(SRCDIR)/state.c\
		$(SRCDIR)/threads.c\
		$(SRCDIR)/routine.c\
		$(SRCDIR)/monitor.c\
		$(SRCDIR)/clean.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re