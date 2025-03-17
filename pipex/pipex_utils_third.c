/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_third.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 00:01:27 by kel-mous          #+#    #+#             */
/*   Updated: 2025/03/17 00:01:31 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

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

char	**ft_strjoin_px(char **str, char *buff, int choice)
{
	char	*result;
	int		len1;
	int		len2;

	if (!str || !(*str) || !buff)
		return (NULL);
	len1 = ft_strlen(*str);
	len2 = ft_strlen(buff);
	result = malloc((len1 + len2 + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	ft_memcpy(result, *str, len1);
	ft_memcpy(result + len1, buff, len2);
	result[len1 + len2] = 0;
	if (choice == 1 || choice == 3)
		free(*str);
	if (choice == 2 || choice == 3)
		free(buff);
	*str = result;
	return (str);
}

void	free_size(char ***ptr, int size)
{
	int	i;

	i = 0;
	while (size--)
	{
		if (ptr[0][i])
			free(ptr[0][i]);
		i++;
	}
	free(*ptr);
	return ;
}

void	free_arr(char ***ptr)
{
	int	i;

	i = 0;
	while ((*ptr)[i] != NULL)
		free((*ptr)[i++]);
	free(*ptr);
	return ;
}
