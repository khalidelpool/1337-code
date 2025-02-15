/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <kel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:28:31 by kel-mous          #+#    #+#             */
/*   Updated: 2024/11/23 15:29:57 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static int	ft_parse_format(const char **s, va_list args, t_flag *params)
{
	char	*temp;
	int		res;

	res = 0;
	ft_init_flags(params);
	ft_struct((char **)s, params);
	if (**s == 'c')
	{
		res = ft_char(va_arg(args, int), params->width, params->minus);
		return (res);
	}
	temp = ft_format(*s, args, params);
	temp = ft_flags(temp, params);
	res += ft_width(temp, params);
	return (res);
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	t_flag	params;
	int		result;

	if (!s || !ft_overflow((char *)s))
		return (-1);
	result = 0;
	va_start(args, s);
	while (*s)
	{
		if (*s == '%')
		{
			if (ft_order((char *)++s) && (*s && *s != '%'))
				result += ft_parse_format(&s, args, &params);
			else
				ft_putchar((result++, '%'));
		}
		else
			ft_putchar((result++, *s));
		s++;
	}
	va_end(args);
	return (result);
}
