/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_overflow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <kel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:10:49 by kel-mous          #+#    #+#             */
/*   Updated: 2024/11/23 15:17:17 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_overflow(char *s)
{
	while (*s)
	{
		if (*s == '%' && ft_order(++s))
		{
			while (*s && (!ft_isdigit(*s) || *s == '0'))
				s++;
			if (*s && ft_isdigit(*s) && ft_atoi(&s) > 2147483647)
				return (0);
			if (*s && *s == '.' && ft_isdigit(*(++s + 1))
				&& ft_atoi(&s) > 2147483647)
				return (0);
		}
		s++;
	}
	return (1);
}
