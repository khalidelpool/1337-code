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

void next_to(t_vars *var, t_queue *node, int bros[5][2], int exclude_E)
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
            if (var->map[y][x] != '1' && (var->map[y][x] != 'E' || !exclude_E))
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
            if (var->map[pos[1]][pos[0]] == 'C' && !in_list(var->visited, pos))
            {
                // ft_lstiter(var->visited, f);
                printf("x is: %d, y is: %d\n", pos[0], pos[1]);
                return (0);
            }
            pos[0]++;
        }
        pos[1]++;
    }
    
    q_clear(&var->visited);
    q_clear(&var->queue);
    return (1);
}

int check_path(t_vars *var, int exclude_E)
{
    t_queue *node;
    int     bros[5][2];
    int     i;

    if (put(&var->queue, var->pos[0], var->pos[1])
        || put(&var->visited, var->pos[0], var->pos[1]))
        return (printf("malloc error"), 0);
    while(var->queue != NULL)
    {
        i = 0;
        node = pop(&var->queue);
        next_to(var, node, bros, exclude_E);
        while (bros[i][0] != -1)
        {
            if (!in_list(var->visited, bros[i]))
            {
                put(&var->queue, bros[i][0], bros[i][1]);
                put(&var->visited, bros[i][0], bros[i][1]);
                /*if problem do return (printf("malloc error"), 0);*/
                // var->map[bros[i][1]][bros[i][0]] = '1';
            }
            i++;
        }
        // for (int y = 0; var->map[y]; y++)
        // {
        //     for(int x = 0; var->map[y][x]; x++)
        //     {
        //         printf("%c", var->map[y][x]);
        //     }
        //     printf("\n");
        // }
        // printf("------------------------------------\n");
        // sleep(1);
    }
    if ((exclude_E && ate_all(var) && check_path(var, 0))
        || (!exclude_E && in_list(var->visited, find_c(var, 'E', bros[4]))))
        return (printf("valid\n"), q_clear(&var->queue), q_clear(&var->visited), 1);
    return (printf("invalid\n"), q_clear(&var->queue), q_clear(&var->visited), 0);
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
			if ((y == 0 || x == 0 || y == var->wdt - 1 || x == var->hgt - 1)
				&& var->map[y][x] != '1')
				(printf("invalide map file, x is: %d, y is: %d\n", x, y), exit(1));
			x++;
		}
		y++;
	}
	if (!find_c(var, 'C', NULL) || !find_c(var, 'E', NULL)
		|| !find_c(var, 'P', var->pos)/*these 2 functs probably should be merged*/)
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
	// for (int y = 0; var->map[y]; y++)
    // {
    //     for(int x = 0; var->map[y][x]; x++)
    //     {
    //         printf("%c", var->map[y][x]);
    //     }
	// 	printf("\n");
    // }
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
    mlx_string_put(var->mlx, var->win, 22, 26, 0xffffffff, ft_strjoin_px("moves: ", ft_itoa(var->count), 2));
}

void update_map(t_vars *var, int y, int x)
{
	if (var->map[var->pos[1] + y][var->pos[0] + x] == '0'
        || var->map[var->pos[1] + y][var->pos[0] + x] == 'C')
    {
        var->map[var->pos[1]][var->pos[0]] = '0';
        var->map[var->pos[1] + y][var->pos[0] + x] = 'P';
        var->pos[0] += x;
        var->pos[1] += y;
        if (var->count == 2147483647)
            (/*function to clear var here*/printf("too much moves\n"), exit(0));
        var->count++;
    }
    else if(var->map[var->pos[1] + y][var->pos[0] + x] == 'E')
    {
        if (!find_c(var, 'C', NULL))
			(/*function to clear var here*/printf("You Won!\n"), exit(0));
    }
    else if(var->map[var->pos[1] + y][var->pos[0] + x] == 'V')
    {
			(/*function to clear var here*/printf("You Lost!\n"), exit(0));
    }
    // for (int y = 0; var->map[y]; y++)
    // {
    //     for(int x = 0; var->map[y][x]; x++)
    //     {
    //         printf("%c", var->map[y][x]);
    //     }
    //     printf("\n");
    // }
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
    else
        return (1); // this return should be checked
	return (0);
}

void change_frame(t_vars *var)
{
    int pixel;
    for (int y = 0; y < 45; y++)
    {
        for (int x = 0; x < 45; x++)
        {
            pixel = my_mlx_pixel_get(&var->anim, x + (var->curr_frame * 45), y);
            my_mlx_pixel_put(&var->plyr, x, y, pixel);
        }
    }
}
// 2700213 updates every 60 sec
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

void fill_img(t_vars *var, int color)
{
    for (int y = 0; y < var->bkgr.hgt; y++)
    {
        for (int x = 0; x < var->bkgr.wdt; x++)
        {
            my_mlx_pixel_put(&var->bkgr, x, y, color);
        }
    }
}

void init_textures(t_vars *var)
{
    var->bkgr.img = load(var->mlx, "bkgr.xpm", &var->bkgr.wdt, &var->bkgr.hgt);
    var->food.img = load(var->mlx, "food.xpm", &var->bksz, &var->bksz);
    var->rock.img = load(var->mlx, "rock.xpm", &var->bksz, &var->bksz);
    var->exit.img = load(var->mlx, "exit.xpm", &var->bksz, &var->bksz);
    var->vill.img = load(var->mlx, "vill.xpm", &var->bksz, &var->bksz);
    var->plyr.img = mlx_new_image(var->mlx, var->bksz, var->bksz);
    var->plyr.addr = mlx_get_data_addr(var->plyr.img, &var->plyr.bits_per_pixel, &var->plyr.line_length, &var->plyr.endian);
    var->anim.img = load(var->mlx, "anim.xpm", &var->bksz, &var->bksz);
    var->anim.addr = mlx_get_data_addr(var->anim.img, &var->anim.bits_per_pixel, &var->anim.line_length, &var->anim.endian);
    if (!(var->bkgr.img && var->food.img && var->rock.img
        && var->exit.img && var->vill.img && var->plyr.img
        && var->plyr.addr && var->anim.img && var->anim.addr ))
        (printf("should safely quit, some textures didnt load correctly\n"), exit(0));
    change_frame(&var);
}

int main(int ac, char **av)
{
	t_vars var;
    t_queue node;
    t_queue *neys;

	if (ac != 2)
        (printf("usage: program *.ber\n"), exit(0));
	ft_bzero(&var, sizeof(t_vars));
    parse(&var, av[1]);
    check_path(&var, 1);
	var.mlx = mlx_init();
    init_textures(&var);
	var.win = mlx_new_window(var.mlx, var.hgt * var.bksz, var.wdt * var.bksz, "Main"); // update this to the size of map
    draw_map(&var);
	mlx_key_hook(var.win, key_hook, &var);
    mlx_loop_hook(var.mlx, render_next_frame, &var);
    mlx_loop(var.mlx);
}
