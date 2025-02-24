#include "minilibx-linux/mlx.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include "get_next_line.h"
#include "get_next_line.c"
#include "get_next_line_utils.c"

#define WIDTH 450
#define HEIGHT 800

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int power(int base, int power)
{
	int result = 1;
	
	while(power-- > 0)
		result *= base;
	return (result);
}

void circle(t_data *img)
{
	int r = WIDTH * 0.1;
	int xc = HEIGHT / 2;
	int yc = WIDTH / 2;

	for (int y = yc - r; y < yc + r; y++)
	{
		for(int x = xc - r; x < xc + r; x++)
		{
			if (power(x - xc, 2) + power(y - yc, 2) <= power(r, 2))
				my_mlx_pixel_put(img, x, y, 0x00808080);
		}
	}
}

typedef struct	s_vars {
    void	*mlx;
    void	*win;
}				t_vars;

int	closer(int keycode, t_vars *vars)
{
	printf("key is: %d\n", keycode);
    mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
    return (0);
}

int key_hook(int keycode, t_vars *vars)
{
	printf("the keycode is: %d, the char is: %c\n", keycode, keycode);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_vars *vars)
{
	printf("the button is: %d\nthe positions is: (%d,%d)\n", button, x, y);
	return (0);
}

int main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_vars	vars;
	void *image;
    char *relative_path = "./grass.xpm";
    int img_width;
    int img_height;
	t_data background;

	mlx = mlx_init();
	vars.mlx = mlx;
	mlx_win = mlx_new_window(mlx, HEIGHT, WIDTH, "Hello world!");
	vars.win = mlx_win;
	img.img = mlx_new_image(mlx, HEIGHT, WIDTH);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);

	background.img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
	background.addr = mlx_get_data_addr(background.img, &background.bits_per_pixel, &background.line_length,
								&background.endian);
    if (!background.img)
        return (1); // Handle failure if image loading fails

	for(int y = 20; y < 200; y++)
    {
        for(int x = 20; x < 200; x++)
        {

			my_mlx_pixel_put(&background, x, y, 0);
            // mlx_pixel_put(mlx, mlx_window, x, y, rand() % 0x1000000);
        }
    }
	mlx_put_image_to_window(mlx, vars.win, background.img, 0, 0);
	my_mlx_pixel_put(&background, 5, 5, 0x00000000);

	sleep(1);
	for(int y = 20; y < 200; y++)
    {
        for(int x = 20; x < 200; x++)
        {
			my_mlx_pixel_put(&background, x, y, rand() % 0x1000000);
            // mlx_pixel_put(mlx, mlx_window, x, y, rand() % 0x1000000);
        }
    }
	mlx_put_image_to_window(mlx, vars.win, background.img, 0, 0);

	// mlx_hook(vars.win, 2, (1L << 0), closer, &vars);
	
	mlx_key_hook(mlx_win, key_hook, &vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	
	// circle(&img);
    // mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);

    mlx_loop(mlx);
}
