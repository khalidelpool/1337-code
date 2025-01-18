/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 21:05:42 by kel-mous          #+#    #+#             */
/*   Updated: 2024/11/04 21:06:33 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size != 0)
	{
		while (i < (size - 1))
		{
			if (src[i] != '\0')
			{
				dst[i] = src[i];
				i++;
			}
			else
			{
				break ;
			}
		}
		dst[i] = '\0';
	}
	return (((ft_strlen(src))));
}
