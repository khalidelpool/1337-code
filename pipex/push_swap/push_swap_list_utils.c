/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_list_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:44:30 by kel-mous          #+#    #+#             */
/*   Updated: 2025/01/24 16:39:51 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

int	ft_is_sorted(t_stack *head)
{
	int	last;

	last = INT_MIN;
	while (head != NULL)
	{
		if (last > head->number)
			return (0);
		last = head->number;
		head = head->next;
	}
	return (1);
}

int	ft_add_backlst(t_stack **lst, int content)
{
	t_stack	*last;
	t_stack	*new;

	new = malloc(sizeof(t_stack));
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

int	ft_lstcompare(t_stack *lst, int to_compare)
{
	t_stack	*curr;

	curr = lst;
	while (curr != NULL)
	{
		if (curr->number == to_compare)
			return (1);
		curr = curr->next;
	}
	return (0);
}

int	ft_sizelst(t_stack *node)
{
	int	size;

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

void	ft_clearlst(t_stack **lst)
{
	t_stack	*curr;
	t_stack	*temp;

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
