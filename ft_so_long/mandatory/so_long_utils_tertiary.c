#include "so_long.h"

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

void print_moves(t_vars *var)
{
    char *str_move_count;

    str_move_count = ft_strjoin_px("moves: ", ft_itoa(var->count), 2);
    if (str_move_count == NULL)
        (display_err(MLC_ERR), quit(var), exit(0));
    write(1, str_move_count, ft_strlen(str_move_count));
	write(1, "\n", 1);
    free(str_move_count);
}

void display_err(char *str)
{
    write(1, str, ft_strlen(str));
}