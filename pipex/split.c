#include <stdlib.h>
#include "./libft/libft.h"

void ft_putstr(char *str, int fd)
{
	while(*str)
	{
		write(fd, str++, 1);
	}
}

int at(int i, int state, int wr)
{
    return ((((i + state) % 2) * 2) + wr);
}

char	*get_path(char **envp)
{
	int i;

    i = 0;
	while (envp[i])
	{
		if (!ft_strncmp("PATH=", envp[i], 5))
			return (&envp[i][5]);
		i++;
	}
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*source;
	unsigned char	*destination;
	size_t			i;

	if (!dest && !src)
		return (0);
	source = (unsigned char *) src;
	destination = dest;
	i = 0;
	while (i < n)
	{
		destination[i] = source[i];
		i++;
	}
	return ((dest));
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return ((i));
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	c = (unsigned char) c;
	while (s[i])
	{
		if (s[i] == c)
			return ((((char *)(s + i))));
		i++;
	}
	if (c == '\0')
		return ((((char *)(s + i))));
	return ((0));
}

char	*ft_strdup(const char *s)
{
	size_t	size;
	char	*dup;

	size = ft_strlen(s) + 1;
	dup = malloc(size * sizeof(char));
	if (dup == 0)
		return ((0));
	ft_memcpy(dup, s, size);
	return ((dup));
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = s;
	i = 0;
	while (i < n)
		ptr[i++] = '\0';
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	i;

	if (!s)
		return (0);
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - (size_t) start;
	if (ft_strlen(s) < start)
		len = 0;
	substring = malloc((len + 1) * sizeof(char));
	if (substring == 0)
		return ((0));
	i = 0;
	while (i < len)
	{
		substring[i] = s[start + i];
		i++;
	}
	substring[i] = 0;
	return ((substring));
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb && size > __SIZE_MAX__ / nmemb)
		return (0);
	ptr = malloc(nmemb * size);
	if (ptr == 0)
		return (((0)));
	ft_bzero(ptr, nmemb * size);
	return (((ptr)));
}

static int	count_words(const char *str, char c, int i)
{
	int		in_word;
	int		n;

	in_word = 0;
	n = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] != c)
		{
			if (!in_word)
			{
				in_word = 1;
				n++;
			}
		}
		else
			in_word = 0;
		i++;
	}
	return (((n)));
}

int arr_size(char **ptr)
{
	int size;

	size = 0;
	if (!ptr)
		return (0);
	while(ptr[size])
		size++;
	return (size);
}

void free_arr(char ***ptr)
{
	int	i;

	i = 0;
	while ((*ptr)[i] != NULL)
		free((*ptr)[i++]);
	free(*ptr);
	return ;
}

void free_size(char ***ptr, int size)
{
	int	i;

	i = 0;
	while (size--)
	{
		if (ptr[0][i])
			free(ptr[0][i]);
		i++;
	}
	free(*ptr);
	return ;
}

char	**ft_strjoin_px(char **str, char *buff, int choice)
{
	char	*result;
	int		len1;
	int		len2;

	if (!str || !(*str) || !buff)
		return (NULL);
	len1 = ft_strlen(*str);
	len2 = ft_strlen(buff);
	result = malloc((len1 + len2 + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	ft_memcpy(result, *str, len1);
	ft_memcpy(result + len1, buff, len2);
	result[len1 + len2] = 0;
	if (choice == 1 || choice == 3)
		free(*str);
	if (choice == 2 || choice == 3)
		free(buff);
	*str = result;
	return (str);
}

char	**ft_split(const char *s, char c)
{
	char	**ptr;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	ptr = ft_calloc((count_words(s, c, 0) + 1), sizeof(char *));
	if (!ptr || (!s && (free(ptr), 1)))
		exit(1);
	while (k < count_words(s, c, 0))
	{
		j = 0;
		while (s[i] == c)
			i++;
		while (s[i + j] != c && s[i + j])
			j++;
		ptr[k] = ft_substr(s, i, j);
		if (!ptr[k])
			(free_arr(&ptr), exit(1));
		i = i + j;
		k++;
	}
	return ((ptr));
}

char	*ft_append(char **org, char c, int position)
{
	char	*result;
	size_t	size;

	if(position == -1)
		position = ft_strlen(org[0]);
	if (org[0] == NULL)
	{
		org[0] = ft_strdup("");
		if (org[0] == NULL)
			return (NULL);
	}
	size = ft_strlen(org[0]);
	result = ft_calloc((size + 2), sizeof(char));
	if (result == NULL)
		return (NULL);
	ft_memcpy(result, org[0], position);
	ft_memcpy(result + position, &c, 1);
	ft_memcpy(result + position + 1, org[0] + position, size - position);
	free(org[0]);
	org[0] = result;
	return (result);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i] || (s1[i] == 0 && s2[i] == 0))
			return (((unsigned char)s1[i] - (unsigned char)s2[i]));
		i++;
	}
	return ((0));
}

// t_list *get_args(char *cmd, t_list *head, int ps, int i)
// {
// 	while(cmd[i])
// 	{
// 		if (((cmd[i] > 8 && cmd[i] < 14) || cmd[i] == 32) && ps < 2)
// 			ps = 0;
// 		else
// 		{
// 			if (ps == 0)
// 			{
// 				if(init_back_node(&head) == NULL)
// 					return (ft_lstclear(&head, del), NULL);
// 				ps = 1;
// 			}
// 			if ((cmd[i] == 34 || cmd[i] == 39) && (ps < 2 || ps == cmd[i]))
// 				ps = ((ps == cmd[i]) * 1 + (ps != cmd[i]) * cmd[i]);
// 			else
// 			{
// 				if (cmd[i] == 92 && (ps < 2 || (ps == 34 && (ps == cmd[i + 1] || cmd[i + 1] == 92))))
// 					i++;
// 				if(!ft_append((char **) &ft_lstlast(head)->content, cmd[i], -1))
// 					return (ft_lstclear(&head, del), NULL);
// 			}
// 		}
// 		i++;
// 	}
// 	return (head);
// }

// char **get_array(char *cmd)
// {
// 	t_list *head;
// 	t_list *curr;
// 	char **result;
// 	int i;
	
// 	i = 0;
// 	head = get_args(cmd, NULL, 0, 0);
// 	if (head == NULL)
// 		return (NULL);
// 	curr = head;
// 	result = ft_calloc(ft_lstsize(head) + 1, sizeof(char *));
// 	if (result == NULL)
// 		return (NULL);
// 	while (curr != NULL)
// 	{
// 		result[i] = curr->content;
// 		curr = curr->next;
// 		i++;
// 	}
// 	ft_lstclear(&head, del);
// 	return (result);
// }