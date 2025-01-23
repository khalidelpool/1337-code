#include "push_swap.h"

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

char	**free_arr(char ***ptr)
{
	int i;

	i = 0;
	while ((*ptr)[i] != NULL)
		free((*ptr)[i++]);
	free(*ptr);
	return ((0));
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
		return ((0));
	while (k < count_words(s, c, 0))
	{
		j = 0;
		while (s[i] == c)
			i++;
		while (s[i + j] != c && s[i + j])
			j++;
		ptr[k] = ft_substr(s, i, j);
		if (!ptr[k])
			return ((free_arr(&ptr)));
		i = i + j;
		k++;
	}
	return ((ptr));
}

stack *parser(int i, int ac, char **av, stack *head)
{
	int j;
	long temp;
	char **numbers;
	int *content;

	while (i < ac)
	{
		numbers = ft_split(av[i], ' ');
		j = 0;
		while (numbers[j])
		{
			temp = ft_atoy(numbers[j]);
			if (temp == 2147483648 || ft_lstcompare(head, (int)temp))
			{
				free_arr(&numbers);
				ft_clearlst(&head);
				return (write(2, "Error\n", 6), NULL);
			}
			ft_add_backlst(&head, ft_newlst((int)temp));
			j++;
		}
		free_arr(&numbers);
		i++;
	}
	return (head);
}
