/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_forth.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 00:03:33 by kel-mous          #+#    #+#             */
/*   Updated: 2025/03/17 00:03:36 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void	del(void *content)
{
	(void)content;
}

int	at(int i, int state, int wr)
{
	return ((((i + state) % 2) * 2) + wr);
}

static int	count_words(const char *str, char c, int i)
{
	int		in_word;
	int		n;

	in_word = 0;
	n = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] != c)
		{
			if (!in_word)
			{
				in_word = 1;
				n++;
			}
		}
		else
			in_word = 0;
		i++;
	}
	return (((n)));
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

char	**ft_split(const char *s, char c)
{
	char	**ptr;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	ptr = ft_calloc((count_words(s, c, 0) + 1), sizeof(char *));
	if (!ptr || (!s && (free(ptr), 1)))
		return (NULL);
	while (k < count_words(s, c, 0))
	{
		j = 0;
		while (s[i] == c)
			i++;
		while (s[i + j] != c && s[i + j])
			j++;
		ptr[k] = ft_substr(s, i, j);
		if (!ptr[k])
			return (free_arr(&ptr), NULL);
		i = i + j;
		k++;
	}
	return ((ptr));
}
