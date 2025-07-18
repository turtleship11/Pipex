#include "pipex.h"
#include <stdio.h>

// void	set_dup(char **av, int *fd)
// {
// 	int	infile;

// 	infile = open(av[1], O_RDONLY); // infile=3
// 	if (infile == -1)
// 		perror_exit("infile error");
// 	if (dup2(infile, STDIN_FILENO) == -1) // 3->0, 0=3
// 		perror_exit("dup2 error");
// 	if (dup2(fd[1], STDOUT_FILENO) == -1)
// 		perror_exit("dup2 error");
// 	close(fd[0]);
// 	close(fd[1]);
// }

// void	pipe_set(char **av, char **envp)
// {
// 	int	fd[2];
// 	pid_t	pid;

// 	if (pipe(fd) == -1)
// 		perror_exit("pipe error");
// 	pid = fork();
// 	if (pid == -1)
// 		perror_exit("fork error");
// 	if (pid == 0)
// 	{
// 		set_dup(av, fd);
// 		execute(av[2], envp);
// 	}
// }

void	excute(char *av, char **envp)
{
	char **cmd;
	char *path;
	char **paths;

	cmd = ft_split(av, ' ');
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	path = *envp + 5;
	// paths = ft_split(path, ':');
	printf("reach\n");
	execve(path, cmd, envp);
	printf("fail\n");
}
int	main(int ac, char **av, char **envp)
{
	t_pipex pipex;
	int	infile;
	pid_t pid;

	if (ac != 5)
	{
		printf("aguments error");
	}
	pipex.infile = av[1];
	pipex.outfile = av[ac];
	infile = open(av[1], O_RDONLY);
	if (infile == -1)
		perror("infile error");
	if (dup2(infile, STDIN_FILENO) == -1) // 3->0, 0=3
		perror("dup2 error");
	pid = fork();
	if (pid == -1)
		perror("fork error");
	if (pid == 0)
	{
		excute(av[2], envp);
		//excute cmd
	}
	else if (pid > 0)
	{

	}
}


	// if (init_pipex(&pipex, argc - 1, argv + 1, get_path(envp)) < 0)
	// {
	// 	write_and_clean_up(&pipex);
	// 	return (EXIT_FAILURE);
	// }
