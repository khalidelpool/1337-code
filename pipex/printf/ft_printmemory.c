/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printmemory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <kel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:30:37 by kel-mous          #+#    #+#             */
/*   Updated: 2024/11/23 15:33:50 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static char	*ft_memhexa(unsigned long n, char *base)
{
	char	*result;

	result = 0;
	while (1)
	{
		result = ft_append(result, base[n % 16], 0);
		n /= 16;
		if (!n)
			break ;
	}
	return (result);
}

char	*ft_printmemory(void *addr)
{
	char	*ptr;

	if (!addr)
		return (NULL);
	ptr = ft_memhexa((unsigned long) addr, "0123456789abcdef");
	ptr = ft_append(ptr, 'x', 0);
	ptr = ft_append(ptr, '0', 0);
	return (ptr);
}
