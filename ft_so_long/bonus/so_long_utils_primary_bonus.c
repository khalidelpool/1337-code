/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils_primary_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:42:08 by kel-mous          #+#    #+#             */
/*   Updated: 2025/03/17 20:42:14 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long_bonus.h"

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
				|| !in_set(var->map[y][x], "01CPVE"))
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

int	render_next_frame(t_vars *var)
{
	if (var->random == 0)
	{
		if (var->curr_frame == 7)
			var->curr_frame = 0;
		else
			var->curr_frame++;
		change_frame(var);
	}
	var->random++;
	if (var->random > 9000)
		var->random = 0;
	mlx_put_image_to_window(var->mlx, var->win, var->plyr.img,
		var->pos[0] * var->bksz, var->pos[1] * var->bksz);
	return (0);
}

void	change_frame(t_vars *var)
{
	int	pixel;
	int	y;
	int	x;

	y = 0;
	while (y < var->bksz)
	{
		x = 0;
		while (x < var->bksz)
		{
			if (var->last_move == ('E' - '0'))
				pixel = my_mlx_pixel_get(&var->anex,
						x + (var->curr_frame * var->bksz), y);
			else
				pixel = my_mlx_pixel_get(&var->anim,
						x + (var->curr_frame * var->bksz), y);
			my_mlx_pixel_put(&var->plyr, x, y, pixel);
			x++;
		}
		y++;
	}
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
			else if (var->map[y][x] == 'V')
				drawer(var, var->vill.img, x, y);
			x++;
		}
		y++;
	}
	print_moves(var);
}

void	update_map(t_vars *var, int y, int x)
{
	if (var->map[var->pos[1] + y][var->pos[0] + x] == '0'
		|| var->map[var->pos[1] + y][var->pos[0] + x] == 'C'
		|| var->map[var->pos[1] + y][var->pos[0] + x] == 'E')
	{
		var->map[var->pos[1]][var->pos[0]] = var->last_move + '0';
		var->last_move = 0;
		if (var->map[var->pos[1] + y][var->pos[0] + x] == 'E')
		{
			if (!find_c(var, 'C', NULL))
				(ft_putstr("You Won!\n"), quit(var), exit(0));
			var->last_move = 'E' - '0';
		}
		var->map[var->pos[1] + y][var->pos[0] + x] = 'P';
		var->pos[0] += x;
		var->pos[1] += y;
		if (var->count == 2147483647)
			(ft_putstr("Too much moves\n"), quit(var), exit(0));
		var->count++;
		change_frame(var);
		draw_map(var);
	}
	else if (var->map[var->pos[1] + y][var->pos[0] + x] == 'V')
		(ft_putstr("You Lost!\n"), quit(var), exit(0));
}
