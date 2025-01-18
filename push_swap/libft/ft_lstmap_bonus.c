/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_lstmap_bonus.c								  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: kel-mous <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/11/04 17:53:11 by kel-mous		  #+#	#+#			 */
/*   Updated: 2024/11/04 17:56:20 by kel-mous		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*curr;
	t_list	*result;
	t_list	*new;

	curr = lst;
	result = 0;
	while (curr != NULL)
	{
		new = ft_lstnew(f(curr->content));
		if (new == NULL)
		{
			ft_lstclear(&result, del);
			return ((NULL));
		}
		ft_lstadd_back(&result, new);
		curr = curr->next;
	}
	return ((result));
}
