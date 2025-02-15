/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:26:24 by kel-mous          #+#    #+#             */
/*   Updated: 2024/11/23 14:26:31 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

char	*ft_append(char *org, char c, int position)
{
	char	*result;
	size_t	size;

	if (!org)
	{
		result = ft_calloc(2, sizeof(char));
		ft_memmove(result, &c, 1);
		result[1] = 0;
		return (result);
	}
	size = ft_strlen(org);
	result = ft_calloc((size + 2), sizeof(char));
	ft_memmove(result, org, position);
	ft_memmove(result + position, &c, 1);
	ft_memmove(result + position + 1, org + position, size - position);
	result[size + 1] = 0;
	free(org);
	return (result);
}
