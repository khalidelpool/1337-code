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

#define WIDTH 999999999
#define HEIGHT 999999999

void start()
{
    void *mlx;
    void *mlx_window;

    srand(time(NULL));
    mlx = mlx_init();
    mlx_window = mlx_new_window(mlx, WIDTH, HEIGHT, "My First Window!");
    
    for(int y = HEIGHT * 0.1; y < HEIGHT * 0.9; y++)
    {
        for(int x = WIDTH * 0.1; x < WIDTH * 0.9; x++)
        {
            mlx_pixel_put(mlx, mlx_window, x, y, rand() % 0x1000000);
        }
    }
    mlx_string_put(mlx, mlx_window, WIDTH * 0.8, HEIGHT * 0.95, 0xffffff, "My pollock");
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
