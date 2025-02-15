/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:29:16 by kel-mous          #+#    #+#             */
/*   Updated: 2024/11/23 14:29:24 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

long	ft_atoi(char **nptr)
{
	long	result;

	result = 0;
	while (ft_isdigit(**nptr) && result < 2147483648)
	{
		result = result * 10 + **nptr - '0';
		(*nptr)++;
	}
	return (result);
}
