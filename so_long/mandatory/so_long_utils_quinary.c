/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils_quinary.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:53:00 by kel-mous          #+#    #+#             */
/*   Updated: 2025/03/17 10:53:04 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

int	get_next_move(int i, int choice)
{
	if (choice == 0)
	{
		if (i % 2 == 0)
		{
			if (i == 0)
				return (-1);
			else
				return (1);
		}
		else
			return (0);
	}
	else
	{
		if (i % 2 != 0)
		{
			if (i == 1)
				return (1);
			else
				return (-1);
		}
		else
			return (0);
	}
}

void	*loader(t_vars *var, char *path)
{
	return (mlx_xpm_file_to_image(var->mlx, path, &var->bksz, &var->bksz));
}

int	drawer(t_vars *var, void *img, int x, int y)
{
	return (mlx_put_image_to_window(var->mlx, var->win, img,
			x * var->bksz, y * var->bksz));
}
