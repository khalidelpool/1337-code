/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_second.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 21:36:47 by kel-mous          #+#    #+#             */
/*   Updated: 2025/03/17 21:36:53 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../mandatory/so_long.h"

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
