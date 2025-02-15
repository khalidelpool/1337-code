/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 21:34:08 by kel-mous          #+#    #+#             */
/*   Updated: 2024/11/04 21:35:36 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*result;

	i = 0;
	result = 0;
	c = (unsigned char) c;
	while (s[i])
	{
		if (s[i] == c)
			result = ((char *)(s + i));
		i++;
	}
	if (c == 0)
		return ((((char *)(s + i))));
	return ((result));
}
