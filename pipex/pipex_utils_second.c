/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_second.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 23:59:42 by kel-mous          #+#    #+#             */
/*   Updated: 2025/03/16 23:59:46 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i] || (s1[i] == 0 && s2[i] == 0))
			return (((unsigned char)s1[i] - (unsigned char)s2[i]));
		i++;
	}
	return ((0));
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return ((i));
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

char	*ft_append(char **org, char c, int position)
{
	char	*result;
	size_t	size;

	if (position == -1)
		position = ft_strlen(org[0]);
	if (org[0] == NULL)
	{
		org[0] = ft_strdup("");
		if (org[0] == NULL)
			return (NULL);
	}
	size = ft_strlen(org[0]);
	result = ft_calloc((size + 2), sizeof(char));
	if (result == NULL)
		return (NULL);
	ft_memcpy(result, org[0], position);
	ft_memcpy(result + position, &c, 1);
	ft_memcpy(result + position + 1, org[0] + position, size - position);
	free(org[0]);
	org[0] = result;
	return (result);
}
