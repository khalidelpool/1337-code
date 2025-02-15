/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:45:13 by kel-mous          #+#    #+#             */
/*   Updated: 2024/11/23 14:45:33 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

char	*ft_format(const char *format, va_list args, t_flag *params)
{
	char	*ptr;

	ptr = 0;
	if (++(params->specifier) && format[0] == 's')
		ptr = ft_precision(params, ft_strdup(va_arg(args, char *)));
	else if (++(params->specifier) && format[0] == 'u')
		ptr = ft_precision(params,
				ft_unsigned_itoa(va_arg(args, unsigned int)));
	else if (++(params->specifier) && format[0] == 'x')
		ptr = ft_precision(params,
				ft_hexa(va_arg(args, unsigned int),
					"0123456789abcdef", params));
	else if (++(params->specifier) && format[0] == 'X')
		ptr = ft_precision(params,
				ft_hexa(va_arg(args, unsigned int),
					"0123456789ABCDEF", params));
	else if (++(params->specifier) && format[0] == 'd')
		ptr = ft_precision(params, ft_itoa(va_arg(args, int), params));
	else if (++(params->specifier) && format[0] == 'i')
		ptr = ft_precision(params, ft_itoa(va_arg(args, int), params));
	else if (++(params->specifier) && format[0] == 'p')
		ptr = ft_precision(params, ft_printmemory(va_arg(args, void *)));
	return (ptr);
}
