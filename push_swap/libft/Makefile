NAME = libft.a

source = ft_itoa.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_atoi.c ft_strdup.c ft_strlen.c ft_putnbr_fd.c ft_bzero.c ft_split.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_strchr.c ft_strrchr.c ft_memset.c ft_calloc.c ft_memchr.c ft_strjoin.c ft_strtrim.c ft_memcpy.c ft_memcmp.c ft_memmove.c ft_strncmp.c ft_striteri.c ft_strlcpy.c ft_strlcat.c ft_strmapi.c ft_substr.c ft_strnstr.c
object = $(source:.c=.o)
bonus = ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstnew_bonus.c ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstiter_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstmap_bonus.c
object_bonus = $(bonus:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(object)
	ar rcs $(NAME) $(object)

bonus : $(object) $(object_bonus)
	touch bonus
	ar rcs $(NAME) $(object) $(object_bonus)

clean: 
	rm -f $(object) $(object_bonus)

fclean: clean
	rm -f $(NAME)

re: fclean all

%.o:%.c
	cc -Wall -Wextra -Werror -c $< -o $@ 