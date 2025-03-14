NAME_1 = so_long
NAME_2 = so_long_bonus

source = so_long.c
object = $(source:.c=.o)

bonus_source = so_long_bonus.c
bonus_object = $(bonus_source:.c=.o)

MLX_FLAGS = -I./minilibx-linux -L./minilibx-linux -lmlx -lXext -lX11

FLAGS = -Wall -Wextra -Werror

.PHONY: all clean fclean re

all: $(NAME_1)

$(NAME_1): $(object)
	cc $(object) $(MLX_FLAGS) -o $(NAME_1)

bonus: $(NAME_2)

$(NAME_2): $(bonus_object)
	cc $(bonus_object) $(MLX_FLAGS) -o $(NAME_2)

clean: 
	rm -f $(object) $(bonus_object)

fclean: clean
	rm -f $(NAME_1) $(NAME_2)

re: fclean all

%.o:%.c
	cc $(FLAGS) -c $< -o $@ 