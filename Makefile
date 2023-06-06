NAME = philo

SRCS_DIR = ./src

SRCS = $(SRCS_DIR)/main.c $(SRCS_DIR)/initialize.c $(SRCS_DIR)/utils.c $(SRCS_DIR)/ft_atoi.c $(SRCS_DIR)/dining.c $(SRCS_DIR)/finish_dinner.c

OBJS = $(SRCS:.c=.o)

CC = gcc -pthread
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) 

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
