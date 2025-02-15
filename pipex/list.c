#include <stdlib.h>
#include "./libft/libft.h"

void del(void *content)
{
	//free(content);
}

void f(void *content)
{
	printf("str in list is: {%s}\n", (char *)content);
}

t_list *init_back_node(t_list **lst)
{
	t_list	*last;
	t_list *new;
	char *str;

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

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	last = *lst;
	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = new;
	new->next = NULL;
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new != NULL && lst != NULL)
	{
		new->next = *lst;
		*lst = new;
	}
}

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

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*curr;

	if (!f)
		return ;
	curr = lst;
	while (curr != NULL)
	{
		f(curr->content);
		curr = curr->next;
	}
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
