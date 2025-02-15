/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:54:19 by kel-mous          #+#    #+#             */
/*   Updated: 2024/11/23 14:54:22 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	ft_init_flags(t_flag *params)
{
	if (params != NULL)
	{
		params->zero = false;
		params->minus = false;
		params->plus = false;
		params->precision = 0;
		params->width = 0;
		params->space = false;
		params->hashtag = false;
		params->specifier = 1;
		params->precision_exist = false;
		params->negative = false;
	}
}
