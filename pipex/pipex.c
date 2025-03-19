/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 23:43:49 by kel-mous          #+#    #+#             */
/*   Updated: 2025/03/16 23:43:59 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

char	*get_binary(char *cmd, char **envp)
{
	char	**binaries;
	char	*result;
	int		size;
	int		i;

	binaries = ft_split(get_path(envp), ':');
	size = arr_size(binaries);
	result = NULL;
	i = 0;
	if (binaries == NULL)
		return (NULL);
	while (binaries[i])
	{
		if (ft_strjoin_px(ft_strjoin_px(&binaries[i], "/", 1), cmd, 1) == NULL)
			return (free_size(&binaries, size), NULL);
		if (access(binaries[i], X_OK) == 0)
		{
			result = ft_strdup(binaries[i]);
			break ;
		}
		i++;
	}
	free_size(&binaries, size);
	return (result);
}

void	execute(char *cmd, char **envp, int *pipe_fd)
{
	char	*path;
	char	**array;

	path = NULL;
	array = get_array(cmd);
	if (array == NULL)
		(close_fds(pipe_fd), exit(EXIT_FAILURE));
	if (!ft_strchr(array[0], '/'))
		path = get_binary(array[0], envp);
	if (path == NULL)
		path = ft_strdup(array[0]);
	if (path == NULL)
		(free_arr(&array), close_fds(pipe_fd), exit(EXIT_FAILURE));
	if (!ft_strchr(path, '/'))
	{
		ft_putstr("command not found: ", 2);
		ft_putstr(path, 2);
		ft_putstr("\n", 2);
		exit(127);
	}
	errno = ENOENT;
	
	if (execve(path, array, envp) == -1)
	{
		perror(array[0]);
		free(path);
		free_arr(&array);
		close_fds(pipe_fd);
		exit(errno);
	}
}

void	piper(int *pip, int wr_flags, char **av, char **envp)
{
	int		i;
	pid_t	id;

	i = 0;
	while (av[i + 1])
	{
		if (av[i + 2] == NULL)
		{
			pip[at(i, CURR, WRITE)] = open(av[i + 1], wr_flags, 0644);
			if (pip[at(i, CURR, WRITE)] == -1)
				(perror("open"), close_fds(pip), exit(EXIT_FAILURE));
		}
		else if (pipe(&pip[at(i, CURR, READ)]))
			(perror("pipe"), close_fds(pip), exit(EXIT_FAILURE));
		id = fork();
		if (id < 0)
			(perror("fork"), close_fds(pip), exit(EXIT_FAILURE));
		if (id == 0)
		{
			(dup2(pip[at(i, PREV, READ)], 0), close(pip[at(i, PREV, READ)]));
			(dup2(pip[at(i, CURR, WRITE)], 1), close(pip[at(i, CURR, WRITE)]));
			execute(av[i], envp, pip);
		}
		(cleanup(i, pip, av[i + 2], id), i++);
	}
}

int	main(int ac, char **av, char **envp)
{
	int	pipe_fd[4];

	if (ac != 5)
		return (EXIT_FAILURE);
	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	pipe_fd[2] = -1;
	pipe_fd[3] = -1;
	pipe_fd[at(0, PREV, READ)] = open(av[1], O_RDONLY);
	if (pipe_fd[at(0, PREV, READ)] == -1)
	{
		perror("open");
		if (pipe(&pipe_fd[at(0, PREV, READ)]))
			return (EXIT_FAILURE);
		close(pipe_fd[at(0, PREV, WRITE)]);
	}
	av = &av[2];
	piper(pipe_fd, O_WRONLY | O_CREAT | O_TRUNC, av, envp);
}
