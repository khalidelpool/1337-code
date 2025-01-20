#ifndef PUSH_SWAP
# define PUSH_SWAP

// # include "./libft/libft.h"
// # include "./libft/ft_split.c"
// # include "./libft/ft_strlen.c"
// # include "./libft/ft_strlen.c"
// # include "./libft/ft_substr.c"
// # include "./libft/ft_calloc.c"
# include <limits.h>
# include <ctype.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_stack
{
	int				number;
	struct s_stack	*next;
}	stack;

void	f(int content);
void	ft_rot(stack **head);
void	ft_swap(stack **head);
int		ft_sizelst(stack *node);
void	ft_revrot(stack **head);
char	**free_arr_ps(char ***ptr);
stack	*ft_newlst(int content);
void	ft_clearlst(stack **lst);
int		ft_is_sorted(stack *head);
long	ft_atoy(const char *nptr);
void	ft_push(stack **src, stack **dest);
void	ft_sort3(stack **head, int *last_move);
void	ft_iterlst(stack *lst, void (*f)(int));
void	ft_add_backlst(stack **lst, stack *new);
int		ft_lstcompare(stack* lst, int to_compare);
stack	*parser(int i, int ac, char **av, stack *head);
void	moves(int choice, int operation, int *last_move);
void	old_moves(int instruction, int *last_move, int new);

#endif