NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g #-pthread -fsanitize=thread

SRCS = destructor.c init.c philo.c routine.c times.c utils.c
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