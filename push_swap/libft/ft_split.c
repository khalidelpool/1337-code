/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: kel-mous <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/11/04 18:24:36 by kel-mous		  #+#	#+#			 */
/*   Updated: 2024/11/04 20:56:41 by kel-mous         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */
#include "libft.h"

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

static char	**free_arr(char ***ptr, int k)
{
	while (k >= 0)
		free((*ptr)[k--]);
	free(*ptr);
	return ((0));
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
		return ((0));
	while (k < count_words(s, c, 0))
	{
		j = 0;
		while (s[i] == c)
			i++;
		while (s[i + j] != c && s[i + j])
			j++;
		ptr[k] = ft_substr(s, i, j);
		if (!ptr[k])
			return ((free_arr(&ptr, k - 1)));
		i = i + j;
		k++;
	}
	return ((ptr));
}
