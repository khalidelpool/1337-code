/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: kel-mous <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/11/04 17:27:26 by kel-mous		  #+#	#+#			 */
/*   Updated: 2024/11/08 15:18:11 by kel-mous         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */
#include "libft.h"

static void	set_up(char *result, int *size, long *r)
{
	long	m;

	if (*r < 0)
	{
		*r = -(*r);
		result[0] = '-';
		(*size)++;
	}
	m = *r;
	while (m > 9 && (*size)++)
		m /= 10;
	result[*size] = '\0';
}

static int	int_size(int n)
{
	int	size;

	size = 1;
	if (n < 0)
		size = 2;
	while (1)
	{
		n /= 10;
		size++;
		if (!n)
			return (size);
	}
}

char	*ft_itoa(int n)
{
	char	*result;
	int		size;
	long	r;

	result = malloc(sizeof(char) * int_size(n));
	r = n;
	size = 1;
	if (!result)
		return (((0)));
	set_up(result, &size, &r);
	result[size] = '\0';
	while (1)
	{
		result[size-- - 1] = r % 10 + 48;
		r /= 10;
		if (!r)
			break ;
	}
	return (((result)));
}
