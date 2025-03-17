/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 23:47:37 by kel-mous          #+#    #+#             */
/*   Updated: 2025/03/16 23:47:40 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*curr;
	t_list	*temp;

	if (!lst || !del)
		return ;
	curr = *lst;
	while (curr != NULL)
	{
		temp = curr;
		curr = curr->next;
		del(temp->content);
		free(temp);
	}
	*lst = NULL;
}

int	ft_lstsize(t_list *lst)
{
	t_list	*curr;
	int		i;

	curr = lst;
	i = 0;
	while (curr != NULL)
	{
		curr = curr->next;
		i++;
	}
	return ((i));
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*last;

	last = lst;
	if (lst == NULL)
		return ((lst));
	while (last->next != NULL)
	{
		last = last->next;
	}
	return ((last));
}

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (node == NULL)
		return ((NULL));
	node->content = content;
	node->next = NULL;
	return ((node));
}

t_list	*init_back_node(t_list **lst)
{
	t_list	*last;
	t_list	*new;
	char	*str;

	str = ft_strdup("");
	if (str == NULL)
		return (NULL);
	new = ft_lstnew(str);
	if (new == NULL)
		return (free(str), NULL);
	last = *lst;
	if (lst == NULL)
		return (free(str), free(new), NULL);
	if (*lst == NULL)
	{
		*lst = new;
		return (new);
	}
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = new;
	new->next = NULL;
	return (new);
}
