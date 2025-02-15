/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:34:05 by kel-mous          #+#    #+#             */
/*   Updated: 2024/11/23 14:34:10 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

char	*ft_flags(char *ptr, t_flag *params)
{
	if (!ptr)
		return (NULL);
	if (params->negative == true)
		ptr = ft_append(ptr, '-', 0);
	if (params->plus && !params->negative
		&& params->specifier > 5 && ptr[0] != '+')
	{
		return (ft_append(ptr, '+', 0));
	}
	if (params->space && !params->negative && !params->plus
		&& params->specifier > 5 && ptr[0] != ' ')
	{
		return (ft_append(ptr, ' ', 0));
	}
	if (params->hashtag && params->specifier == 4)
	{
		ptr = ft_append(ptr, '0', 0);
		return (ft_append(ptr, 'x', 1));
	}
	if (params->hashtag && params->specifier == 5)
	{
		ptr = ft_append(ptr, '0', 0);
		return (ft_append(ptr, 'X', 1));
	}
	return (ptr);
}
