#ifndef PUSH_SWAP
# define PUSH_SWAP

#include "./libft/libft.h"

typedef struct s_stack
{
	int				number;
	struct s_stack	*next;
}	stack;

void f(int content);
long	ft_atoy(const char *nptr);
char	**free_arr(char ***ptr);
int ft_lstcompare(stack* lst, int to_compare);
stack	*ft_newlst(int content);
void ft_clearlst(stack **lst);
void	ft_iterlst(stack *lst, void (*f)(int));
void	ft_add_backlst(stack **lst, stack *new);
stack *parser(int i, int ac, char **av, stack *head);
void ft_swap(stack **head);
void ft_push(stack **src, stack **dest);
void ft_rot(stack **head);
void ft_revrot(stack **head);
int ft_sizelst(stack *node);
void ft_sort3(stack **head);
void moves(int choice, int operation);

#endif