#include "pipex.h"

char **get_path(char **envp)
{
	char **temp;
	while (*envp && ft_strncmp("PATH=", *envp, 5) != 0)
		envp++;
	if (!*envp)
	{
		perror("PATH not found");
		exit(1);
	}
	temp = ft_split(*envp + 5, ':');
	return (temp);
}

void	try_exe(char **paths,char *cmd_n, char **cmd, char **envp)
{
	char full_path[1024];
	int	i;

	i = 0;
	while(paths[i])
	{
		full_path[0] = '\0';
		ft_strlcat(full_path, paths[i], 1024);
		ft_strlcat(full_path, "/", 1024);
		ft_strlcat(full_path, cmd[0], 1024);

		if (access(full_path, X_OK) == 0)
			execve(full_path, cmd, envp);
		i++;
	}
}
void	execute(char *av, char **envp)
{
	char **cmd;
	char **paths;
	int	i;
	char full_path[1024];

	cmd = ft_split(av, ' ');
	paths = get_path(envp);
	try_exe(paths, cmd[0], cmd, envp);
	perror("cmd not found");
	free_all(cmd);
	free_all(paths);
	exit(127);
}

void	pid1_set(t_pipex *pipex, int *fd)
{
	dup2(pipex->infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(pipex->infile);
	close(pipex->outfile);	
}

void	pid2_set(t_pipex *pipex, int *fd)
{
		dup2(fd[0], STDIN_FILENO);
		dup2(pipex->outfile, STDOUT_FILENO);
		close(fd[1]);
		close(pipex->infile);
		close(pipex->outfile);
}

void	parent_closed(t_pipex *pipex, int *fd)
{
    close(fd[0]);
    close(fd[1]);
    close(pipex->infile);
    close(pipex->outfile);
    waitpid(pipex->pid1, NULL, 0);
    waitpid(pipex->pid2, NULL, 0);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex pipex;

	if (ac != 5)
		perror_exit("args error");
	init_pipex(&pipex, av);
	pipex.pid1 = fork();
	if (pipex.pid1 == -1)
		perror_exit("fork error");
	if (pipex.pid1 == 0)
	{
		pid1_set(&pipex, pipex.fd);
		execute(av[2], envp);
	}
	pipex.pid2 = fork();
	if (pipex.pid2 == -1)
		perror_exit("fork error");
	if (pipex.pid2 == 0)
	{
		pid2_set(&pipex, pipex.fd);
		execute(av[3], envp);
	}
	parent_closed(&pipex, pipex.fd);
    return (0);
}