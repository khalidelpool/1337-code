#include "so_long_bonus.h"

t_queue	*pop(t_queue **queue)
{
	t_queue *node;

	if (queue == NULL || (*queue) == NULL)
		return (NULL);
	node = *queue;
	*queue = node->next;
	return (node);
}

int	put(t_queue **queue, int x, int y)
{
	t_queue	*last;
	t_queue	*new;

	if (queue == NULL)
		return (0);
	new = malloc(sizeof(t_queue));
	if (new == NULL)
		return (1);
	new->pos[0] = x;
	new->pos[1] = y;
	new->next = NULL;
	last = *queue;
	if (*queue == NULL)
	{
		*queue = new;
		return (0);
	}
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = new;
	new->next = NULL;
	return (0);
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

void print_moves(t_vars *var)
{
    char *str_move_count;

    str_move_count = ft_strjoin_px("moves: ", ft_itoa(var->count), 2);
    if (str_move_count == NULL)
        (printf(MLC_ERR), quit(var), exit(0));
    mlx_string_put(var->mlx, var->win, 22, 26, 0xffffffff, str_move_count);
    free(str_move_count);
}