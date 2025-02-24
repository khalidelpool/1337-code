#include "minilibx-linux/mlx.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

#define WIDTH 450
#define HEIGHT 810

typedef struct	s_buff {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
    int     img_width;
    int     img_height;
}				t_buff;

typedef struct	s_vars {
    void	*mlx;
    void	*win;
    t_buff  buff;
    t_buff  rock;
    t_buff  spider;
    int     x;
    int     y;
}				t_vars;

void	my_mlx_pixel_put(t_buff *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_obstacle(char **map, t_vars *vars)
{
    for(int y = 0; y < 10; y++)
    {
        for(int x = 0; x < 18; x++)
        {
            if (map[y][x] == '1')
                mlx_put_image_to_window(vars->mlx, vars->win, vars->rock.img, x * vars->rock.img_height, y * vars->rock.img_width);
        }
    }
}

char *map[] = { "111111111111111111",
                "100000000000000001",
                "100000000000000001",
                "100000000000000001",
                "100000000000000001",
                "100000000000000001",
                "100000000000000001",
                "100000000000000001",
                "100000000000000001",
                "111111111111111111", NULL};

int key_hook(int keycode, t_vars *vars)
{
	printf("the keycode is: %d, the char is: %c\n", keycode, keycode);
    if ((keycode == 'w' || keycode == 65362) && (vars->y) > 45)
        vars->y-= vars->spider.img_width;
    else if ((keycode == 'a' || keycode == 65361) && (vars->x) > 45)
        vars->x-= vars->spider.img_height;
    else if ((keycode == 's' || keycode == 65364) && (vars->y + vars->spider.img_width) < WIDTH - 45)
        vars->y+= vars->spider.img_width;
    else if ((keycode == 'd' || keycode == 65363) && (vars->x + vars->spider.img_height) < HEIGHT- 45)
        vars->x+= vars->spider.img_height;
    else   
        return (1);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->buff.img, 0, 0);
    draw_obstacle(map, vars);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->spider.img, vars->x, vars->y);
    // mlx_pixel_put(vars->mlx, vars->win, vars->x, vars->y, 0);
    // my_mlx_pixel_put(&vars->buff, vars->x, vars->y, 0);
    // mlx_put_image_to_window(vars->mlx, vars->win, vars->buff.img, 0, 0);
	return (0);
}

int main()
{
    t_vars var;
    char *relative_path;
    int w, h;

    var.mlx = mlx_init();
    var.win = mlx_new_window(var.mlx, HEIGHT, WIDTH, "Main");

    relative_path = "./grass.xpm";
    var.buff.img = mlx_xpm_file_to_image(var.mlx, relative_path, &var.buff.img_width, &var.buff.img_height);
    var.buff.addr = mlx_get_data_addr(var.buff.img, &var.buff.bits_per_pixel,
        &var.buff.line_length, &var.buff.endian);
    mlx_put_image_to_window(var.mlx, var.win, var.buff.img, 0, 0);

    var.spider.img = mlx_xpm_file_to_image(var.mlx, "spider.xpm", &var.spider.img_width, &var.spider.img_height);
    mlx_put_image_to_window(var.mlx, var.win, var.spider.img, 45, 45);

    var.rock.img = mlx_xpm_file_to_image(var.mlx, "rock.xpm", &var.rock.img_width, &var.rock.img_height);
    // mlx_put_image_to_window(var.mlx, var.win, var.rock.img, 0, 0);
    draw_obstacle(map, &var);

    var.x = 45;
    var.y = 45;
    mlx_key_hook(var.win, key_hook, &var);
    mlx_loop(var.mlx);
}