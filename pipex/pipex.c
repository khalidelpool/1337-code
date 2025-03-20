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

	path = NULL; // maybe you shouldnt pass pipe_fd to this function, nor use close_fds
	array = get_array(cmd);
	if (array == NULL)
		(close_fds(pipe_fd), exit(EXIT_FAILURE));
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
	pid_t 	ids[2];

	i = 0;
	while (av[i + 1])
	{
		ft_putstr("runned\n", 2);
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
		ids[i] = id;
		(close(pip[at(i, PREV, READ)]), close(pip[at(i, CURR, WRITE)]));
		i++;
		// (cleanup(i, pip, av[i + 2], id), i++);
	}
	close_fds(pip);
	ft_putstr("test\n", 2);
	int status;
	waitpid(ids[0], NULL, WNOHANG);
	
	ft_putstr("test2\n", 2);
	// wait(NULL);
	waitpid(ids[1], &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status))
		exit(WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		exit(WTERMSIG(status) + 128);
}

// int	main(int ac, char **av, char **envp)
// {
// 	int	pipe_fd[4];

// 	if (ac != 5)
// 		return (EXIT_FAILURE);
// 	pipe_fd[0] = -1;
// 	pipe_fd[1] = -1;
// 	pipe_fd[2] = -1;
// 	pipe_fd[3] = -1;
// 	pipe_fd[at(0, PREV, READ)] = open(av[1], O_RDONLY);
// 	if (pipe_fd[at(0, PREV, READ)] == -1)
// 	{
// 		perror("open");
// 		if (pipe(&pipe_fd[at(0, PREV, READ)]))
// 			return (EXIT_FAILURE);
// 		close(pipe_fd[at(0, PREV, WRITE)]);
// 	}
// 	av = &av[2];
// 	piper(pipe_fd, O_WRONLY | O_CREAT | O_TRUNC, av, envp);
// }


int main(int ac, char **av, char **envp)
{
	int pipe_fd[2];
	int input_fd;
	int output_fd;
	pid_t	id;
	pid_t	id2;
	int 	status;

	if (ac != 5)
		return (EXIT_FAILURE);
	if (pipe(pipe_fd) == -1)
		return (perror("pipe"), EXIT_FAILURE);
	id = fork();
	if (id < 0)
		return (perror("fork failed"), close(pipe_fd[0]), close(pipe_fd[1]), EXIT_FAILURE);
	if (id == 0)
	{
		input_fd = open(av[1], O_RDONLY);
		if (input_fd != -1)
		{
			close(pipe_fd[0]);
			dup2(input_fd, 0); // check dup2 failure: perror("dup2 failed");
			close(input_fd);
			dup2(pipe_fd[1], 1);
			close(pipe_fd[1]);
			execute(av[2], envp, pipe_fd);
		}
		else
		{
			perror("open");
			close(pipe_fd[0]);
			close(pipe_fd[1]);
		}
	}
	id2 = fork();
	if (id2 == -1)
		return (perror("fork failed"), close(pipe_fd[0]), close(pipe_fd[1]), EXIT_FAILURE); // maybe we should wait for the first process to not be a zombie
	if (id2 == 0)
	{
		output_fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (output_fd != -1)
		{
			close(pipe_fd[1]);
			dup2(pipe_fd[0], 0);
			close(pipe_fd[0]);
			dup2(output_fd, 1);
			close(output_fd);
			execute(av[3], envp, pipe_fd);
		}
		else
		{
			perror("open");
			close(pipe_fd[0]);
			close(pipe_fd[1]);
		}
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(id, NULL, 0);
	waitpid(id2, &status, 0);
	exit(status);
}
