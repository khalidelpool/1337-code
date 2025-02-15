/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_precision.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <kel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:23:06 by kel-mous          #+#    #+#             */
/*   Updated: 2024/11/23 15:26:41 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static char	*precision_2(int digits, char *str, t_flag *params)
{
	size_t	len;
	char	*result;

	if (!digits && params->specifier > 2 && params->specifier < 8
		&& str[0] == '0' && str[1] == '\0')
	{
		free(str);
		return (ft_strdup(""));
	}
	len = strlen(str);
	result = ft_calloc((digits + 1), sizeof(char));
	ft_memset(result, '0', digits);
	ft_memmove(result + (digits - len), str, len + 1);
	free(str);
	return (result);
}

char	*ft_precision(t_flag *params, char *str)
{
	char	*result;
	size_t	len;
	size_t	digits;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	result = str;
	digits = params->precision;
	if (digits || params->precision_exist)
	{
		params->zero = false;
		if ((digits > len && params->specifier > 2)
			|| (!digits && params->specifier > 2 && params->specifier < 8
				&& str[0] == '0' && str[1] == '\0'))
			return (precision_2(digits, str, params));
		if (digits < len && params->specifier == 2)
		{
			result = ft_calloc((digits + 1), sizeof(char));
			ft_memmove(result, str, digits);
			result[digits] = 0;
			free(str);
		}
	}
	return (result);
}
