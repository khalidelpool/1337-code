#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int ac, char **av, char *envp[])
{
	int pipe_fd[2];
	//pipe_fd[0] read
	//pipie_fd[1] write

	if (pipe(pipe_fd))
		return (printf("error\n"), 1);
	int id = fork();
	if (id == 0)
	{
		close(pipe_fd[0]);
		int infile = open("infile", O_RDONLY);
		dup2(infile, 0);
		close(infile);
		dup2(pipe_fd[1], 1);
		close(pipe_fd[1]);
		char *child_args[] = { av[2], NULL };
		execve(av[2], child_args, envp);
	}
	else
	{
		wait(NULL);
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
		int outfile = open("outfile", O_WRONLY | O_CREAT, 0644);
		dup2(outfile, 1);
		close(outfile);
		char *parent_args[] = { av[3], NULL };
		execve(av[3], parent_args, envp);
	}
}