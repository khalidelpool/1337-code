#include "minilibx-linux/mlx.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
#include "get_next_line.h"
#include "get_next_line.c"
#include "get_next_line_utils.c"
#include "utils.c"

#define WIDTH 450
#define HEIGHT 810
#define load mlx_xpm_file_to_image
#define XK_Left                          0xff51  /* Move left, left arrow */
#define XK_Up                            0xff52  /* Move up, up arrow */
#define XK_Right                         0xff53  /* Move right, right arrow */
#define XK_Down                          0xff54  /* Move down, down arrow */

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
    int     wdt;
    int     hgt;
}				t_img;

typedef struct	s_vars {
    void	*mlx;
    void	*win;
    t_img   bkgr;
    t_img   rock;
    t_img   plyr;
    t_img   food;
    t_img   exit;
    char    **map;
    int     x;
    int     y;
    int     count;
}				t_vars;

char **init_map() {
    char **map = malloc(sizeof(char *) * 11);  // Allocate for 10 strings + NULL
    if (!map) return NULL;

    map[0] = ft_strdup("111111111111111111");
    map[1] = ft_strdup("101c0c100000001cc1");
    map[2] = ft_strdup("1011011000000000c1");
    map[3] = ft_strdup("100000000000000011");
    map[4] = ft_strdup("100000000000000001");
    map[5] = ft_strdup("100000001010000001");
    map[6] = ft_strdup("10000001ccc1000001");
    map[7] = ft_strdup("1000001ccccc100001");
    map[8] = ft_strdup("1P0001ccccccc100E1");
    map[9] = ft_strdup("111111111111111111");
    map[10] = NULL;  // Null terminator

    return map;
}

int find_c(t_vars *var, char c, int change)
{
    for (int y = 0; var->map[y]; y++)
    {
        for(int x = 0; var->map[y][x]; x++)
        {
            if (var->map[y][x] == c)
            {
                if (change)
                {
                    var->y = y;
                    var->x = x;
                }
                return (1);
            }
        }
    }
    return (0);
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_map(t_vars *vars)
{
    mlx_put_image_to_window(vars->mlx, vars->win, vars->bkgr.img, 0, 0);
    for(int y = 0; y < 10; y++)
    {
        for(int x = 0; x < 18; x++)
        {
            if (vars->map[y][x] == '1')
                mlx_put_image_to_window(vars->mlx, vars->win, vars->rock.img, x * vars->rock.hgt, y * vars->rock.wdt);
            else if (vars->map[y][x] == 'c')
                mlx_put_image_to_window(vars->mlx, vars->win, vars->food.img, x * vars->food.hgt, y * vars->food.wdt);
            else if (vars->map[y][x] == 'E')
                mlx_put_image_to_window(vars->mlx, vars->win, vars->exit.img, x * vars->exit.hgt, y * vars->exit.wdt);
            else if(vars->map[y][x] == 'P')
                mlx_put_image_to_window(vars->mlx, vars->win, vars->plyr.img, x * vars->plyr.hgt, y * vars->plyr.wdt);
        }
    }
    mlx_string_put(vars->mlx, vars->win, 22, 26, 0xffffffff, ft_strjoin_px("moves: ", ft_itoa(vars->count), 2));
}

void update_map(t_vars *vars, int y, int x)
{
    if (vars->map[vars->y + y][vars->x + x] == '0'
        || vars->map[vars->y + y][vars->x + x] == 'c')
    {
        vars->map[vars->y][vars->x] = '0';
        vars->map[vars->y + y][vars->x + x] = 'P';
        vars->x += x;
        vars->y += y;
        if (vars->count == 2147483647)
            exit(0);
        vars->count++;
    }
    else if(vars->map[vars->y + y][vars->x + x] == 'E')
    {
        if (!find_c(vars, 'c', 0))
        {
            printf("You Won!\n");
            exit(0);
        }
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
    
	printf("the keysym is: %d, the char is: %c\n", keysym, keysym);
    if (keysym == 'w' || keysym == XK_Up)
        update_map(vars, -1, 0);
    else if (keysym == 'a' || keysym == XK_Left)
        update_map(vars, 0, -1);
    else if (keysym == 's' || keysym == XK_Down)
        update_map(vars, 1, 0);
    else if (keysym == 'd' || keysym == XK_Right)
        update_map(vars, 0, 1);
    else
        return (1);
	return (0);
}

void parse(char *path)
{
    int fd = open(path, O_RDONLY);
    if (fd == -1)
        (perror("open"), exit(1));
    
}

int main(int ac, char **av)
{
    t_vars var;
    int w, h;

    if (ac != 2)
        printf("usage: program *.ber\n"), exit(0);
    parse(av[1]);
    var.mlx = mlx_init();
    var.win = mlx_new_window(var.mlx, HEIGHT, WIDTH, "Main");

    var.map = init_map();
    var.count = 0;
    find_c(&var, 'P', 1);

    var.bkgr.img = load(var.mlx, "bkgr.xpm", &var.bkgr.wdt, &var.bkgr.hgt);
    var.plyr.img = load(var.mlx, "plyr.xpm", &var.plyr.wdt, &var.plyr.hgt);
    var.food.img = load(var.mlx, "food.xpm", &var.food.wdt, &var.food.hgt);
    var.rock.img = load(var.mlx, "rock.xpm", &var.rock.wdt, &var.rock.hgt);
    var.exit.img = load(var.mlx, "exit.xpm", &var.exit.wdt, &var.exit.hgt);

    draw_map(&var);

    mlx_key_hook(var.win, key_hook, &var);
    mlx_loop(var.mlx);
}
