NAME = philo

SRCS_DIR = ./src

SRCS = $(SRCS_DIR)/main.c $(SRCS_DIR)/ft_atoi.c $(SRCS_DIR)/utils.c

OBJS = $(SRCS:.c=.o)

CC = gcc -g -pthread
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
