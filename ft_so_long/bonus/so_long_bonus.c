#include "so_long_bonus.h"

void check_path(t_vars *var)
{
    t_queue *node;
    int     bros[5][2];
    int     i;

    if (put(&var->queue, var->pos[0], var->pos[1])
        || put(&var->visited, var->pos[0], var->pos[1]))
        (display_err(PTH_ERR), quit(var), exit(0));
    while(var->queue != NULL)
    {
        i = 0;
        node = pop(&var->queue);
        next_to(var, node, bros);
        while (bros[i][0] != -1)
        {
            if (!in_list(var->visited, bros[i]))
                if (put(&var->queue, bros[i][0], bros[i][1])
                    || put(&var->visited, bros[i][0], bros[i][1]))
                        (display_err(PTH_ERR), quit(var), exit(0));
            i++;
        }
    }
    if (!ate_all(var))
        (display_err(WRG_PTH), quit(var), exit(0));
    (q_clear(&var->queue), q_clear(&var->visited));
}

int key_hook(int keysym, t_vars *var)
{
	if (keysym == 'w' || keysym == XK_Up)
		update_map(var, -1, 0);
	else if (keysym == 'a' || keysym == XK_Left)
		update_map(var, 0, -1);
	else if (keysym == 's' || keysym == XK_Down)
		update_map(var, 1, 0);
	else if (keysym == 'd' || keysym == XK_Right)
		update_map(var, 0, 1);
	else if (keysym == ESC)
		(quit(var), exit(0));
	return (0);
}

void init_textures(t_vars *var)
{
    var->bkgr.img = load(var->mlx, BKGR, &var->bksz, &var->bksz);
    var->food.img = load(var->mlx, FOOD, &var->bksz, &var->bksz);
    var->rock.img = load(var->mlx, ROCK, &var->bksz, &var->bksz);
    var->exit.img = load(var->mlx, EXIT, &var->bksz, &var->bksz);
    var->vill.img = load(var->mlx, VILL, &var->bksz, &var->bksz);
    var->anex.img = load(var->mlx, ANEX, &var->bksz, &var->bksz);
    var->anim.img = load(var->mlx, ANIM, &var->bksz, &var->bksz);
    var->plyr.img = mlx_new_image(var->mlx, var->bksz, var->bksz);
    var->anex.addr = mlx_get_data_addr(var->anex.img, &var->anex.bits_per_pixel, &var->anex.line_length, &var->anex.endian);
    var->plyr.addr = mlx_get_data_addr(var->plyr.img, &var->plyr.bits_per_pixel, &var->plyr.line_length, &var->plyr.endian);
    var->anim.addr = mlx_get_data_addr(var->anim.img, &var->anim.bits_per_pixel, &var->anim.line_length, &var->anim.endian);
    if (!(var->bkgr.img && var->food.img && var->rock.img
        && var->exit.img && var->vill.img && var->plyr.img
        && var->plyr.addr && var->anim.img && var->anim.addr
        && var->anex.img && var->anex.addr))
        (display_err(IMG_ERR), quit(var), exit(0));
    change_frame(var);
}

void parse(t_vars *var, char *path)
{
	int fd;
	int len;

	fd = open(path, O_RDONLY);
	if (fd == -1)
        (display_err(OPN_ERR), perror(""), quit(var), exit(0));
	var->map[var->wdt] = get_next_line(fd);
	while (var->map[var->wdt] != NULL)
	{
		str_replace(var->map[var->wdt], '\n', '\0');
		len = ft_strlen(var->map[var->wdt]);
		if ((var->hgt == 0 || len == var->hgt) && len < 44 && var->wdt < 23)
			var->hgt = len;
		else
			(display_err(MAP_ERR), close(fd), quit(var), exit(0));
        var->wdt++;
		var->map[var->wdt] = get_next_line(fd);
	}
    close(fd);
	check_map(var);
}

int main(int ac, char **av)
{
    t_vars var;

	if (ac != 2 || !check_file_name(av[1]))
        (display_err(PRM_ERR), exit(0));
    ft_bzero(&var, sizeof(t_vars));
    parse(&var, av[1]);
    check_path(&var);
    var.mlx = mlx_init();
    if (var.mlx == NULL)
        return (quit(&var), 0);
    init_textures(&var);
    var.win = new_win(var.mlx, var.hgt * var.bksz, var.wdt * var.bksz, "Main");
    if (var.win == NULL)
        return (quit(&var), 0);
    draw_map(&var);
    mlx_hook(var.win, 2, 1L<<0, key_hook, &var);
    mlx_hook(var.win, 17, 1L<<17, destroy, &var);
    mlx_loop_hook(var.mlx, render_next_frame, &var);
    mlx_loop(var.mlx);
}
