#include "push_swap.h"

void ft_swap(stack **head)
{
	stack *temp;

	if (!head || !(*head) || !((*head)->next)) // at least 2 nodes
		return ;
	temp = (*head)->next->next;
	(*head)->next->next = (*head);
	(*head) = (*head)->next;
	(*head)->next->next = temp;
}

void ft_push(stack **src, stack **dest)
{
	stack *temp;
	if (!src || !dest || !(*src))
		return ;
	temp = *dest;
	*dest = *src;
	*src = (*src)->next;
	(*dest)->next = temp;
}

void ft_rot(stack **head)
{
	stack *temp;
	stack *curr;

	if (!head || !(*head) || !((*head)->next)) // at least 2 nodes
		return ;
	temp = *head;
	*head = (*head)->next;
	temp->next = NULL;
	curr = *head;
	while (curr->next != NULL)
	{
		curr = curr->next;
	}
	curr->next = temp;
}

void ft_revrot(stack **head)
{
	stack *curr;

	if (!head || !(*head) || !((*head)->next)) // at least 2 nodes
		return ;
	curr = *head;
	while (curr->next->next != NULL)
	{
		curr = curr->next;
	}
	curr->next->next = *head;
	*head = curr->next;
	curr->next = NULL;
}

void ft_sort3(stack **head, int *last_move)
{
	int index;
	int size;

	size = ft_sizelst(*head);
	index = ft_index_max(*head, -1); // -1 meaning index of the smallest
	if (index == 2)
	{
		if ((*head)->number > (*head)->next->number)
			ft_swap(head), moves(0, 1, last_move);
		ft_revrot(head), moves(0, 4, last_move);
	}
	else if (index == 1 && size == 3)
	{
		if ((*head)->number > (*head)->next->next->number)
			ft_rot(head), moves(0, 3, last_move);
		else
			ft_swap(head), moves(0, 1, last_move);
	}
	else if(index == 0 && size == 3 && (*head)->next->number > (*head)->next->next->number)
		ft_revrot(head), ft_swap(head), moves(0, 4, last_move), moves(0, 1, last_move);
}
