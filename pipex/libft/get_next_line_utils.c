/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 19:44:17 by kel-mous          #+#    #+#             */
/*   Updated: 2024/12/21 19:46:27 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_findchar(char *str, char to_find, int *len)
{
	*len = 0;
	while (str[*len])
	{
		if (str[(*len)++] == to_find)
		{
			return (*len);
		}
	}
	return (-1);
}
