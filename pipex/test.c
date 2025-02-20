#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h> 
#include "split.c"
#include "list.c"
#include "./libft/libft.h"
#include "get_next_line.c"
#include "get_next_line_utils.c"

# define READ 0
# define WRITE 1
# define CURR 0
# define PREV 1

char *get_binary(char *cmd, char **envp)
{
	char **binaries;
	char *result;
	int size;
	int i;

    binaries = ft_split(get_path(envp), ':');
	size = arr_size(binaries);
	result = NULL;
	i = 0;
    if (binaries == NULL)
        return (NULL);
	while(binaries[i])
	{
		if (ft_strjoin_px(ft_strjoin_px(&binaries[i], "/", 1), cmd, 1) == NULL)
            return (free_size(&binaries, size), NULL);
		if (access(binaries[i], X_OK) == 0)
		{
			result = ft_strdup(binaries[i]); // this is already malloc protected, since result would be null, we break and return NULL then
			break;
		}
		i++;
	}
	free_size(&binaries, size);
	return (result);
}

void execute(char *cmd, char **envp)
{
	char *path = NULL;
	char **array;

	array = ft_split(cmd, ' ');
	if (array == NULL)
		return ;
	if (!ft_strchr(array[0], '/'))
		path = get_binary(array[0], envp);
	if (path == NULL)
		path = ft_strdup(array[0]);
    if (path == NULL)
        (free_arr(&array), exit(EXIT_FAILURE));
	if (execve(path, array, envp) == -1)
	{
		perror(array[0]);
		free(path);
		free_arr(&array);
		exit(0);
	}
}

void cleanup(int i, int *pip, char *av)
{
	int status;

	(close(pip[at(i, PREV, READ)]), close(pip[at(i, CURR, WRITE)]));
	wait(&status);
	if (av == NULL)
	{
		if (WIFEXITED(status) && WEXITSTATUS(status))
			exit(WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			exit(WTERMSIG(status) + 128);
	}
}

void piper(int *pip, int wr_flags, char **av, char **envp)
{
	int i;
	pid_t id;

	i = 0;
	while (av[i + 1])
	{
		if (av[i + 2] == NULL)
		{
			pip[at(i, CURR, WRITE)] = open(av[i + 1], wr_flags, 0644);
			if (pip[at(i, CURR, WRITE)] == -1)
				(perror("open"), exit(EXIT_FAILURE));
		}
		else if (pipe(&pip[at(i, CURR, READ)]))
			(perror("pipe"), exit(EXIT_FAILURE));
		id = fork();
		if (id < 0)
			(perror("fork"), exit(EXIT_FAILURE));
		if (id == 0)
		{
			(dup2(pip[at(i, PREV, READ)], 0), close(pip[at(i, PREV, READ)]));
			(dup2(pip[at(i, CURR, WRITE)], 1), close(pip[at(i, CURR, WRITE)]));
			execute(av[i], envp);
		}
		(cleanup(i, pip, av[i + 2]), i++);
	}
}

void here_doc(char **av, int *pipe_fd)
{
	char *line;

	if (pipe(&pipe_fd[at(0, PREV, READ)]))
		(perror("pipe"), exit(EXIT_FAILURE));
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (line == NULL)
		{
			write(1, "\n", 1);
			break;
		}
		if (!ft_strchr(line, '\n'))
			(write(1, "\n", 1), ft_strjoin_px(&line, "\n", 1));
		if (!ft_strncmp(line, av[2], ft_strlen(av[2]))
			&& line[ft_strlen(av[2])] == '\n' && (free(line), 1))
			break;
		else
			(ft_putstr(line, pipe_fd[at(0, PREV, WRITE)]), free(line));
	}
	close(pipe_fd[at(0, PREV, WRITE)]);
}

int main(int ac, char **av, char **envp)
{
	int pipe_fd[4];
	int stout = dup(1);

	if (ac < 5)
		return (0);
	if (ft_strncmp("here_doc", av[1], 9))
	{
		pipe_fd[at(0, PREV, READ)] = open(av[1], O_RDONLY);
		if (pipe_fd[at(0, PREV, READ)] == -1)
			(perror("open"), exit(0));
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
