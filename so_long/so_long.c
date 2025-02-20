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

#define WIDTH 350
#define HEIGHT 600

typedef struct s_img
{
    void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}t_img;

typedef struct s_data
{
    t_img img;
}t_data;


void start()
{
    void *mlx;
    void *mlx_window;
    t_img img;

    mlx = mlx_init();
    mlx_window = mlx_new_window(mlx, WIDTH, HEIGHT, "My First Window!");
    img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    

    mlx_loop(mlx);
}

int main(int ac, char **av)
{
    if (ac < 2)
        printf("enter map as *.ber file!\n"), exit(0);
    int map_fd = open(av[1], O_RDONLY);
    char *line = get_next_line(map_fd);
    printf("%s", line);
    free(line);
    return (0);
}
