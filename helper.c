#include "pipex.h"

void	free_all(char **arr)
{
	int	i;

	i = 0;
	if(!arr)
		return;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	perror_exit(char *str)
{
	perror(str);
	exit(1);
}

void	init_pipex(t_pipex *pipex, char **av)
{
	if ((pipex->infile = open(av[1], O_RDONLY)) == -1)
		perror_exit("infile error");

	if ((pipex->outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
	{
		close(pipex->infile);
		perror_exit("outfile error");
	}

	if (pipe(pipex->fd) == -1)
	{
		close(pipex->infile);
		close(pipex->outfile);
		perror_exit("pipe error");
	}
}