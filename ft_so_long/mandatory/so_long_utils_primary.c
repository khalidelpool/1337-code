#include "so_long.h"

void check_map(t_vars *var)
{
	int x;
	int y;

	y = 0;
	while (var->map[y])
	{
		x = 0;
		while (var->map[y][x])
		{
			if (((y == 0 || x == 0 || y == var->wdt - 1 || x == var->hgt - 1)
				&& var->map[y][x] != '1') || !in_set(var->map[y][x], "01CPE"))
				(printf(MAP_ERR), quit(var), exit(0));
			x++;
		}
		y++;
	}
	if (ocurrence(var, 'P') > 1 || ocurrence(var, 'E') > 1
		|| !find_c(var, 'C', NULL) || !find_c(var, 'E', NULL)
		|| !find_c(var, 'P', var->pos))
		(printf(MAP_ERR), quit(var), exit(0));
}

void draw_map(t_vars *var)
{
    mlx_put_image_to_window(var->mlx, var->win, var->bkgr.img, 0, 0);
    for(int y = 0; y < var->wdt; y++)
    {
        for(int x = 0; x < var->hgt; x++)
        {
            if (var->map[y][x] == '1')
                mlx_put_image_to_window(var->mlx, var->win, var->rock.img, x * var->bksz, y * var->bksz);
            else if (var->map[y][x] == 'C')
                mlx_put_image_to_window(var->mlx, var->win, var->food.img, x * var->bksz, y * var->bksz);
            else if (var->map[y][x] == 'E')
                mlx_put_image_to_window(var->mlx, var->win, var->exit.img, x * var->bksz, y * var->bksz);
            else if (var->map[y][x] == 'P')
                mlx_put_image_to_window(var->mlx, var->win, var->plyr.img, x * var->bksz, y * var->bksz);
        }
    }
    print_moves(var);
}

void switch_images(t_vars *var)
{
    t_img temp;

    temp = var->plyr;
    var->plyr = var->plex;
    var->plex = temp;
}

void update_map(t_vars *var, int y, int x)
{
	if (var->map[var->pos[1] + y][var->pos[0] + x] == '0'
        || var->map[var->pos[1] + y][var->pos[0] + x] == 'C'
        || var->map[var->pos[1] + y][var->pos[0] + x] == 'E')
    {
        if (var->last_move == 'E' - '0')
            switch_images(var);
        var->map[var->pos[1]][var->pos[0]] = var->last_move + '0';
        var->last_move = 0;
        if(var->map[var->pos[1] + y][var->pos[0] + x] == 'E')
        {
            if (!find_c(var, 'C', NULL))
			    (printf("You Won!\n"), quit(var), exit(0));
            var->last_move = 'E' - '0';
            switch_images(var);
        }
        var->map[var->pos[1] + y][var->pos[0] + x] = 'P';
        var->pos[0] += x;
        var->pos[1] += y;
        if (var->count == 2147483647)
            (printf("Too much moves\n"), quit(var), exit(0));
        var->count++;
        draw_map(var);
    }
}
