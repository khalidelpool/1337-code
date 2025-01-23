#include "push_swap.h"

// not needed
void f(int content)
{
	printf("content is: %d\n", content);
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
// end of not needed



int		ft_is_sorted(stack *head)
{
	int last;

	last = -2147483648;
	while (head != NULL)
	{
		if (last > head->number)
			return (0);
		last = head->number;
		head = head->next;
	}
	return (1);
}

int	ft_add_backlst(stack **lst, int content)
{
	stack	*last;
	stack *new;

	new = malloc(sizeof(stack));
	if (new == NULL)
		return (1);
	new->number = content;
	new->next = NULL;
	last = *lst;
	if (lst == NULL)
		return (0);
	if (*lst == NULL)
	{
		*lst = new;
		return (0);
	}
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = new;
	new->next = NULL;
	return (0);
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
		if (temp != NULL)
			free(temp);
	}
	*lst = NULL;
}
