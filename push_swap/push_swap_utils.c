#include "push_swap.h"

void f(int content)
{
	printf("content is: %d\n", content);
}

char	**free_arr(char ***ptr)
{
	int i;

	i = 0;
	while ((*ptr)[i] != NULL)
		free((*ptr)[i++]);
	free(*ptr);
	return ((0));
}

long	ft_atoy(const char *nptr)
{
	long	result;
	int	sign;

	result = 0;
	sign = 1;
	while ((*nptr > 8 && *nptr < 14) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	else if (!ft_isdigit(*nptr))
		return (2147483648);
	while (ft_isdigit(*nptr))
	{
		result = result * 10 + *nptr - 48;
		if (result < -2147483648 || result > 2147483647)
			return (2147483648);
		nptr++;
	}
	if (!((*nptr > 8 && *nptr < 14) || *nptr == 32 || *nptr == 0))
		return (2147483648);
	return (((result * sign)));
}

stack	*ft_newlst(int content)
{
	stack	*node;

	node = malloc(sizeof(stack));
	if (node == NULL)
		return ((NULL));
	node->number = content;
	node->next = NULL;
	return ((node));
}

void ft_clearlst(stack **lst)
{
	stack	*curr;
	stack	*temp;

	if (!lst)
		return ;
	curr = *lst;
	while (curr != NULL)
	{
		temp = curr;
		curr = curr->next;
		free(temp);
	}
	*lst = NULL;
}

void	ft_iterlst(stack *lst, void (*f)(int))
{
	stack	*curr;

	if (!f)
		return ;
	curr = lst;
	while (curr != NULL)
	{
		f(curr->number);
		curr = curr->next;
	}
}

void	ft_add_backlst(stack **lst, stack *new)
{
	stack	*last;

	last = *lst;
	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = new;
	new->next = NULL;
}

int ft_lstcompare(stack *lst, int to_compare)
{
	stack	*curr;

	curr = lst;
	while (curr != NULL)
	{
		if (curr->number == to_compare)
			return (1);
		curr = curr->next;
	}
	return (0);
}

int ft_sizelst(stack *node)
{
	int size;
	if (!node)
		return (0);
	size = 0;
	while (node)
	{
		node = node->next;
		size++;
	}
	return (size);
}

void ft_sort3(stack **head)
{
	int smallest;
	int index;
	int i;
	stack *curr;

	index = 0;
	i = 0;
	smallest = 2147483647;
	curr = *head;
	while (curr != NULL)
	{
		if (curr->number < smallest)
		{
			smallest = curr->number;
			index = i;
		}
		curr = curr->next;
		i++;
	}
	if (index == 2)
	{
		if ((*head)->number > (*head)->next->number)
			ft_swap(head), moves(0, 1);
		ft_revrot(head), moves(0, 4);
	}
	else if (index == 1)
	{
		if ((*head)->number > (*head)->next->next->number)
			ft_rot(head), moves(0, 3);
		else
			ft_swap(head), moves(0, 1);
	}
	else if(index == 0 && (*head)->next->number > (*head)->next->next->number)
		ft_revrot(head), ft_swap(head), moves(0, 4), moves(0, 1);
}
