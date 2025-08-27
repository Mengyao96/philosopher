NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -I.

SRCS_DIR = philo
SRCS := $(addprefix $(SRCS_DIR)/, \
	  main.c \
	)

OBJS = $(SRCS:.c=.o)


all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

debug:
	$(CC) -g -I. $(SRCS)

%.o: $(SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re
