/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 19:52:47 by kel-mous          #+#    #+#             */
/*   Updated: 2024/12/21 19:52:51 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

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

int	ft_findchar(char *str, char to_find, int *len)
{
	*len = 0;
	while (str[*len])
	{
		if (str[(*len)++] == to_find)
		{
			return (*len);
		}
	}
	return (-1);
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

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb && size > __SIZE_MAX__ / nmemb)
		return (0);
	ptr = malloc(nmemb * size);
	if (ptr == 0)
		return (((0)));
	ft_bzero(ptr, nmemb * size);
	return (((ptr)));
}
