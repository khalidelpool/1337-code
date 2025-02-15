/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_order.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <kel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:01:34 by kel-mous          #+#    #+#             */
/*   Updated: 2024/11/23 15:58:17 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_order(char *s)
{
	size_t	i;

	i = 0;
	while (in_set(s[i], "-+#0 "))
		i++;
	while (isdigit(s[i]))
		i++;
	if (s[i] == '.')
		i++;
	while (isdigit(s[i]))
		i++;
	if (in_set(s[i], "%cspdiuxX"))
		return (1);
	return (0);
}
