/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <kel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:56:42 by kel-mous          #+#    #+#             */
/*   Updated: 2024/11/23 14:57:00 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	num_len(long int nb)
{
	int	i;

	i = 0;
	if (nb == 0)
	{
		i++;
	}
	if (nb < 0)
	{
		nb = -nb;
	}
	while (nb)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n, t_flag *params)
{
	char		*res;
	int			len;
	long int	nb;

	nb = (long int)n;
	len = num_len(nb);
	res = malloc(len * sizeof(char) + 1);
	if (!res)
		return (NULL);
	res[len] = 0;
	len--;
	if (!nb)
		res[0] = '0';
	else if (nb < 0)
	{
		params->negative = true;
		nb = -nb;
	}
	while (nb)
	{
		res[len--] = (nb % 10 + '0');
		nb = nb / 10;
	}
	return (res);
}
