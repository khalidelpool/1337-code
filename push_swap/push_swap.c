#include "push_swap.h"
# include "operations.c"
# include "push_swap_utils.c"

int ft_index_max(stack *head, int choice)
{
	int index;
	int max;
	int i;
	stack *curr;

	curr = head;
	index = 0;
	i = 0;
	max = -2147483648 + choice;
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

int ft_target(int number, stack **head_B, int choice)
{
	stack *curr;
	int target;
	int index;
	int i;
	
	i = 0;
	curr = *head_B;
	index = -1;
	target = -2147483648 + choice;
	while(curr != NULL)
	{
		if ((!choice && number > curr->number && curr->number >= target) || (choice && number < curr->number && curr->number <= target))
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

int min(int a, int b)
{
	if (a >= b)
		return (b);
	return (a);
}
int count = 0;
void ft_move_cheapest(stack **head_A, stack **head_B, int *lci, int *last_move)
{
	int size_A;
	int size_B;
	int choice;

	choice = lci[2];
	size_A = ft_sizelst(*head_A);
	size_B = ft_sizelst(*head_B);
	while (1)
	{
		// printf("i am in move cheapest while, with lci_a: %d, lci_b: %d\n", lci[0], lci[1]);
		// if(count == 4)
		// 	exit(0);
		// you should handle rr and rrr, see garbage.txt
		if (lci[0] <= size_A / 2 && lci[0])
			ft_rot(head_A), lci[0]--, moves(choice, 3, last_move);
		else if (lci[0] > size_A / 2 && lci[0] != size_A)
			ft_revrot(head_A), lci[0]++, moves(choice, 4, last_move);
		if (lci[1] <= size_B / 2 && lci[1])
			ft_rot(head_B), lci[1]--, moves(choice + 1, 3, last_move);
		else if (lci[1] > size_B / 2 && lci[1] != size_B)
			ft_revrot(head_B), lci[1]++, moves(choice + 1, 4, last_move);
		if ((!lci[0] || lci[0] == size_A) && (!lci[1] || lci[1] == size_B))
			break ;
		count++;
	}
	ft_push(head_A, head_B), moves(choice, 2, last_move);
}

int one_of_us(stack *head, int number)
{
	int biggest[3];

	biggest[0] = INT_MIN;
	biggest[1] = INT_MIN;
	biggest[2] = INT_MIN;
	while (head != NULL)
	{
		if (head->number > biggest[0] && biggest[0] <= biggest[1] && biggest[0] <= biggest[2])
			biggest[0] = head->number;
		else if (head->number > biggest[1] && biggest[1] <= biggest[0] && biggest[1] <= biggest[2])
			biggest[1] = head->number;
		else if (head->number > biggest[2] && biggest[2] <= biggest[0] && biggest[2] <= biggest[1])
			biggest[2] = head->number;
		head = head->next;
	}
	//printf("biggest 1 is: %d\nbiggest 2 is: %d\nbiggest 3 is: %d\n", biggest[0], biggest[1], biggest[2]);
	if (number == biggest[0] || number == biggest[1] || number == biggest[2])
		return (1);
	return (0);
}

void ft_cost(stack **head_A, stack **head_B, int choice, int *last_move)
{
	long temp_cost;
	long curr_cost;
	stack *curr;
	int temp;
	int i;
	int lci[3]; // least cost index
	int size_A;
	int size_B;
	int test = 0;

	curr = *head_A;
	i = 0;
	lci[2] = choice;
	size_A = ft_sizelst(*head_A);
	size_B = ft_sizelst(*head_B);
	while (curr != NULL)
	{
		// printf("i am in\n");
		// if (one_of_us(*head_A, curr->number) && !choice)
		// {
		// 	// printf("number is: %d\n", curr->number);
		// 	curr = curr->next;
		// 	i++;
		// 	continue;
		// }
		temp = ft_target(curr->number, head_B, choice);
		curr_cost = min(i, size_A - i) + min(temp, size_B - temp);
		if ((curr == *head_A || !test || curr_cost < temp_cost))
		{
			lci[0] = i;
			lci[1] = temp;
			temp_cost = curr_cost;
			test = 1;
		}
		curr = curr->next;
		i++;
	}
	// printf("i am out\n");
	ft_move_cheapest(head_A, head_B, lci, last_move);
}

int ranker(stack *head)
{
	int rank;
	int target;

	target = head->number;
	rank = 0;
	if (head->next != NULL)
		head = head->next;
	while(head != NULL)
	{
		if (head->number < target)
			rank++;
		head = head->next;
	}
	return (rank);
}

void choose_rank(stack **head_A, stack** head_B, int *last_move)
{
	int size;

	size = ft_sizelst(*head_A);
	while (!(ranker(*head_A) <= size / 2))
	{
		ft_rot(head_A), moves(0, 3, last_move);
	}
	ft_push(head_A, head_B);
	moves(0, 2, last_move);
}

int main(
	int ac, char **av
	)
{
	stack *head = NULL;
	stack *head_b = NULL; // very important, does problems with stuff like ft_sizelst
	int min;
	int size;
	int last_move;

	// int ac = 2;
	// char *av[] = {"./push_swap", "8 9 6 5"};

	if (ac < 2)
		return (0);
	head = parser(1, ac, av, (stack *)NULL);

	last_move = 0;
	
	// printf("the return is: %d\n", ranker(head));
	// exit(0);

	// // // pushing 2 elements to B to start the algo
	// while (ft_sizelst(head) > 3 && ft_sizelst(head_b) < 2)
	// 	ft_push(&head, &head_b), moves(0, 2, &last_move);

	// printf("the return is: %d\n", one_of_us(head, 0));
	// exit(0);

	// moving least cost element in each iteration
	while (ft_sizelst(head) > 3)
		// ft_cost(&head, &head_b, 0, &last_move); // 5162
		choose_rank(&head, &head_b, &last_move); // 4824
		//, ft_cost(&head, &head_b, 0, &last_move)
	
	// ARG=""; ./a.out $ARG

	// ft_iterlst(head, f);
	// printf("------------------------------------\n");
	// ft_iterlst(head_b, f);
	// exit(0);
	
	ft_sort3(&head, &last_move);

	// moving least cost element in each iteration
	while (ft_sizelst(head_b))
		ft_cost(&head_b, &head, -1, &last_move);

	// making sure the smallest number is at the top
	min = ft_index_max(head, -1);
	size = ft_sizelst(head);
	while (1)
	{
		if (min && min <= size / 2)
			ft_rot(&head), min--, moves(0, 3, &last_move);
		else if (min != size && min > size / 2)
			ft_revrot(&head), min++, moves(0, 4, &last_move);
		else 
			break;
	}

	// printing a move that gets left in last_move variable
	old_moves(last_move, &last_move, 0);

	// printing the 2 stacks
	// ft_iterlst(head, f);
	// printf("------------------------------------\n");
	// ft_iterlst(head_b, f);
	
	ft_clearlst(&head);
	ft_clearlst(&head_b);
}
