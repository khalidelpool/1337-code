/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:05:29 by kel-mous          #+#    #+#             */
/*   Updated: 2025/01/24 16:35:34 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

void	mv_cheap(t_stack **head_a, t_stack **head_b, int *lci, int *last_move)
{
	int	size_a;
	int	size_b;
	int	lci_a;
	int	lci_b;
	int	choice;

	lci_a = lci[0];
	lci_b = lci[1];
	choice = lci[2];
	size_a = ft_sizelst(*head_a);
	size_b = ft_sizelst(*head_b);
	while (1)
	{
		if (lci_a <= size_a / 2 && lci_a)
			(ft_rot(head_a), lci_a--, moves(choice, 3, last_move));
		else if (lci_a > size_a / 2 && lci_a != size_a)
			(ft_revrot(head_a), lci_a++, moves(choice, 4, last_move));
		if (lci_b <= size_b / 2 && lci_b)
			(ft_rot(head_b), lci_b--, moves(choice + 1, 3, last_move));
		else if (lci_b > size_b / 2 && lci_b != size_b)
			(ft_revrot(head_b), lci_b++, moves(choice + 1, 4, last_move));
		if ((!lci_a || lci_a == size_a) && (!lci_b || lci_b == size_b))
			break ;
	}
	(ft_push(head_a, head_b), moves(choice, 2, last_move));
}

void	ft_cost(t_stack **head_a, t_stack **head_b, int choice, int *last_move)
{
	long	temp_cost;
	long	curr_cost;
	t_stack	*curr;
	int		tab[4];
	int		lci[3];

	curr = *head_a;
	lci[2] = choice;
	tab[0] = ft_sizelst(*head_a);
	tab[1] = ft_sizelst(*head_b);
	tab[2] = 0;
	while (curr != NULL)
	{
		tab[3] = ft_target(curr->number, head_b, choice);
		curr_cost = min(tab[2], tab[0] - tab[2]) + min(tab[3], tab[1] - tab[3]);
		if ((curr == *head_a || curr_cost < temp_cost))
		{
			lci[0] = tab[2];
			lci[1] = tab[3];
			temp_cost = curr_cost;
		}
		curr = curr->next;
		tab[2]++;
	}
	mv_cheap(head_a, head_b, lci, last_move);
}

void	choose_rank(t_stack **head_a, t_stack **head_b, int *last_move)
{
	int		size;
	int		rank;
	int		target;
	t_stack	*curr;

	size = ft_sizelst(*head_a);
	while (1)
	{
		if ((*head_a)->next != NULL)
			curr = (*head_a)->next;
		target = (*head_a)->number;
		rank = 0;
		while (curr != NULL)
		{
			if (curr->number < target)
				rank++;
			curr = curr->next;
		}
		if (rank <= size / 2)
			break ;
		(ft_rot(head_a), moves(0, 3, last_move));
	}
	ft_push(head_a, head_b);
	moves(0, 2, last_move);
}

void	clearup(t_stack **head, int *last_move)
{
	int	min;
	int	size;

	min = ft_index_max(*head, -1);
	size = ft_sizelst(*head);
	while (1)
	{
		if (min && min <= size / 2)
			(ft_rot(head), min--, moves(0, 3, last_move));
		else if (min != size && min > size / 2)
			(ft_revrot(head), min++, moves(0, 4, last_move));
		else
			break ;
	}
	old_moves(*last_move, last_move, 0);
}

int	main(int ac, char **av)
{
	t_stack	*head_a;
	t_stack	*head_b;
	int		last_move;

	if (ac < 2)
		return (0);
	head_a = NULL;
	head_b = NULL;
	last_move = 0;
	head_a = parser(1, ac, av, (t_stack *) NULL);
	if (ft_is_sorted(head_a))
	{
		ft_clearlst(&head_a);
		ft_clearlst(&head_b);
		return (0);
	}
	while (ft_sizelst(head_a) > 3)
		choose_rank(&head_a, &head_b, &last_move);
	ft_sort3(&head_a, &last_move);
	while (ft_sizelst(head_b))
		ft_cost(&head_b, &head_a, -1, &last_move);
	clearup(&head_a, &last_move);
	ft_clearlst(&head_a);
	ft_clearlst(&head_b);
}
