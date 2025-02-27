#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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

int find_c(t_vars *var, char c, int change)
{
    for (int y = 0; var->map[y]; y++)
    {
        for(int x = 0; var->map[y][x]; x++)
        {
            if (var->map[y][x] == c)
            {
                if (change)
                {
                    var->y = y;
                    var->x = x;
                }
                return (1);
            }
        }
    }
    return (0);
}