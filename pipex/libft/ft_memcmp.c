/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_memcmp.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: kel-mous <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/11/04 18:07:15 by kel-mous		  #+#	#+#			 */
/*   Updated: 2024/11/04 18:10:51 by kel-mous		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*s3;
	const unsigned char	*s4;

	s3 = s1;
	s4 = s2;
	i = 0;
	while (i < n)
	{
		if (s3[i] != s4[i])
			return ((s3[i] - s4[i]));
		i++;
	}
	return ((0));
}
