/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_first.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 23:48:50 by kel-mous          #+#    #+#             */
/*   Updated: 2025/03/16 23:48:54 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void	close_fds(int *pipe_fd)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		close(pipe_fd[i]);
		i++;
	}
}

void	cleanup(int i, int *pip, char *av, pid_t id)
{
	int	status;

	(close(pip[at(i, PREV, READ)]), close(pip[at(i, CURR, WRITE)]));
	if (av == NULL)
	{
		waitpid(id, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status))
			exit(WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			exit(WTERMSIG(status) + 128);
	}
}

void	real_del(void *content)
{
	if (content != NULL)
		free(content);
}

t_list	*get_args(char *cmd, t_list *head, int ps, int i)
{
	while (cmd[i])
	{
		if (((cmd[i] > 8 && cmd[i] < 14) || cmd[i] == 32) && ps < 2)
			ps = 0;
		else
		{
			if (ps == 0 && ++ps && init_back_node(&head) == NULL)
				return (ft_lstclear(&head, real_del), NULL);
			if ((cmd[i] == 34 || cmd[i] == 39) && (ps < 2 || ps == cmd[i]))
				ps = ((ps == cmd[i]) * 1 + (ps != cmd[i]) * cmd[i]);
			else
			{
				if (cmd[i] == 92 && (ps < 2 || (ps == 34
							&& (ps == cmd[i + 1] || cmd[i + 1] == 92))))
					i++;
				if (!ft_append((char **) &ft_lstlast(head)->content,
						cmd[i], -1))
					return (ft_lstclear(&head, real_del), NULL);
			}
		}
		i++;
	}
	return (head);
}

char	**get_array(char *cmd)
{
	t_list	*head;
	t_list	*curr;
	char	**result;
	int		i;

	i = 0;
	head = get_args(cmd, NULL, 0, 0);
	if (head == NULL)
		return (NULL);
	curr = head;
	result = ft_calloc(ft_lstsize(head) + 1, sizeof(char *));
	if (result == NULL)
		return (NULL);
	while (curr != NULL)
	{
		result[i] = curr->content;
		curr = curr->next;
		i++;
	}
	ft_lstclear(&head, del);
	return (result);
}
