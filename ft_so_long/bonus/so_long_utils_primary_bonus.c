#include "so_long_bonus.h"

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
				&& var->map[y][x] != '1') || !in_set(var->map[y][x], "01CPVE"))
				(display_err(MAP_ERR), quit(var), exit(0));
			x++;
		}
		y++;
	}
	if (ocurrence(var, 'P') > 1 || ocurrence(var, 'E') > 1
		|| !find_c(var, 'C', NULL) || !find_c(var, 'E', NULL)
		|| !find_c(var, 'P', var->pos))
		(display_err(MAP_ERR), quit(var), exit(0));
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
    mlx_put_image_to_window(var->mlx, var->win, var->plyr.img, var->pos[0] * var->bksz, var->pos[1] * var->bksz);
	return (0);
}

void change_frame(t_vars *var)
{
    int pixel;
    for (int y = 0; y < 45; y++)
    {
        for (int x = 0; x < 45; x++)
        {
            if (var->last_move == ('E' - '0'))
                pixel = my_mlx_pixel_get(&var->anex, x + (var->curr_frame * 45), y);
            else
                pixel = my_mlx_pixel_get(&var->anim, x + (var->curr_frame * 45), y);
            my_mlx_pixel_put(&var->plyr, x, y, pixel);
        }
    }
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
            else if (var->map[y][x] == 'V')
                mlx_put_image_to_window(var->mlx, var->win, var->vill.img, x * var->bksz, y * var->bksz);
        }
    }
    print_moves(var);
}

void update_map(t_vars *var, int y, int x)
{
	if (var->map[var->pos[1] + y][var->pos[0] + x] == '0'
        || var->map[var->pos[1] + y][var->pos[0] + x] == 'C'
        || var->map[var->pos[1] + y][var->pos[0] + x] == 'E')
    {
        var->map[var->pos[1]][var->pos[0]] = var->last_move + '0';
        var->last_move = 0;
        if(var->map[var->pos[1] + y][var->pos[0] + x] == 'E')
        {
            if (!find_c(var, 'C', NULL))
			    (write(1, "You Won!\n", 9), quit(var), exit(0));
            var->last_move = 'E' - '0';
        }
        var->map[var->pos[1] + y][var->pos[0] + x] = 'P';
        var->pos[0] += x;
        var->pos[1] += y;
        if (var->count == 2147483647)
            (display_err("Too much moves\n"), quit(var), exit(0));
        var->count++;
        change_frame(var);
        draw_map(var);
    }
    else if(var->map[var->pos[1] + y][var->pos[0] + x] == 'V')
			(write(1, "You Lost!\n", 10), quit(var), exit(0));
}
