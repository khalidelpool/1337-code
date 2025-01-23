NAME = push_swap
BONUS_NAME = checker

source = push_swap.c push_swap_utils.c push_swap_operations.c push_swap_list_utils.c push_swap_input_first.c push_swap_input_second.c
object = $(source:.c=.o)

bonus_source = checker.c push_swap_utils.c push_swap_operations.c
bonus_object = $(bonus_source:.c=.o)

libft = -L./libft -lft

FLAGS = #-Wall -Wextra -Werror

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(object)
	gcc $(object) -o $(NAME)

bonus: $(bonus_object)
	gcc $(bonus_object) -o $(BONUS_NAME)

clean: 
	rm -f $(object)

fclean: clean
	rm -f $(NAME)

re: fclean all

%.o:%.c
	cc $(FLAGS) -c $< -o $@ 