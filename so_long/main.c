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

void quit(t_vars *var)
{
    int y;

    y = 0;
    while (var->map[y])
        free(var->map[y++]);
    q_clear(&var->queue);
    q_clear(&var->visited);
    if (var->food.img)
    {
        mlx_destroy_image(var->mlx, var->anex.img);
        mlx_destroy_image(var->mlx, var->anim.img);
        mlx_destroy_image(var->mlx, var->bkgr.img);
        mlx_destroy_image(var->mlx, var->exit.img);
        mlx_destroy_image(var->mlx, var->food.img);
        mlx_destroy_image(var->mlx, var->plyr.img);
        mlx_destroy_image(var->mlx, var->rock.img);
        mlx_destroy_image(var->mlx, var->vill.img);
    }
    if (var->win)
        mlx_destroy_window(var->mlx, var->win);
    if (var->mlx)
    {
        mlx_destroy_display(var->mlx);
        free(var->mlx);
    }
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int     my_mlx_pixel_get(t_img *img, int x, int y)
{
	char	*dst;
    
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int*)dst);
}

int in_list(t_queue *queue, int *pos)
{
    while (queue)
    {
        if (queue->pos[0] == pos[0] && queue->pos[1] == pos[1])
            return (1);
        queue = queue->next;
    }
    return (0);
}

void next_to(t_vars *var, t_queue *node, int bros[5][2])
{
    int moves[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int i = 0;
    int j = 0;
    int x;
    int y;

    while (i < 4)
    {
        x = node->pos[0] + moves[i][0];
        y = node->pos[1] + moves[i][1];
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

int ate_all(t_vars *var)
{
    int pos[2];

    pos[1] = 0;
    while (var->map[pos[1]])
    {
        pos[0] = 0;
        while (var->map[pos[1]][pos[0]])
        {
            if ((var->map[pos[1]][pos[0]] == 'C' || var->map[pos[1]][pos[0]] == 'E') && !in_list(var->visited, pos))
            {
                return (0);
            }
            pos[0]++;
        }
        pos[1]++;
    }
    return (1);
}

void check_path(t_vars *var)
{
    t_queue *node;
    int     bros[5][2];
    int     i;

    if (put(&var->queue, var->pos[0], var->pos[1])
        || put(&var->visited, var->pos[0], var->pos[1]))
        (printf("malloc error"), quit(var), exit(0));
    while(var->queue != NULL)
    {
        i = 0;
        node = pop(&var->queue);
        next_to(var, node, bros);
        while (bros[i][0] != -1)
        {
            if (!in_list(var->visited, bros[i])
                && (put(&var->queue, bros[i][0], bros[i][1])
                    || put(&var->visited, bros[i][0], bros[i][1])))
                (printf("malloc errors\n"), quit(var), exit(0));
            i++;
        }
    }
    if (!ate_all(var))
        (printf("No valid path!\n"), quit(var), exit(0));
    (q_clear(&var->queue), q_clear(&var->visited));
}

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
				(printf("invalide map file\n"), quit(var), exit(0));
			x++;
		}
		y++;
	}
	if (ocurrence(var, 'P') > 1 || ocurrence(var, 'E') > 1
		|| !find_c(var, 'C', NULL) || !find_c(var, 'E', NULL)
		|| !find_c(var, 'P', var->pos))
		(printf("invalide map file\n"), quit(var), exit(0));
}

void parse(t_vars *var, char *path)
{
	int fd;
	int len;

	fd = open(path, O_RDONLY);
	if (fd == -1)
        (perror("open"), quit(var), exit(0));
	var->map[var->wdt] = get_next_line(fd);
	while (var->map[var->wdt] != NULL)
	{
		str_replace(var->map[var->wdt], '\n', '\0');
		len = ft_strlen(var->map[var->wdt]);
		if ((var->hgt == 0 || len == var->hgt) && len < 44 && var->wdt < 23)
			var->hgt = len;
		else
			(printf("invalide map file\n"), close(fd), quit(var), exit(0));
        var->wdt++;
		var->map[var->wdt] = get_next_line(fd);
	}
    close(fd);
	check_map(var);
}

