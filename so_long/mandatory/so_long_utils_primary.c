/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils_primary.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 18:08:17 by kel-mous          #+#    #+#             */
/*   Updated: 2025/03/15 18:08:20 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

void	check_map(t_vars *var)
{
	int	x;
	int	y;

	y = 0;
	while (var->map[y])
	{
		x = 0;
		while (var->map[y][x])
		{
			if (((y == 0 || x == 0 || y == var->wdt - 1 || x == var->hgt - 1)
					&& var->map[y][x] != '1')
					|| !in_set(var->map[y][x], "01CPE"))
				(ft_putstr(MAP_ERR), quit(var), exit(0));
			x++;
		}
		y++;
	}
	if (ocurrence(var, 'P') > 1 || ocurrence(var, 'E') > 1
		|| !find_c(var, 'C', NULL) || !find_c(var, 'E', NULL)
		|| !find_c(var, 'P', var->pos))
		(ft_putstr(MAP_ERR), quit(var), exit(0));
}

void	draw_map(t_vars *var)
{
	int	y;
	int	x;

	y = 0;
	mlx_put_image_to_window(var->mlx, var->win, var->bkgr.img, 0, 0);
	while (y < var->wdt)
	{
		x = 0;
		while (x < var->hgt)
		{
			if (var->map[y][x] == '1')
				drawer(var, var->rock.img, x, y);
			else if (var->map[y][x] == 'C')
				drawer(var, var->food.img, x, y);
			else if (var->map[y][x] == 'E')
				drawer(var, var->exit.img, x, y);
			else if (var->map[y][x] == 'P')
				drawer(var, var->plyr.img, x, y);
			x++;
		}
		y++;
	}
}

void	switch_images(t_vars *var)
{
	t_img	temp;

	temp = var->plyr;
	var->plyr = var->plex;
	var->plex = temp;
}

void	update_map(t_vars *var, int y, int x)
{
	if (var->map[var->pos[1] + y][var->pos[0] + x] == '0'
		|| var->map[var->pos[1] + y][var->pos[0] + x] == 'C'
		|| var->map[var->pos[1] + y][var->pos[0] + x] == 'E')
	{
		if (var->last_move == 'E' - '0')
			switch_images(var);
		var->map[var->pos[1]][var->pos[0]] = var->last_move + '0';
		var->last_move = 0;
		if (var->map[var->pos[1] + y][var->pos[0] + x] == 'E')
		{
			if (!find_c(var, 'C', NULL))
				(ft_putstr("You Won!\n"), quit(var), exit(0));
			var->last_move = 'E' - '0';
			switch_images(var);
		}
		var->map[var->pos[1] + y][var->pos[0] + x] = 'P';
		var->pos[0] += x;
		var->pos[1] += y;
		if (var->count == 2147483647)
			(ft_putstr("Too much moves\n"), quit(var), exit(0));
		var->count++;
		draw_map(var);
		print_moves(var);
	}
}
