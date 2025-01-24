/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:36:58 by kel-mous          #+#    #+#             */
/*   Updated: 2025/01/24 15:42:04 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "get_next_line.h"
# include <limits.h>
# include <stdio.h>
# define MAX 2147483648

typedef struct s_stack
{
	int				number;
	struct s_stack	*next;
}	t_stack;

// // push_swap_list_utils.c not needed functions
// void	f(int content);
// void	ft_iterlst(t_stack *lst, void (*f)(int));

// push_swap_list_utils.c
int		ft_sizelst(t_stack *node);
void	ft_clearlst(t_stack **lst);
int		ft_is_sorted(t_stack *head);
int		ft_add_backlst(t_stack **lst, int content);
int		ft_lstcompare(t_stack *lst, int to_compare);

// operations.c
void	ft_rot(t_stack **head);
void	ft_swap(t_stack **head);
void	ft_revrot(t_stack **head);
void	ft_push(t_stack **src, t_stack **dest);

// push_swap_input(1/2).c
void	ft_bzero(void *s, size_t n);
t_stack	*parser(int i, int ac, char **av, t_stack *head);
long	ft_atoy(const char *nptr, long result, int sign);
char	*ft_substr(char const *s, unsigned int start, size_t len);

// push_swap_utils.c
int		min(int a, int b);
int		ft_index_max(t_stack *head, int choice);
void	ft_sort3(t_stack **head, int *last_move);
void	moves(int choice, int operation, int *last_move);
int		ft_target(int number, t_stack **head_B, int choice);
void	old_moves(int instruction, int *last_move, int new);

#endif
