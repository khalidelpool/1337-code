CC := cc
FLAGS := -Wall -Wextra -Werror

MLX_FLAGS = -I/usr/include/minilibx-linux -L/usr/include/minilibx-linux -lmlx -lXext -lX11

NAME_1 = so_long
NAME_2 = so_long_bonus

PROJE_DIR = projects/
MANDA_DIR = mandatory/
BONUS_DIR = bonus/

PROJE_FILES = get_next_line.c get_next_line_utils.c libft_first.c libft_second.c
MANDA_FILES = so_long.c so_long_utils_primary.c so_long_utils_secondary.c so_long_utils_tertiary.c\
				so_long_utils_quaternary.c so_long_utils_quinary.c
BONUS_FILES = so_long_bonus.c  so_long_utils_primary_bonus.c  so_long_utils_quaternary_bonus.c\
				so_long_utils_secondary_bonus.c  so_long_utils_tertiary_bonus.c so_long_utils_quinary.c

source = $(addprefix $(MANDA_DIR), $(MANDA_FILES)) $(addprefix $(PROJE_DIR), $(PROJE_FILES))
object = $(source:.c=.o)

bonus_source = $(addprefix $(BONUS_DIR), $(BONUS_FILES)) $(addprefix $(PROJE_DIR), $(PROJE_FILES))
bonus_object = $(bonus_source:.c=.o)

all: $(NAME_1)

$(NAME_1): $(object)
	$(CC) $(object) $(MLX_FLAGS) -o $(NAME_1)

bonus: $(NAME_2)

$(NAME_2): $(bonus_object)
	$(CC) $(bonus_object) $(MLX_FLAGS) -o $(NAME_2)

clean: 
	rm -f $(object) $(bonus_object)

fclean: clean
	rm -f $(NAME_1) $(NAME_2)

re: fclean all

%.o:%.c
	$(CC) $(FLAGS) -c $< -o $@ 

.PHONY: all clean fclean re