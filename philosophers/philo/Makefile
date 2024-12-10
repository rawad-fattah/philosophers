NAME		:= philo
CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror
SRC := 		main.c \
			clear_data.c \
			helpers.c \
			philosopher_actions.c \
			philosopher_many.c \
			philosopher_one.c \

OBJS		:= $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all


.PHONY: all clean fclean re