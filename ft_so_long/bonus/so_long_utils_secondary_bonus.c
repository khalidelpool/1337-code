/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils_secondary_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 21:05:11 by kel-mous          #+#    #+#             */
/*   Updated: 2025/03/17 21:05:15 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long_bonus.h"

int	ocurrence(t_vars *var, char c)
{
	int	y;
	int	x;
	int	result;

	y = 0;
	result = 0;
	while (var->map[y])
	{
		x = 0;
		while (var->map[y][x])
		{
			if (var->map[y][x] == c)
				result++;
			x++;
		}
		y++;
	}
	return (result);
}

int	*find_c(t_vars *var, char c, int *pos)
{
	int	y;
	int	x;

	y = 0;
	while (var->map[y])
	{
		x = 0;
		while (var->map[y][x])
		{
			if (var->map[y][x] == c)
			{
				if (pos != NULL)
				{
					pos[0] = x;
					pos[1] = y;
					return (pos);
				}
				return (var->pos);
			}
			x++;
		}
		y++;
	}
	return (NULL);
}

int	in_list(t_queue *queue, int *pos)
{
	while (queue)
	{
		if (queue->pos[0] == pos[0] && queue->pos[1] == pos[1])
			return (1);
		queue = queue->next;
	}
	return (0);
}

void	next_to(t_vars *var, t_queue *node, int bros[5][2])
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	j = 0;
	while (i < 4)
	{
		x = node->pos[0] + get_next_move(i, 0);
		y = node->pos[1] + get_next_move(i, 1);
		if (x < var->hgt && y < var->wdt && x > -1 && y > -1)
		{
			if (var->map[y][x] != '1' && var->map[y][x] != 'V')
			{
				bros[j][0] = x;
				bros[j][1] = y;
				j++;
			}
		}
		i++;
	}
	bros[j][0] = -1;
	free(node);
}

int	ate_all(t_vars *var)
{
	int	pos[2];

	pos[1] = 0;
	while (var->map[pos[1]])
	{
		pos[0] = 0;
		while (var->map[pos[1]][pos[0]])
		{
			if ((var->map[pos[1]][pos[0]] == 'C'
				|| var->map[pos[1]][pos[0]] == 'E')
					&& !in_list(var->visited, pos))
			{
				return (0);
			}
			pos[0]++;
		}
		pos[1]++;
	}
	return (1);
}
