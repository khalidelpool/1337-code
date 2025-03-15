#include "so_long.h"

int ocurrence(t_vars *var, char c)
{
	int y;
	int x;
	int result;

	y = 0;
	result = 0;
	while (var->map[y])
	{
		x = 0;
		while (var->map[y][x])
		{
			if (var->map[y][x] == c)
				result++;
			x++;
		}
		y++;
	}
	return (result);
}

int	*find_c(t_vars *var, char c, int *pos)
{
    for (int y = 0; var->map[y]; y++)
    {
        for(int x = 0; var->map[y][x]; x++)
        {
            if (var->map[y][x] == c)
            {
                if (pos != NULL)
                {
                    pos[0] = x;
                    pos[1] = y;
					return (pos);
                }
				return (var->pos);
            }
        }
    }
    return (NULL);
}

int in_list(t_queue *queue, int *pos)
{
    while (queue)
    {
        if (queue->pos[0] == pos[0] && queue->pos[1] == pos[1])
            return (1);
        queue = queue->next;
    }
    return (0);
}

void next_to(t_vars *var, t_queue *node, int bros[5][2])
{
    int moves[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int i = 0;
    int j = 0;
    int x;
    int y;

    while (i < 4)
    {
        x = node->pos[0] + moves[i][0];
        y = node->pos[1] + moves[i][1];
        if (x < var->hgt && y < var->wdt && x > -1 && y > -1)
        {
            if (var->map[y][x] != '1')
            {
                bros[j][0] = x;
                bros[j][1] = y;
                j++;
            }
        }
        i++;
    }
    bros[j][0] = -1;
    free(node);
}

int ate_all(t_vars *var)
{
    int pos[2];

    pos[1] = 0;
    while (var->map[pos[1]])
    {
        pos[0] = 0;
        while (var->map[pos[1]][pos[0]])
        {
            if ((var->map[pos[1]][pos[0]] == 'C' || var->map[pos[1]][pos[0]] == 'E') && !in_list(var->visited, pos))
            {
                return (0);
            }
            pos[0]++;
        }
        pos[1]++;
    }
    return (1);
}
