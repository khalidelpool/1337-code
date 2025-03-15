#include "so_long_bonus.h"

int check_file_name(char *file)
{
    int size;

    size = ft_strlen(file);
    if (file[size - 1] == 'r' && file[size - 2] == 'e' && file[size - 3] == 'b'
        && file[size - 4] == '.' && ft_isalnum(file[size - 5]))
        return (1);
    return (0);
}

int destroy(t_vars *var)
{
    quit(var);
    exit(0);
}

void	q_clear(t_queue **queue)
{
	t_queue	*curr;
	t_queue	*temp;

	if (!queue)
		return ;
	curr = *queue;
	while (curr != NULL)
	{
		temp = curr;
		curr = curr->next;
		free(temp);
	}
	*queue = NULL;
}

void quit(t_vars *var)
{
    int y;

    y = 0;
    while (var->map[y])
        free(var->map[y++]);
    q_clear(&var->queue);
    q_clear(&var->visited);
    if (var->food.img)
    {
        mlx_destroy_image(var->mlx, var->anex.img);
        mlx_destroy_image(var->mlx, var->anim.img);
        mlx_destroy_image(var->mlx, var->bkgr.img);
        mlx_destroy_image(var->mlx, var->exit.img);
        mlx_destroy_image(var->mlx, var->food.img);
        mlx_destroy_image(var->mlx, var->plyr.img);
        mlx_destroy_image(var->mlx, var->rock.img);
        mlx_destroy_image(var->mlx, var->vill.img);
    }
    if (var->win)
        mlx_destroy_window(var->mlx, var->win);
    if (var->mlx)
    {
        mlx_destroy_display(var->mlx);
        free(var->mlx);
    }
}
