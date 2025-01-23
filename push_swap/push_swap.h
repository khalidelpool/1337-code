#ifndef PUSH_SWAP
# define PUSH_SWAP

# include <limits.h>
# include <ctype.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_stack
{
	int				number;
	int				rank;
	struct s_stack	*next;
}	stack;

// push_swap_list_utils.c not needed functions
void	f(int content);
int		ft_is_sorted(stack *head);
void	ft_iterlst(stack *lst, void (*f)(int));

// push_swap_list_utils.c
stack	*ft_newlst(int content);
int		ft_sizelst(stack *node);
void	ft_clearlst(stack **lst);
void	ft_add_backlst(stack **lst, stack *new);
int		ft_lstcompare(stack* lst, int to_compare);

// operations.c
void	ft_rot(stack **head);
void	ft_swap(stack **head);
void	ft_revrot(stack **head);
void	ft_push(stack **src, stack **dest);

// push_swap_input(1/2).c
long	ft_atoy(const char *nptr);
void	ft_bzero(void *s, size_t n);
stack	*parser(int i, int ac, char **av, stack *head);
char	*ft_substr(char const *s, unsigned int start, size_t len);

// push_swap_utils.c
int		min(int a, int b);
int		ft_index_max(stack *head, int choice);
void	ft_sort3(stack **head, int *last_move);
void	moves(int choice, int operation, int *last_move);
int		ft_target(int number, stack **head_B, int choice);
void	old_moves(int instruction, int *last_move, int new);

#endif