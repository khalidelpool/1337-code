#include "push_swap.h"

int checker_moves(char *move, stack **head_A, stack **head_B)
{
	if (!ft_strncmp(move, "sa\n", 4))
		ft_swap(head_A);
	else if (!ft_strncmp(move, "sb\n", 4))
		ft_swap(head_B);
	else if (!ft_strncmp(move, "pb\n", 4))
		ft_push(head_A, head_B);
	else if (!ft_strncmp(move, "pa\n", 4))
		ft_push(head_B, head_A);
	else if (!ft_strncmp(move, "ra\n", 4))
		ft_rot(head_A);
	else if (!ft_strncmp(move, "rb\n", 4))
		ft_rot(head_B);
    else if (!ft_strncmp(move, "rr\n", 4))
        ft_rot(head_A), ft_rot(head_B);
	else if (!ft_strncmp(move, "rra\n", 5))
		ft_revrot(head_A);
	else if (!ft_strncmp(move, "rrb\n", 5))
		ft_revrot(head_B);
    else if (!ft_strncmp(move, "rrr\n", 5))
        ft_revrot(head_A), ft_revrot(head_B);
    else
        return (1);
    return (0);
    // make sure to handle pb that gets run before stack gets a chance to be filled
}

int main(int ac, char **av)
{
	stack *head;
	stack *head_b = NULL;
    char *moves;

	if (ac < 2)
		return (0);
	head = parser(1, ac, av, (stack *)NULL);
    moves = get_next_line(0);
    while (moves != NULL)
    {
        if (checker_moves(moves, &head, &head_b))
        {
            write(1, "KO\n", 3);
            ft_clearlst(&head);
	        ft_clearlst(&head_b);
            return (1);
        }
        free(moves);
        moves = get_next_line(0);
    }
    if (ft_is_sorted(head))
    {
        ft_clearlst(&head);
	    ft_clearlst(&head_b);
        write(1, "OK\n", 3);
        return (0);
    }
    write(1, "KO\n", 3);
    ft_clearlst(&head);
	ft_clearlst(&head_b);
    return (1);
}
