NAME_1 = pipex
NAME_2 = pipex_bonus

source = pipex.c pipex_utils_first.c pipex_utils_second.c pipex_utils_third.c pipex_utils_forth.c\
			pipex_utils_fifth.c pipex_list.c
object = $(source:.c=.o)

bonus_source = pipex_bonus.c pipex_utils_first_bonus.c pipex_utils_second_bonus.c pipex_utils_third_bonus.c\
				pipex_utils_forth_bonus.c pipex_utils_fifth_bonus.c pipex_list_bonus.c get_next_line.c get_next_line_utils.c
bonus_object = $(bonus_source:.c=.o)

FLAGS = -Wall -Wextra -Werror

.PHONY: all clean fclean re

all: $(NAME_1)

$(NAME_1): $(object)
	cc $(object) -o $(NAME_1)

$(NAME_2): $(bonus_object)
	cc $(bonus_object) -o $(NAME_2)

bonus: $(NAME_2)

clean: 
	rm -f $(object) $(bonus_object)

fclean: clean
	rm -f $(NAME_1) $(NAME_2)

re: fclean all

%.o:%.c
	cc $(FLAGS) -c $< -o $@ 