/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <kel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:39:33 by kel-mous          #+#    #+#             */
/*   Updated: 2024/11/23 15:41:44 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	ft_struct(char **str, t_flag *params)
{
	while (**str && in_set(**str, "-+#0 "))
	{
		if (**str == '+')
			params->plus = true;
		else if (**str == '-')
			params->minus = true;
		else if (**str == ' ' )
			params->space = true;
		else if (**str == '#')
			params->hashtag = true;
		else if (**str == '0')
			params->zero = true;
		(*str)++;
	}
	params->width = ft_atoi(str);
	if (**str == '.')
	{
		params->precision_exist = true;
		(*str)++;
		params->precision = ft_atoi(str);
	}
}
