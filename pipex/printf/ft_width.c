/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_width.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:47:22 by kel-mous          #+#    #+#             */
/*   Updated: 2024/11/23 15:47:26 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static int	print_shiftright(char *ptr, t_flag *params, char c, int len)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if ((ptr[0] == '+' || ptr[0] == '-' || ptr[0] == ' ') && c == '0')
	{
		ft_putchar(ptr[0]);
		count++;
		ptr++;
	}
	if ((ptr[0] == '0' && ptr[1] == 'x') && c == '0')
	{
		ft_putstr("0x");
		ptr += 2;
		count += 2;
	}
	while (params->width-- > len)
	{
		ft_putchar(c);
		count++;
	}
	while (ptr[i])
		ft_putchar((count++, ptr[i++]));
	return (count);
}

static int	print_shiftleft(char *ptr, t_flag *params, char c)
{
	int	count;

	count = 0;
	while (ptr[count])
	{
		ft_putchar(ptr[count]);
		count++;
		params->width--;
	}
	while (params->width > 0)
	{
		ft_putchar(c);
		params->width--;
		count++;
	}
	return (count);
}

int	ft_width(char *ptr, t_flag *params)
{
	int	len;

	if (!ptr)
	{
		ptr = ft_null(params);
	}
	len = ft_strlen(ptr);
	if (params->width > len)
	{
		if (params->minus == false && params->zero && params->specifier > 2)
			len = print_shiftright(ptr, params, '0', len);
		else if (params->minus == false)
			len = print_shiftright(ptr, params, ' ', len);
		else
			len = print_shiftleft(ptr, params, ' ');
	}
	else
	{
		ft_putstr(ptr);
	}
	free(ptr);
	return (len);
}
