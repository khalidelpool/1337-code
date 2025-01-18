NAME = push_swap

source = push_swap.c push_swap_utils.c operations.c
object = $(source:.c=.o)

FLAGS = #-Wall -Wextra -Werror

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(object)
	gcc $(object) -L./libft -lft -o $(NAME)

clean: 
	rm -f $(object)

fclean: clean
	rm -f $(NAME)

re: fclean all

%.o:%.c
	cc $(FLAGS) -c $< -o $@ 