/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_memmove.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: kel-mous <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/11/04 18:17:13 by kel-mous		  #+#	#+#			 */
/*   Updated: 2024/11/04 18:18:52 by kel-mous		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*source;
	unsigned char	*destination;

	if (!dest && !src)
		return (0);
	source = (unsigned char *)src;
	destination = dest;
	if (src > dest)
	{
		ft_memcpy(dest, src, n);
	}
	else
	{
		while (n > 0)
		{
			destination[n - 1] = source[n - 1];
			n--;
		}
	}
	return ((dest));
}
