/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:54:53 by kel-mous          #+#    #+#             */
/*   Updated: 2025/03/17 10:54:56 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef SO_LONG_H
# define SO_LONG_H

# include "/usr/include/minilibx-linux/mlx.h"
# include "../projects/get_next_line.h"

# define ESC			65307
# define XK_LEFT		65361
# define XK_UP			65362
# define XK_RIGHT		65363
# define XK_DOWN		65364
# define BKGR			"./textures/bkgr.xpm"
# define FOOD			"./textures/food.xpm"
# define ROCK 			"./textures/rock.xpm"
# define EXIT 			"./textures/exit.xpm"
# define PLYR 			"./textures/plyr.xpm"
# define PLEX 			"./textures/plex.xpm"
# define MLC_ERR		"Error\nMalloc failed\n"
# define WRG_PTH		"Error\nNo valid path!\n"
# define MAP_ERR		"Error\ninvalide map file\n"
# define OPN_ERR		"Error\nCouldn't open file\n"
# define PRM_ERR		"Error\nusage: program *.ber\n"
# define IMG_ERR		"Error\nFailed to load textures!\n"
# define PTH_ERR		"Error\nfailed while checking path\n"

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_queue
{
	int				pos[2];
	struct s_queue	*next;
}	t_queue;

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		wdt;
	int		hgt;
}				t_img;

typedef struct s_vars {
	void	*mlx;
	void	*win;
	t_img	bkgr;
	t_img	exit;
	t_img	food;
	t_img	plyr;
	t_img	plex;
	t_img	rock;
	char	*map[25];
	int		wdt;
	int		hgt;
	int		bksz;
	int		count;
	int		pos[2];
	int		random;
	int		last_move;
	int		curr_frame;
	t_queue	*queue;
	t_queue	*visited;
}				t_vars;

char	*ft_itoa(int n);
int		ft_isalnum(int c);
void	quit(t_vars *var);
int		destroy(t_vars *var);
int		ate_all(t_vars *var);
void	ft_putstr(char *str);
void	check_map(t_vars *var);
void	draw_map(t_vars *var);
t_queue	*pop(t_queue **queue);
void	print_moves(t_vars *var);
void	q_clear(t_queue **queue);
size_t	ft_strlen(const char *s);
int		check_file_name(char *file);
void	init_textures(t_vars *var);
void	ft_bzero(void *s, size_t n);
int		in_set(char c, char const *set);
int		ocurrence(t_vars *var, char c);
int		get_next_move(int i, int choice);
int		key_hook(int keysym, t_vars *var);
void	*loader(t_vars *var, char *path);
int		put(t_queue **queue, int x, int y);
int		in_list(t_queue *queue, int *pos);
int		*find_c(t_vars *var, char c, int *pos);
void	update_map(t_vars *var, int y, int x);
void	str_replace(char *str, char c, char n);
int		drawer(t_vars *var, void *img, int x, int y);
char	*ft_strjoin_px(char *str, char *buff, int choice);
void	next_to(t_vars *var, t_queue *node, int bros[5][2]);

#endif
