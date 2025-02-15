/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_input_first.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:47:52 by kel-mous          #+#    #+#             */
/*   Updated: 2025/01/24 15:53:46 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
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
	int	i;

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

t_stack	*parser(int i, int ac, char **av, t_stack *head)
{
	char	**numbers;
	long	temp;
	int		j;

	while (i < ac)
	{
		numbers = ft_split(av[i], ' ');
		if (numbers[0] == NULL)
			(write(2, "Error\n", 6), exit(0));
		j = 0;
		while (numbers[j])
		{
			temp = ft_atoy(numbers[j], 0, 1);
			if (temp == MAX || ft_lstcompare(head, (int)temp))
			{
				(free_arr(&numbers), ft_clearlst(&head));
				(write(2, "Error\n", 6), exit(0));
			}
			if ((j++, ft_add_backlst(&head, (int)temp)))
				(free_arr(&numbers), ft_clearlst(&head), exit(1));
		}
		(free_arr(&numbers), i++);
	}
	return (head);
}
