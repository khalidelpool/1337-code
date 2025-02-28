#include "minilibx-linux/mlx.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "get_next_line.c"
#include "get_next_line_utils.c"
#include "utils.c"

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
			if ((y == 0 || x == 0 || y == var->wdt - 1 || x == var->hgt - 1)
				&& var->map[y][x] != '1')
				(printf("invalide map file, x is: %d, y is: %d\n", x, y), exit(1));
			x++;
		}
		y++;
	}
	if (!find(var->map, 'C') || !find(var->map, 'E')
		|| !find_c(var, 'P', 1)/*these 2 functs probably should be merged*/)
        (printf("invalide map file\n"), exit(1));
}

void parse(t_vars *var, char *path)
{
	int fd;
	int len;

	fd = open(path, O_RDONLY);
	if (fd == -1)
        (perror("open"), exit(1));
	var->map[var->wdt] = get_next_line(fd);
	while (var->map[var->wdt] != NULL)
	{
		str_replace(var->map[var->wdt], '\n', '\0');
		len = ft_strlen(var->map[var->wdt]);
		if ((var->hgt == 0 || len == var->hgt) && len > 2 && len < 43) // check width too
			var->hgt = len;
		else
			(/*function to clear var*/ printf("invalide map file\n"), exit(1));
		var->map[++(var->wdt)] = get_next_line(fd);
	}
	var->map[var->wdt] = NULL;
	check_map(var);
	for (int y = 0; var->map[y]; y++)
    {
        for(int x = 0; var->map[y][x]; x++)
        {
            printf("%c", var->map[y][x]);
        }
		printf("\n");
    }
}

void draw_map(t_vars *vars)
{
    mlx_put_image_to_window(vars->mlx, vars->win, vars->bkgr.img, 0, 0);
    for(int y = 0; y < vars->wdt; y++)
    {
        for(int x = 0; x < vars->hgt; x++)
        {
            if (vars->map[y][x] == '1')
                mlx_put_image_to_window(vars->mlx, vars->win, vars->rock.img, x * vars->rock.hgt, y * vars->rock.wdt);
            else if (vars->map[y][x] == 'C')
                mlx_put_image_to_window(vars->mlx, vars->win, vars->food.img, x * vars->food.hgt, y * vars->food.wdt);
            else if (vars->map[y][x] == 'E')
                mlx_put_image_to_window(vars->mlx, vars->win, vars->exit.img, x * vars->exit.hgt, y * vars->exit.wdt);
            else if(vars->map[y][x] == 'P')
                mlx_put_image_to_window(vars->mlx, vars->win, vars->plyr.img, x * vars->plyr.hgt, y * vars->plyr.wdt);
        }
    }
    mlx_string_put(vars->mlx, vars->win, 22, 26, 0xffffffff, ft_strjoin_px("moves: ", ft_itoa(vars->count), 2));
    printf("\n");
}

void update_map(t_vars *vars, int y, int x)
{
	if (vars->map[vars->y + y][vars->x + x] == '0'
        || vars->map[vars->y + y][vars->x + x] == 'C')
    {
        vars->map[vars->y][vars->x] = '0';
        vars->map[vars->y + y][vars->x + x] = 'P';
        vars->x += x;
        vars->y += y;
        if (vars->count == 2147483647)
            (/*function to clear var here*/printf("too much moves\n"), exit(0));
        vars->count++;
    }
    else if(vars->map[vars->y + y][vars->x + x] == 'E')
    {
        if (!find_c(vars, 'C', 0))
			(/*function to clear var here*/printf("You Won!\n"), exit(0));
    }
    for (int y = 0; vars->map[y]; y++)
    {
        for(int x = 0; vars->map[y][x]; x++)
        {
            printf("%c", vars->map[y][x]);
        }
        printf("\n");
    }
    draw_map(vars);
}

int key_hook(int keysym, t_vars *vars)
{
    if (keysym == 'w' || keysym == XK_Up)
        update_map(vars, -1, 0);
    else if (keysym == 'a' || keysym == XK_Left)
        update_map(vars, 0, -1);
    else if (keysym == 's' || keysym == XK_Down)
        update_map(vars, 1, 0);
    else if (keysym == 'd' || keysym == XK_Right)
        update_map(vars, 0, 1);
    else
        return (1); // this return should be checked
	return (0);
}

int main(int ac, char **av)
{
	t_vars var;

	if (ac != 2)
        (printf("usage: program *.ber\n"), exit(0));
	ft_bzero(&var, sizeof(t_vars));
    parse(&var, av[1]);
	var.mlx = mlx_init();

    var.bkgr.img = load(var.mlx, "bkgr.xpm", &var.bkgr.wdt, &var.bkgr.hgt);
    var.plyr.img = load(var.mlx, "plyr.xpm", &var.plyr.wdt, &var.plyr.hgt);
    var.food.img = load(var.mlx, "food.xpm", &var.food.wdt, &var.food.hgt);
    var.rock.img = load(var.mlx, "rock.xpm", &var.rock.wdt, &var.rock.hgt);
    var.exit.img = load(var.mlx, "exit.xpm", &var.exit.wdt, &var.exit.hgt);
	var.win = mlx_new_window(var.mlx, var.hgt * var.plyr.wdt, var.wdt * var.plyr.wdt, "Main"); // update this to the size of map

	draw_map(&var);
	mlx_key_hook(var.win, key_hook, &var);
    mlx_loop(var.mlx);
}
