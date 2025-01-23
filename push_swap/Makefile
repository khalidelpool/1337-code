NAME = push_swap
BONUS_NAME = checker


shared_files = push_swap_utils.c push_swap_operations.c push_swap_list_utils.c push_swap_input_first.c push_swap_input_second.c
source = push_swap.c $(shared_files)
object = $(source:.c=.o)

bonus_source = checker.c $(shared_files) get_next_line.c get_next_line_utils.c
bonus_object = $(bonus_source:.c=.o)

libft = -L./libft -lft

FLAGS = #-Wall -Wextra -Werror

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(object)
	gcc $(object) -o $(NAME)

bonus: $(bonus_object)
	touch bonus
	gcc $(bonus_object) -o $(BONUS_NAME)

clean: 
	rm -f $(object) $(bonus_object)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME) bonus

re: fclean all

%.o:%.c
	cc $(FLAGS) -c $< -o $@ 