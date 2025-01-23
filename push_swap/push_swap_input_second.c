#include "push_swap.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return ((i));
}

int ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return ((1));
	return ((0));
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	i;

	if (!s)
		return (0);
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - (size_t) start;
	if (ft_strlen(s) < start)
		len = 0;
	substring = malloc((len + 1) * sizeof(char));
	if (substring == 0)
		return ((0));
	i = 0;
	while (i < len)
	{
		substring[i] = s[start + i];
		i++;
	}
	substring[i] = 0;
	return ((substring));
}

long	ft_atoy(const char *nptr, long result, int sign)
{
	while ((*nptr > 8 && *nptr < 14) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
		if (!nptr[0])
			return (MAX);
	}
	else if (!ft_isdigit(*nptr))
		return (MAX);
	while (ft_isdigit(*nptr))
	{
		result = result * 10 + *nptr - 48;
		if (result > MAX || (result == MAX && sign == 1))
			return (MAX);
		nptr++;
	}
	if (!((*nptr > 8 && *nptr < 14) || *nptr == 32 || *nptr == 0))
		return (MAX);
	return (((result * sign)));
}
