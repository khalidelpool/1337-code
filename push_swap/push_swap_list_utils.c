#include "push_swap.h"

// not needed
void f(int content)
{
	printf("content is: %d\n", content);
}

int ft_is_sorted(stack *head)
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
