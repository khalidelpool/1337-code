#include "push_swap.h"

void f(int content)
{
	printf("content is: %d\n", content);
}

char	**free_arr_ps(char ***ptr)
{
	int i;

	i = 0;
	while ((*ptr)[i] != NULL)
		free((*ptr)[i++]);
	free(*ptr);
	return ((0));
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return ((1));
	return ((0));
}

long	ft_atoy(const char *nptr)
{
	long	result;
	int	sign;

	result = 0;
	sign = 1;
	while ((*nptr > 8 && *nptr < 14) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	else if (!ft_isdigit(*nptr))
		return (2147483648);
	while (ft_isdigit(*nptr))
	{
		result = result * 10 + *nptr - 48;
		if (result < -2147483648 || result > 2147483647)
			return (2147483648);
		nptr++;
	}
	if (!((*nptr > 8 && *nptr < 14) || *nptr == 32 || *nptr == 0))
		return (2147483648);
	return (((result * sign)));
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

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return ((i));
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

static char	**free_arr(char ***ptr, int k)
{
	while (k >= 0)
		free((*ptr)[k--]);
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
			return ((free_arr(&ptr, k - 1)));
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
				free_arr_ps(&numbers);
				ft_clearlst(&head);
				return (write(2, "Error\n", 6), NULL);
			}
			ft_add_backlst(&head, ft_newlst((int)temp));
			j++;
		}
		free_arr_ps(&numbers);
		i++;
	}
	return (head);
}

stack	*ft_newlst(int content)
{
	stack	*node;

	node = malloc(sizeof(stack));
	if (node == NULL)
		return ((NULL));
	node->number = content;
	node->next = NULL;
	return ((node));
}

void ft_clearlst(stack **lst)
{
	stack	*curr;
	stack	*temp;

	if (!lst)
		return ;
	curr = *lst;
	while (curr != NULL)
	{
		temp = curr;
		curr = curr->next;
		if (temp != NULL)
			free(temp);
	}
	*lst = NULL;
}

void	ft_iterlst(stack *lst, void (*f)(int))
{
	stack	*curr;

	if (!f)
		return ;
	curr = lst;
	while (curr != NULL)
	{
		f(curr->number);
		curr = curr->next;
	}
}

void	ft_add_backlst(stack **lst, stack *new)
{
	stack	*last;

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

int ft_lstcompare(stack *lst, int to_compare)
{
	stack	*curr;

	curr = lst;
	while (curr != NULL)
	{
		if (curr->number == to_compare)
			return (1);
		curr = curr->next;
	}
	return (0);
}

int ft_sizelst(stack *node)
{
	int size;
	if (!node)
		return (0);
	size = 0;
	while (node)
	{
		node = node->next;
		size++;
	}
	return (size);
}

void old_moves(int instruction, int *last_move, int new)
{
	if (instruction == 1)
		write(1, "sa\n", 3);
	else if (instruction == 2)
		write(1, "sb\n", 3);
	else if (instruction == 3)
		write(1, "pb\n", 3);
	else if (instruction == 4)
		write(1, "pa\n", 3);
	else if (instruction == 5)
		write(1, "ra\n", 3);
	else if (instruction == 6)
		write(1, "rb\n", 3);
	else if (instruction == 7)
		write(1, "rra\n", 4);
	else if (instruction == 8)
		write(1, "rrb\n", 4);
	*last_move = new;
}

void moves(int choice, int operation, int *last_move)
{
	if (!choice && operation == 3 && *last_move == 6)
		write(1, "rr\n", 3), old_moves(0, last_move, 0);
	else if (choice && operation == 3 && *last_move == 5)
		write(1, "rr\n", 3), old_moves(0, last_move, 0);
	else if (!choice && operation == 4 && *last_move == 8)
		write(1, "rrr\n", 4), old_moves(0, last_move, 0);
	else if (choice && operation == 4 && *last_move == 7)
		write(1, "rrr\n", 4), old_moves(0, last_move, 0);
	else if (!choice && operation == 1)
		old_moves(*last_move, last_move, 1);
	else if (choice && operation == 1)
		old_moves(*last_move, last_move, 2);
	else if (!choice && operation == 2)
		old_moves(*last_move, last_move, 3);
	else if (choice && operation == 2)
		old_moves(*last_move, last_move, 4);
	else if (!choice && operation == 3)
		old_moves(*last_move, last_move, 5);
	else if (choice && operation == 3)
		old_moves(*last_move, last_move, 6);
	else if (!choice && operation == 4)
		old_moves(*last_move, last_move, 7);
	else if (choice && operation == 4)
		old_moves(*last_move, last_move, 8);
}

void ft_sort3(stack **head, int *last_move)
{
	int smallest;
	int index;
	int i;
	stack *curr;

	index = 0;
	i = 0;
	smallest = 2147483647;
	curr = *head;
	while (curr != NULL)
	{
		if (curr->number < smallest)
		{
			smallest = curr->number;
			index = i;
		}
		curr = curr->next;
		i++;
	}
	if (index == 2)
	{
		if ((*head)->number > (*head)->next->number)
			ft_swap(head), moves(0, 1, last_move);
		ft_revrot(head), moves(0, 4, last_move);
	}
	else if (index == 1)
	{
		if ((*head)->number > (*head)->next->next->number)
			ft_rot(head), moves(0, 3, last_move);
		else
			ft_swap(head), moves(0, 1, last_move);
	}
	else if(index == 0 && (*head)->next->number > (*head)->next->next->number)
		ft_revrot(head), ft_swap(head), moves(0, 4, last_move), moves(0, 1, last_move);
}

int ft_is_sorted(stack *head)
{
	int last;

	last = -2147483648;
	while (head != NULL)
	{
		if (last > head->number)
			return (0);
		last = head->number;
		head = head->next;
	}
	return (1);
}
