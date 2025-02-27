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

#define load		mlx_xpm_file_to_image
#define XK_Left		0xff51  /* Move left, left arrow */
#define XK_Up		0xff52  /* Move up, up arrow */
#define XK_Right	0xff53  /* Move right, right arrow */
#define XK_Down		0xff54  /* Move down, down arrow */

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
    char    *map[33];
    int     x;
    int     y;
    int     wdt;
    int     hgt;
    int     count;
}				t_vars;

void str_replace(char *str, char c, char n)
{
    int i = 0;

    while (str[i])
    {
        if (str[i] == c)
            str[i] = n;
        i++;
    }
}

int find(char **map, char c)
{
    for (int y = 0; map[y]; y++)
    {
        for(int x = 0; map[y][x]; x++)
        {
            if (map[y][x] == c)
            {
                return (1);
            }
        }
    }
    return (0);
}

void check_map(t_vars *var)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (var->map[y])
	{
		while (var->map[y][x])
		{
			if ((y == 0 || x == 0 || y == var->wdt - 1 || x == var->hgt - 1)
				&& var->map[y][x] != '1')
				(printf("invalide map file, x is: %d, y is: %d\n", x, y), exit(1));
			x++;
		}
		y++;
	}
	if (!find(var->map, 'C') || !find(var->map, 'E') || !find(var->map, 'P'))
        (printf("invalide map file\n"), exit(1));
}

void parse(t_vars *var, char *path)
{
	int fd;
	int len;
	char *line;

	fd = open(path, O_RDONLY);
	if (fd == -1)
        (perror("open"), exit(1));
	var->map[var->wdt] = get_next_line(fd);
	printf("line is: %s\n", var->map[var->wdt]);
	while (line != NULL)
	{
		str_replace(var->map[var->wdt], '\n', '\0');
		
		len = ft_strlen(line);
		if ((var->hgt == 0 || len == var->hgt) && len > 2 && len < 42)
			var->hgt = len;
		else
            (/*function to clear var*/ printf("invalide map file\n"), exit(1));
		printf("test, len is: %d\n", len);
		printf("line is: %s\n", var->map[var->wdt]);
		var->map[++(var->wdt)] = get_next_line(fd);
	}
	var->map[var->wdt] = NULL;
	printf("test\n");
	for (int y = 0; var->map[y]; y++)
    {
        for(int x = 0; var->map[y][x]; x++)
        {
            printf("%c", var->map[y][x]);
        }
		printf("\n");
    }
}

int main(int ac, char **av)
{
	t_vars var;

	if (ac != 2)
        (printf("usage: program *.ber\n"), exit(0));
	// ft_bzero(&var, sizeof(t_vars));
	var.wdt = 0;
	var.hgt = 0;
    parse(&var, av[1]);
}