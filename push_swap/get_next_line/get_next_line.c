/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 19:35:38 by kel-mous          #+#    #+#             */
/*   Updated: 2024/12/21 19:42:54 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*ft_strdup(const char *s, int start, int length)
{
	char	*dup;

	dup = malloc((length + 1) * sizeof(char));
	if (dup == 0)
		return (0);
	ft_memcpy(dup, s + start, length);
	dup[length] = 0;
	return (dup);
}

char	*ft_strjoin(char *str, char *buff)
{
	char	*result;
	int		len1;
	int		len2;

	if (!str)
		str = ft_strdup("", 0, 0);
	len1 = ft_strlen(str);
	len2 = ft_strlen(buff);
	result = malloc((len1 + len2 + 1) * sizeof(char));
	if (result == NULL)
	{
		free(str);
		free(buff);
		return (NULL);
	}
	ft_memcpy(result, str, len1);
	ft_memcpy(result + len1, buff, len2);
	result[len1 + len2] = 0;
	free(str);
	free(buff);
	return (result);
}

char	*ft_split(char **str, int position)
{
	char	*result;
	char	*remaining;
	int		len;

	len = ft_strlen(*str);
	result = ft_strdup(*str, 0, position);
	if (result == NULL)
		return (NULL);
	remaining = ft_strdup(*str, position, len - position);
	if (remaining == NULL)
	{
		free(result);
		return (NULL);
	}
	free(*str);
	*str = remaining;
	return (result);
}

char	*compute(char **str, int fd)
{
	int		len;
	char	*buff;

	while (1)
	{
		if (*str && ft_findchar(*str, '\n', &len) > -1)
		{
			return (ft_split(str, len));
		}
		buff = ft_calloc((size_t)BUFFER_SIZE + 1, sizeof(char));
		if (read(fd, buff, BUFFER_SIZE) < 1)
		{
			free(buff);
			if (*str && (*str)[0] != 0)
			{
				buff = *str;
				*str = NULL;
				return (buff);
			}
			return (NULL);
		}
		*str = ft_strjoin(*str, buff);
		if (!(*str))
			return (NULL);
	}
}

char	*get_next_line(int fd)
{
	static char	*result;
	char		*str;

	if (fd < 0 || fd > 1024)
		return (NULL);
	str = compute(&result, fd);
	if (str == 0)
	{
		if (result != NULL)
		{
			free(result);
			result = NULL;
		}
		return (NULL);
	}
	return (str);
}
