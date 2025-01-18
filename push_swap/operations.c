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