#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "split.c"
#include "list.c"
#include "./libft/libft.h"
#include "get_next_line.c"
#include "get_next_line_utils.c"

# define READ 0
# define WRITE 1
# define CURR 0
# define PREV 1
#define WR_FLAGS O_WRONLY | O_CREAT | O_TRUNC

char *get_binary(char *cmd, char *path)
{
	char **binaries;
	int i;
	char *result;

    i = 0;
    result = NULL;
    binaries = ft_split(path, ':');
    if (binaries == NULL)
        return (NULL);
	while(binaries[i])
	{
		if (ft_append(&binaries[i], '/', -1) == NULL)
            return (free_arr(&binaries), NULL);
		binaries[i] = ft_strjoin_px(binaries[i], cmd, 1);
        if (binaries[i] == NULL)
            return (free_arr(&binaries), NULL);
		if (access(binaries[i], X_OK) == 0)
		{
			result = ft_strdup(binaries[i]);
            if (result == NULL)
                return (free_arr(&binaries), NULL);
			break;
		}
		i++;
	}
	free_arr(&binaries);
	return (result);
}

t_list *get_args(char *cmd, t_list *head, int ps, int i)
{
	while(cmd[i])
	{
		if (((cmd[i] > 8 && cmd[i] < 14) || cmd[i] == 32) && ps < 2)
			ps = 0;
		else
		{
			if (ps == 0)
			{
				if(init_back_node(&head) == NULL)
					return (ft_lstclear(&head, del), NULL);
				ps = 1;
			}
			if ((cmd[i] == 34 || cmd[i] == 39) && (ps < 2 || ps == cmd[i]))
				ps = ((ps == cmd[i]) * 1 + (ps != cmd[i]) * cmd[i]);
			else
			{
				if (cmd[i] == 92 && (ps < 2 || (ps == 34 && (ps == cmd[i + 1] || cmd[i + 1] == 92))))
					i++;
				if(!ft_append((char **) &ft_lstlast(head)->content, cmd[i], -1))
					return (ft_lstclear(&head, del), NULL);
			}
		}
		i++;
	}
	return (head);
}

void execute(char *cmd, char **envp)
{
	char *path = NULL;
	char **array;
	int i = 0;

	array = ft_split(cmd, ' ');
	if (array == NULL)
		return ;
	if (!ft_strchr(array[0], '/'))
	{
		while (envp[i])
		{
			if (!ft_strncmp("PATH=", envp[i], 5))
			{
				path = get_binary(array[0], &envp[i][5]);
                if (path == NULL)
                    return (free_arr(&array));
				break;
			}
			i++;
		}
	}
	if (path == NULL)
		path = ft_strdup(array[0]);
    if (path == NULL)
        return free_arr(&array);
	if (execve(path, array, envp) == -1)
	{
		perror("execve failed");
		free(path);
		free_arr(&array);
	}
}

int at(int i, int state, int wr)
{
    return ((((i + state) % 2) * 2) + wr);
}

void piper(int *pip, int wr_flags, char **av, char **envp)
{
	int i;

	i = 0;
	while (av[i])
	{
		if (av[i + 2] == NULL)
		{
			pip[at(i, CURR, WRITE)] = open(av[i + 1], wr_flags, 0644);
			if (pip[at(i, CURR, WRITE)] == -1)
				exit(1);
		}
		else if (pipe(&pip[at(i, CURR, READ)]))
			(perror("pipe"), exit(1));
		if (fork() == 0)
		{
			(dup2(pip[at(i, PREV, READ)], 0), close(pip[at(i, PREV, READ)]));
			(dup2(pip[at(i, CURR, WRITE)], 1), close(pip[at(i, CURR, WRITE)]));
			execute(av[i], envp);
		}
		(close(pip[at(i, PREV, READ)]), close(pip[at(i, CURR, WRITE)]));
		wait(NULL);
		i++;
	}
}

int main(int ac, char **av, char **envp)
{
	int pipe_fd[4];
	char *line;

	if (ac < 5)
		return (0);
	if (ft_strncmp("here_doc", av[1], 9))
	{
		pipe_fd[at(0, PREV, READ)] = open(av[1], O_RDONLY);
		if (pipe_fd[at(0, PREV, READ)] == -1)
			exit(0);
		av = &av[2];
		piper(pipe_fd, O_WRONLY | O_CREAT | O_TRUNC, av, envp);
	}
	else
	{
		if (pipe(&pipe_fd[at(0, PREV, READ)]))
			perror("pipe"), exit(1);
		while (1)
		{
			write(1, "> ", 2);
			line = get_next_line(0);
			if (line == NULL)
				exit(1);
			if (!ft_strncmp(line, av[2], ft_strlen(av[2]))
				&& line[ft_strlen(av[2])] == '\n' && (free(line), 1))
				break;
			else
				ft_putstr(line, pipe_fd[at(0, PREV, WRITE)]), free(line);
		}
		close(pipe_fd[at(0, PREV, WRITE)]);
		av = &av[3];
		piper(pipe_fd, O_WRONLY | O_CREAT | O_APPEND, av, envp);
	}
}
