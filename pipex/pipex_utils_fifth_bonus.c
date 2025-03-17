/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_fifth.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 00:05:59 by kel-mous          #+#    #+#             */
/*   Updated: 2025/03/17 00:06:02 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	c = (unsigned char) c;
	while (s[i])
	{
		if (s[i] == c)
			return ((((char *)(s + i))));
		i++;
	}
	if (c == '\0')
		return ((((char *)(s + i))));
	return ((0));
}

void	ft_putstr(char *str, int fd)
{
	while (*str)
	{
		write(fd, str++, 1);
	}
}

char	*get_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp("PATH=", envp[i], 5))
			return (&envp[i][5]);
		i++;
	}
	return (NULL);
}

int	arr_size(char **ptr)
{
	int	size;

	size = 0;
	if (!ptr)
		return (0);
	while (ptr[size])
		size++;
	return (size);
}
