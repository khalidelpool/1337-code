/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:55:44 by kel-mous          #+#    #+#             */
/*   Updated: 2025/01/24 15:35:20 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i] || (s1[i] == 0 && s2[i] == 0))
			return (((unsigned char)s1[i] - (unsigned char)s2[i]));
		i++;
	}
	return ((0));
}

int	checker_moves(char *move, t_stack **head_a, t_stack **head_b)
{
	if (!ft_strncmp(move, "sa\n", 4))
		ft_swap(head_a);
	else if (!ft_strncmp(move, "sb\n", 4))
		ft_swap(head_b);
	else if (!ft_strncmp(move, "pb\n", 4))
		ft_push(head_a, head_b);
	else if (!ft_strncmp(move, "pa\n", 4))
		ft_push(head_b, head_a);
	else if (!ft_strncmp(move, "ra\n", 4))
		ft_rot(head_a);
	else if (!ft_strncmp(move, "rb\n", 4))
		ft_rot(head_b);
	else if (!ft_strncmp(move, "rr\n", 4))
		(ft_rot(head_a), ft_rot(head_b));
	else if (!ft_strncmp(move, "rra\n", 5))
		ft_revrot(head_a);
	else if (!ft_strncmp(move, "rrb\n", 5))
		ft_revrot(head_b);
	else if (!ft_strncmp(move, "rrr\n", 5))
		(ft_revrot(head_a), ft_revrot(head_b));
	else
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_stack	*head_a;
	t_stack	*head_b;
	char	*moves;

	if (ac < 2)
		return (0);
	head_a = NULL;
	head_b = NULL;
	head_a = parser(1, ac, av, (t_stack *) NULL);
	moves = get_next_line(0);
	while (moves != NULL && !checker_moves(moves, &head_a, &head_b))
	{
		free(moves);
		moves = get_next_line(0);
	}
	if (ft_is_sorted(head_a) && !ft_sizelst(head_b)
		&& (ft_clearlst(&head_a), ft_clearlst(&head_b), 1))
	{
		write(1, "OK\n", 3);
		return (0);
	}
	write(1, "KO\n", 3);
	return (0);
}
