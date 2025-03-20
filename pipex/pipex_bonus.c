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
#include "pipex_bonus.h"

void	here_doc(char **av, int *pipe_fd)
{
	char	*line;

	if (pipe(&pipe_fd[at(0, PREV, READ)]))
		(perror("pipe"), exit(EXIT_FAILURE));
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (line == NULL)
		{
			write(1, "\n", 1);
			break ;
		}
		if (!ft_strchr(line, '\n'))
			(write(1, "\n", 1), ft_strjoin_px(&line, "\n", 1));
		if (!ft_strncmp(line, av[2], ft_strlen(av[2]))
			&& line[ft_strlen(av[2])] == '\n' && (free(line), 1))
			break ;
		else
			(ft_putstr(line, pipe_fd[at(0, PREV, WRITE)]), free(line));
	}
	close(pipe_fd[at(0, PREV, WRITE)]);
}

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
		(close_fds(pipe_fd), exit(0));
	if (!ft_strchr(array[0], '/'))
		path = get_binary(array[0], envp);
	if (path == NULL)
		path = ft_strdup(array[0]);
	if (path == NULL)
		(free_arr(&array), close_fds(pipe_fd), exit(EXIT_FAILURE));
	if (!ft_strchr(path, '/') || access(path, F_OK) == -1)
		(free_arr(&array), close_fds(pipe_fd),
			ft_putstr("command not found: ", 2), ft_putstr(path, 2),
			ft_putstr("\n", 2), free(path), exit(127));
	else if (access(path, X_OK) == -1)
		(free_arr(&array), close_fds(pipe_fd),
			ft_putstr("permission denied: ", 2), ft_putstr(path, 2),
			ft_putstr("\n", 2), free(path), exit(126));
	if (execve(path, array, envp) == -1)
		(perror(array[0]), free(path), free_arr(&array),
			close_fds(pipe_fd), exit(EXIT_FAILURE));
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

	if (ac < 5)
		return (EXIT_FAILURE);
	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	pipe_fd[2] = -1;
	pipe_fd[3] = -1;
	if (ft_strncmp("here_doc", av[1], 9))
	{
		pipe_fd[at(0, PREV, READ)] = open(av[1], O_RDONLY);
		if (pipe_fd[at(0, PREV, READ)] == -1)
			own_file(pipe_fd);
		av = &av[2];
		piper(pipe_fd, O_WRONLY | O_CREAT | O_TRUNC, av, envp);
	}
	else
	{
		if (ac < 6)
			return (0);
		here_doc(av, pipe_fd);
		av = &av[3];
		piper(pipe_fd, O_WRONLY | O_CREAT | O_APPEND, av, envp);
	}
}
