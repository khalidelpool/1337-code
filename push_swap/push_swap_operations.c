/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_operations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:54:15 by kel-mous          #+#    #+#             */
/*   Updated: 2025/01/24 16:00:17 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

void	ft_swap(t_stack **head)
{
	t_stack	*temp;

	if (!head || !(*head) || !((*head)->next))
		return ;
	temp = (*head)->next->next;
	(*head)->next->next = (*head);
	(*head) = (*head)->next;
	(*head)->next->next = temp;
}

void	ft_push(t_stack **src, t_stack **dest)
{
	t_stack	*temp;

	if (!src || !dest || !(*src))
		return ;
	temp = *dest;
	*dest = *src;
	*src = (*src)->next;
	(*dest)->next = temp;
}

void	ft_rot(t_stack **head)
{
	t_stack	*temp;
	t_stack	*curr;

	if (!head || !(*head) || !((*head)->next))
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

void	ft_revrot(t_stack **head)
{
	t_stack	*curr;

	if (!head || !(*head) || !((*head)->next))
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

void	ft_sort3(t_stack **head, int *last_move)
{
	int	index;
	int	size;

	size = ft_sizelst(*head);
	index = ft_index_max(*head, -1);
	if (index == 2)
	{
		if ((*head)->number > (*head)->next->number)
			(ft_swap(head), moves(0, 1, last_move));
		(ft_revrot(head), moves(0, 4, last_move));
	}
	else if (index == 1 && size == 3)
	{
		if ((*head)->number > (*head)->next->next->number)
			(ft_rot(head), moves(0, 3, last_move));
		else
			(ft_swap(head), moves(0, 1, last_move));
	}
	else if (index == 0 && size == 3
		&& (*head)->next->number > (*head)->next->next->number)
		(ft_revrot(head), ft_swap(head),
			moves(0, 4, last_move), moves(0, 1, last_move));
}
