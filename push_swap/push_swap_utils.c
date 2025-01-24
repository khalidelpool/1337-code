/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:01:26 by kel-mous          #+#    #+#             */
/*   Updated: 2025/01/24 16:04:16 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

int	ft_index_max(t_stack *head, int choice)
{
	int		index;
	int		max;
	int		i;
	t_stack	*curr;

	curr = head;
	index = 0;
	i = 0;
	max = INT_MIN + choice;
	while (curr != NULL)
	{
		if ((!choice && max <= curr->number) || (choice && max >= curr->number))
		{
			max = curr->number;
			index = i;
		}
		curr = curr->next;
		i++;
	}
	return (index);
}

int	ft_target(int number, t_stack **head_B, int choice)
{
	t_stack	*curr;
	int		target;
	int		index;
	int		i;

	i = 0;
	curr = *head_B;
	index = -1;
	target = INT_MIN + choice;
	while (curr != NULL)
	{
		if ((!choice && number > curr->number && curr->number >= target)
			|| (choice && number < curr->number && curr->number <= target))
		{
			target = curr->number;
			index = i;
		}
		curr = curr->next;
		i++;
	}
	if (index == -1)
		index = ft_index_max(*head_B, choice);
	return (index);
}

int	min(int a, int b)
{
	if (a >= b)
		return (b);
	return (a);
}

void	old_moves(int instruction, int *last_move, int new)
{
	if (instruction == 1)
		write(1, "sa\n", 3);
	else if (instruction == 2)
		write(1, "sb\n", 3);
	else if (instruction == 3)
		write(1, "pb\n", 3);
	else if (instruction == 4)
		write(1, "pa\n", 3);
	else if (instruction == 5)
		write(1, "ra\n", 3);
	else if (instruction == 6)
		write(1, "rb\n", 3);
	else if (instruction == 7)
		write(1, "rra\n", 4);
	else if (instruction == 8)
		write(1, "rrb\n", 4);
	*last_move = new;
}

void	moves(int choice, int operation, int *last_move)
{
	if (!choice && operation == 3 && *last_move == 6)
		(write(1, "rr\n", 3), old_moves(0, last_move, 0));
	else if (choice && operation == 3 && *last_move == 5)
		(write(1, "rr\n", 3), old_moves(0, last_move, 0));
	else if (!choice && operation == 4 && *last_move == 8)
		(write(1, "rrr\n", 4), old_moves(0, last_move, 0));
	else if (choice && operation == 4 && *last_move == 7)
		(write(1, "rrr\n", 4), old_moves(0, last_move, 0));
	else if (!choice && operation == 1)
		old_moves(*last_move, last_move, 1);
	else if (choice && operation == 1)
		old_moves(*last_move, last_move, 2);
	else if (!choice && operation == 2)
		old_moves(*last_move, last_move, 3);
	else if (choice && operation == 2)
		old_moves(*last_move, last_move, 4);
	else if (!choice && operation == 3)
		old_moves(*last_move, last_move, 5);
	else if (choice && operation == 3)
		old_moves(*last_move, last_move, 6);
	else if (!choice && operation == 4)
		old_moves(*last_move, last_move, 7);
	else if (choice && operation == 4)
		old_moves(*last_move, last_move, 8);
}
