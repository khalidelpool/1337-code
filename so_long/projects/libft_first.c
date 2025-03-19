/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_first.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 21:36:05 by kel-mous          #+#    #+#             */
/*   Updated: 2025/03/17 21:36:09 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../mandatory/so_long.h"

int	ft_isalnum(int c)
{
	if ((c > 64 && c < 91) || (c > 96 && c < 123) || (c >= '0' && c <= '9'))
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

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return ((i));
}

void	str_replace(char *str, char c, char n)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			str[i] = n;
		i++;
	}
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
