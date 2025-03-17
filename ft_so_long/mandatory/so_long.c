/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 18:04:10 by kel-mous          #+#    #+#             */
/*   Updated: 2025/03/15 18:04:26 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

void	check_path(t_vars *var)
{
	t_queue		*node;
	int			bros[5][2];
	int			i;

	if (put(&var->queue, var->pos[0], var->pos[1])
		|| put(&var->visited, var->pos[0], var->pos[1]))
		(ft_putstr(MLC_ERR), quit(var), exit(0));
	while (var->queue != NULL)
	{
		i = 0;
		node = pop(&var->queue);
		next_to(var, node, bros);
		while (bros[i][0] != -1)
		{
			if (!in_list(var->visited, bros[i]))
				if (put(&var->queue, bros[i][0], bros[i][1])
					|| put(&var->visited, bros[i][0], bros[i][1]))
					(ft_putstr(MLC_ERR), quit(var), exit(0));
			i++;
		}
	}
	if (!ate_all(var))
		(ft_putstr(WRG_PTH), quit(var), exit(0));
	(q_clear(&var->queue), q_clear(&var->visited));
}

int	key_hook(int keysym, t_vars *var)
{
	if (keysym == 'w' || keysym == XK_UP)
		update_map(var, -1, 0);
	else if (keysym == 'a' || keysym == XK_LEFT)
		update_map(var, 0, -1);
	else if (keysym == 's' || keysym == XK_DOWN)
		update_map(var, 1, 0);
	else if (keysym == 'd' || keysym == XK_RIGHT)
		update_map(var, 0, 1);
	else if (keysym == ESC)
		(quit(var), exit(0));
	return (0);
}

void	init_textures(t_vars *var)
{
	var->bkgr.img = loader(var, BKGR);
	var->food.img = loader(var, FOOD);
	var->rock.img = loader(var, ROCK);
	var->exit.img = loader(var, EXIT);
	var->plyr.img = loader(var, PLYR);
	var->plex.img = loader(var, PLEX);
	if (!(var->bkgr.img && var->food.img && var->rock.img
			&& var->exit.img && var->plyr.img && var->plex.img))
		(ft_putstr(IMG_ERR), quit(var), exit(0));
}

void	parse(t_vars *var, char *path)
{
	int		fd;
	int		len;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		(ft_putstr(OPN_ERR), perror(""), quit(var), exit(0));
	var->map[var->wdt] = get_next_line(fd);
	while (var->map[var->wdt] != NULL)
	{
		str_replace(var->map[var->wdt], '\n', '\0');
		len = ft_strlen(var->map[var->wdt]);
		if ((var->hgt == 0 || len == var->hgt) && len < 44 && var->wdt < 23)
			var->hgt = len;
		else
			(ft_putstr(MAP_ERR), close(fd), quit(var), exit(0));
		var->wdt++;
		var->map[var->wdt] = get_next_line(fd);
	}
	close(fd);
	check_map(var);
}

int	main(int ac, char **av)
{
	t_vars	var;

	if (ac != 2 || !check_file_name(av[1]))
		(ft_putstr(PRM_ERR), exit(0));
	ft_bzero(&var, sizeof(t_vars));
	parse(&var, av[1]);
	check_path(&var);
	var.mlx = mlx_init();
	if (var.mlx == NULL)
		return (quit(&var), 0);
	init_textures(&var);
	var.win = mlx_new_window(var.mlx, var.hgt * var.bksz,
			var.wdt * var.bksz, "Main");
	if (var.win == NULL)
		return (quit(&var), 0);
	draw_map(&var);
	mlx_hook(var.win, 2, 1L << 0, key_hook, &var);
	mlx_hook(var.win, 17, 1L << 17, destroy, &var);
	mlx_loop(var.mlx);
}
