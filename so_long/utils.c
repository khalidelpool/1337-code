#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define load		mlx_xpm_file_to_image
#define XK_Left		0xff51  /* Move left, left arrow */
#define XK_Up		0xff52  /* Move up, up arrow */
#define XK_Right	0xff53  /* Move right, right arrow */
#define XK_Down		0xff54  /* Move down, down arrow */
#define ESC			65307

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

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return ((i));
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*source;
	unsigned char	*destination;
	size_t			i;

	if (!dest && !src)
		return (0);
	source = (unsigned char *) src;
	destination = dest;
	i = 0;
	while (i < n)
	{
		destination[i] = source[i];
		i++;
	}
	return ((dest));
}

char	*ft_strdup(const char *s)
{
	size_t	size;
	char	*dup;

	size = ft_strlen(s) + 1;
	dup = malloc(size * sizeof(char));
	if (dup == 0)
		return ((0));
	ft_memcpy(dup, s, size);
	return ((dup));
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return ((1));
	return ((0));
}


int	ft_isalpha(int c)
{
	if ((c > 64 && c < 91) || (c > 96 && c < 123))
		return (((1)));
	return (((0)));
}

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (((1)));
	return (((0)));
}

int	in_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return ((1));
		i++;
	}
	return ((0));
}

static void	set_up(char *result, int *size, long *r)
{
	long	m;

	if (*r < 0)
	{
		*r = -(*r);
		result[0] = '-';
		(*size)++;
	}
	m = *r;
	while (m > 9 && (*size)++)
		m /= 10;
	result[*size] = '\0';
}

static int	int_size(int n)
{
	int	size;

	size = 1;
	if (n < 0)
		size = 2;
	while (1)
	{
		n /= 10;
		size++;
		if (!n)
			return (size);
	}
}

char	*ft_itoa(int n)
{
	char	*result;
	int		size;
	long	r;

	result = malloc(sizeof(char) * int_size(n));
	r = n;
	size = 1;
	if (!result)
		return (((0)));
	set_up(result, &size, &r);
	result[size] = '\0';
	while (1)
	{
		result[size-- - 1] = r % 10 + 48;
		r /= 10;
		if (!r)
			break ;
	}
	return (((result)));
}

char	*ft_strjoin_px(char *str, char *buff, int choice)
{
	char	*result;
	int		len1;
	int		len2;

	if (!str || !buff)
		return (NULL);
	len1 = ft_strlen(str);
	len2 = ft_strlen(buff);
	result = malloc((len1 + len2 + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	ft_memcpy(result, str, len1);
	ft_memcpy(result + len1, buff, len2);
	result[len1 + len2] = 0;
	if (choice == 1 || choice == 3)
		free(str);
	if (choice == 2 || choice == 3)
		free(buff);
	return (result);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = s;
	i = 0;
	while (i < n)
		ptr[i++] = '\0';
}

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

t_queue	*pop(t_queue **queue)
{
	t_queue *node;

	if (queue == NULL || (*queue) == NULL)
		return (NULL);
	node = *queue;
	*queue = node->next;
	return (node);
}

void f(int *pos)
{
	printf("(%d, %d)\n", pos[0], pos[1]);
}

void	ft_lstiter(t_queue *queue, void (*f)(int *))
{
	t_queue	*curr;

	if (!f)
		return ;
	curr = queue;
	while (curr != NULL)
	{
		f(curr->pos);
		curr = curr->next;
	}
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

// int main(){
// 	t_queue *head = NULL;
// 	put(&head, 3, 2);
// 	put(&head, 5, 7);
// 	pop(&head);
// 	pop(&head);
// 	// pop(&head);
// 	// pop(&head);
// 	// pop(&head);
// 	ft_lstiter(head, f);
// 	// printf("hello\n");
// }
