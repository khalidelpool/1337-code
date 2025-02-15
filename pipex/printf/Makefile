
NAME = libftprintf.a

RESOURCE = 	ft_format.c ft_precision.c ft_flags.c ft_unsigned_itoa.c ft_printmemory.c \
      		ft_strdup.c ft_hexa.c ft_putstr.c ft_itoa.c ft_memmove.c ft_memcpy.c ft_null.c\
      		ft_memset.c ft_init_flags.c ft_putchar.c ft_width.c ft_struct.c ft_printf.c ft_in_set.c\
      		ft_overflow.c ft_order.c ft_isdigit.c ft_atoi.c ft_strlen.c ft_append.c ft_char.c ft_calloc.c\

OBJECTS = $(RESOURCE:.c=.o)

FLAGS = -Wall -Werror -Wextra

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJECTS)
	ar rcs $(NAME) $(OBJECTS)

bonus: all

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all 

%.o: %.c
	cc $(FLAGS) -c $< -o $@