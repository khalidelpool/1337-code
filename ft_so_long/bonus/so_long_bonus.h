#ifndef SO_LONG_H
#define SO_LONG_H

// #include "/usr/include/minilibx-linux/mlx.h"
#include "../minilibx-linux/mlx.h"
#include "../projects/get_next_line.h"

#define ESC			65307
#define XK_Left		65361
#define XK_Up		65362
#define XK_Right	65363
#define XK_Down		65364
#define new_win		mlx_new_window
#define load		mlx_xpm_file_to_image
#define BKGR		"./textures/bkgr.xpm"
#define FOOD		"./textures/food.xpm"
#define ROCK 		"./textures/rock.xpm"
#define EXIT 		"./textures/exit.xpm"
#define VILL 		"./textures/vill.xpm"
#define ANEX 		"./textures/anex.xpm"
#define ANIM 		"./textures/anim.xpm"
#define MAP_ERR		"Error\ninvalide map file\n"
#define PTH_ERR		"Error\nfailed while checking path\n"
#define WRG_PTH		"Error\nNo valid path!\n"
#define IMG_ERR		"Failed to load textures!\n"
#define MLC_ERR		"Error\nMalloc failed\n"

typedef struct s_queue
{
	int				pos[2];
	struct s_queue	*next;
}	t_queue;

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
	t_img	anex;
	t_img	anim;
	t_img   bkgr;
	t_img   exit;
	t_img   food;
    t_img   plyr;
    t_img   rock;
	t_img	vill;
    char    *map[25];
    int     wdt;
    int     hgt;
	int		bksz;
    int     count;
	int		pos[2];
	int		random;
	int		last_move;
	int		curr_frame;
	t_queue *queue;
    t_queue *visited;
}				t_vars;

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void	ft_bzero(void *s, size_t n);
int		in_set(char c, char const *set);
void	str_replace(char *str, char c, char n);
size_t	ft_strlen(const char *s);
int		check_file_name(char *file);
void	check_map(t_vars *var);
int		ocurrence(t_vars *var, char c);
int		*find_c(t_vars *var, char c, int *pos);
t_queue	*pop(t_queue **queue);
int		put(t_queue **queue, int x, int y);
void	init_textures(t_vars *var);
int		key_hook(int keysym, t_vars *var);
int		destroy(t_vars *var);
int		render_next_frame(t_vars *var);
void	print_moves(t_vars *var);
void	update_map(t_vars *var, int y, int x);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int     my_mlx_pixel_get(t_img *img, int x, int y);
int		in_list(t_queue *queue, int *pos);
void	next_to(t_vars *var, t_queue *node, int bros[5][2]);
int		ate_all(t_vars *var);
void	draw_map(t_vars *var);
void	quit(t_vars *var);
void	q_clear(t_queue **queue);
void	init_textures(t_vars *var);
void	change_frame(t_vars *var);
char	*ft_strjoin_px(char *str, char *buff, int choice);
char	*ft_itoa(int n);
int		ft_isalnum(int c);

#endif
