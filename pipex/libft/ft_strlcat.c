/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 21:03:52 by kel-mous          #+#    #+#             */
/*   Updated: 2024/11/04 21:05:29 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <string.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	len;

	if (size == 0 && (!dst || !src))
		return (0);
	i = 0;
	len = ft_strlen(dst);
	if (size < len)
	{
		return (((size + ft_strlen(src))));
	}
	while (src[i] && i + len + 1 < size)
	{
		dst[i + len] = src[i];
		i++;
	}
	dst[i + len] = 0;
	return (((len + ft_strlen(src))));
}