void draw_map(t_vars *var)
{
    char *str_move_count;

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
    str_move_count = ft_strjoin_px("moves: ", ft_itoa(var->count), 2);
    if (str_move_count == NULL)
        (printf("Malloc error\n"), quit(var), exit(0));
    mlx_string_put(var->mlx, var->win, 22, 26, 0xffffffff, str_move_count);
    free(str_move_count);
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
			    (printf("You Won!\n"), quit(var), exit(0));
            var->last_move = 'E' - '0';
        }
        var->map[var->pos[1] + y][var->pos[0] + x] = 'P';
        var->pos[0] += x;
        var->pos[1] += y;
        if (var->count == 2147483647)
            (printf("Too much moves\n"), quit(var), exit(0));
        var->count++;
    }
    else if(var->map[var->pos[1] + y][var->pos[0] + x] == 'V')
			(printf("You Lost!\n"), quit(var), exit(0));
    change_frame(var);
    draw_map(var);
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
    mlx_put_image_to_window(var->mlx, var->win, var->plyr.img, var->pos[0] * 45, var->pos[1] * 45);
}

void init_textures(t_vars *var)
{
    var->bkgr.img = load(var->mlx, "bkgr.xpm", &var->bksz, &var->bksz);
    var->food.img = load(var->mlx, "food.xpm", &var->bksz, &var->bksz);
    var->rock.img = load(var->mlx, "rock.xpm", &var->bksz, &var->bksz);
    var->exit.img = load(var->mlx, "exit.xpm", &var->bksz, &var->bksz);
    var->vill.img = load(var->mlx, "vill.xpm", &var->bksz, &var->bksz);
    var->anex.img = load(var->mlx, "anex.xpm", &var->bksz, &var->bksz);
    var->anim.img = load(var->mlx, "anim.xpm", &var->bksz, &var->bksz);
    var->plyr.img = mlx_new_image(var->mlx, var->bksz, var->bksz);
    var->anex.addr = mlx_get_data_addr(var->anex.img, &var->anex.bits_per_pixel, &var->anex.line_length, &var->anex.endian);
    var->plyr.addr = mlx_get_data_addr(var->plyr.img, &var->plyr.bits_per_pixel, &var->plyr.line_length, &var->plyr.endian);
    var->anim.addr = mlx_get_data_addr(var->anim.img, &var->anim.bits_per_pixel, &var->anim.line_length, &var->anim.endian);
    if (!(var->bkgr.img && var->food.img && var->rock.img
        && var->exit.img && var->vill.img && var->plyr.img
        && var->plyr.addr && var->anim.img && var->anim.addr
        && var->anex.img && var->anex.addr))
        (printf("Failed to load textures!\n"), quit(var), exit(0));
    change_frame(var);
}

int destroy(t_vars *var)
{
    quit(var);
    exit(0);
}

int check_file_name(char *file)
{
    int size;

    size = ft_strlen(file);
    if (file[size - 1] == 'r' && file[size - 2] == 'e' && file[size - 3] == 'b'
        && file[size - 4] == '.' && ft_isalnum(file[size - 5]))
        return (1);
    return (0);
}

int main(int ac, char **av)
{
	t_vars var;

	if (ac != 2 || !check_file_name(av[1]))
        (printf("usage: program *.ber\n"), exit(0));
	ft_bzero(&var, sizeof(t_vars));
    parse(&var, av[1]);
    check_path(&var);
	var.mlx = mlx_init();
    if (var.mlx == NULL)
        return (quit(&var), 0);
    init_textures(&var);
	var.win = mlx_new_window(var.mlx, var.hgt * var.bksz, var.wdt * var.bksz, "Main");
    if (var.win == NULL)
        return (quit(&var), 0);
    draw_map(&var);
    mlx_hook(var.win, 2, 1L<<0, key_hook, &var);
    mlx_hook(var.win, 17, 1L<<17, destroy, &var);
    mlx_loop_hook(var.mlx, render_next_frame, &var);
    mlx_loop(var.mlx);
}
