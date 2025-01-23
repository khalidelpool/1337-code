#include "push_swap.h"

void ft_move_cheapest(stack **head_A, stack **head_B, int *lci, int *last_move)
{
	int size_A;
	int size_B;
	int lci_a;
	int lci_b;
	int choice;

	lci_a = lci[0];
	lci_b = lci[1];
	choice = lci[2];
	size_A = ft_sizelst(*head_A);
	size_B = ft_sizelst(*head_B);
	while (1)
	{
		if (lci_a <= size_A / 2 && lci_a)
			ft_rot(head_A), lci_a--, moves(choice, 3, last_move);
		else if (lci_a > size_A / 2 && lci_a != size_A)
			ft_revrot(head_A), lci_a++, moves(choice, 4, last_move);
		if (lci_b <= size_B / 2 && lci_b)
			ft_rot(head_B), lci_b--, moves(choice + 1, 3, last_move);
		else if (lci_b > size_B / 2 && lci_b != size_B)
			ft_revrot(head_B), lci_b++, moves(choice + 1, 4, last_move);
		if ((!lci_a || lci_a == size_A) && (!lci_b || lci_b == size_B))
			break ;
	}
	ft_push(head_A, head_B), moves(choice, 2, last_move);
}

void ft_cost(stack **head_A, stack **head_B, int choice, int *last_move)
{
	long temp_cost;
	long curr_cost;
	stack *curr;
	int tab[4];
	int lci[3]; // least cost index

	curr = *head_A;
	lci[2] = choice;
	tab[0] = ft_sizelst(*head_A); // size_A
	tab[1] = ft_sizelst(*head_B); // size_B
	tab[2] = 0; // i
	while (curr != NULL) // tab[3] = temp
	{
		tab[3] = ft_target(curr->number, head_B, choice);
		curr_cost = min(tab[2], tab[0] - tab[2]) + min(tab[3], tab[1] - tab[3]);
		if ((curr == *head_A || curr_cost < temp_cost))
		{
			lci[0] = tab[2];
			lci[1] = tab[3];
			temp_cost = curr_cost;
		}
		curr = curr->next;
		tab[2]++;
	}
	ft_move_cheapest(head_A, head_B, lci, last_move);
}

void choose_rank(stack **head_A, stack** head_B, int *last_move)
{
	int size;
	int rank;
	int target;
	stack *curr;

	size = ft_sizelst(*head_A);
	while (1)
	{
		if ((*head_A)->next != NULL)
			curr = (*head_A)->next;
		target = (*head_A)->number;
		rank = 0;
		while (curr != NULL)
		{
			if (curr->number < target)
				rank++;
			curr = curr->next;
		}
		if (rank <= size / 2)
			break ;
		ft_rot(head_A), moves(0, 3, last_move);
	}
	ft_push(head_A, head_B);
	moves(0, 2, last_move);
}

void clearup(stack **head, int *last_move)
{
	int min;
	int size;
	
	// making sure the smallest number is at the top
	min = ft_index_max(*head, -1);
	size = ft_sizelst(*head);
	while (1)
	{
		if (min && min <= size / 2)
			ft_rot(head), min--, moves(0, 3, last_move);
		else if (min != size && min > size / 2)
			ft_revrot(head), min++, moves(0, 4, last_move);
		else 
			break;
	}
	// printing a move that gets left in last_move variable
	old_moves(*last_move, last_move, 0);
}

int main(int ac, char **av)
{
	stack *head_A;
	stack *head_B; // very important, does problems with stuff like ft_sizelst
	int last_move;

	if (ac < 2)
		return (0);
	head_A = NULL;
	head_B = NULL;
	last_move = 0;
	head_A = parser(1, ac, av, (stack *)NULL);
	if (ft_is_sorted(head_A))
	{
		ft_clearlst(&head_A);
		ft_clearlst(&head_B);
		return (0);
	}
	while (ft_sizelst(head_A) > 3)
		choose_rank(&head_A, &head_B, &last_move);
	ft_sort3(&head_A, &last_move);
	while (ft_sizelst(head_B))
		ft_cost(&head_B, &head_A, -1, &last_move);
	clearup(&head_A, &last_move);
	ft_clearlst(&head_A);
	ft_clearlst(&head_B);
}
