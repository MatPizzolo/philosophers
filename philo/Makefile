NAME = philo
NAME_DEBUG = philo_debug

SRCS_DIR = ./src

SRCS = $(SRCS_DIR)/main.c $(SRCS_DIR)/initialize.c $(SRCS_DIR)/utils.c $(SRCS_DIR)/ft_atoi.c $(SRCS_DIR)/dining.c $(SRCS_DIR)/finish_dinner.c

OBJS = $(SRCS:.c=.o)

CC = gcc -pthread
CFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=thread

all: $(NAME)

VS_debug: $(NAME_DEBUG)
$(NAME_DEBUG): $(SRCS)
	$(CC) $(CFLAGS) -fdiagnostics-color=always -g $(SRCS) -o $@

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
