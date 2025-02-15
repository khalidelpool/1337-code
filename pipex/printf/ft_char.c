/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:32:45 by kel-mous          #+#    #+#             */
/*   Updated: 2024/11/23 14:32:48 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_char(int c, int width, bool minus)
{
	int	count;

	count = 1;
	if (!minus)
	{
		while (width > 1)
		{
			ft_putchar(' ');
			width--;
			count++;
		}
		ft_putchar(c);
	}
	else
	{
		ft_putchar(c);
		while (width > 1)
		{
			ft_putchar(' ');
			width--;
			count++;
		}
	}
	return (count);
}
