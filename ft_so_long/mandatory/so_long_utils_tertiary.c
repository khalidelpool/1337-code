/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils_tertiary.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:50:18 by kel-mous          #+#    #+#             */
/*   Updated: 2025/03/17 10:50:20 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

t_queue	*pop(t_queue **queue)
{
	t_queue	*node;

	if (queue == NULL || (*queue) == NULL)
		return (NULL);
	node = *queue;
	*queue = node->next;
	return (node);
}

int	put(t_queue **queue, int x, int y)
{
	t_queue	*last;
	t_queue	*new;

	if (queue == NULL)
		return (0);
	new = malloc(sizeof(t_queue));
	if (new == NULL)
		return (1);
	new->pos[0] = x;
	new->pos[1] = y;
	new->next = NULL;
	last = *queue;
	if (*queue == NULL)
	{
		*queue = new;
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

void	print_moves(t_vars *var)
{
	char	*str_move_count;

	str_move_count = ft_strjoin_px("moves: ", ft_itoa(var->count), 2);
	if (str_move_count == NULL)
		(ft_putstr(MLC_ERR), quit(var), exit(0));
	ft_putstr(str_move_count);
	ft_putstr("\n");
	free(str_move_count);
}

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}
