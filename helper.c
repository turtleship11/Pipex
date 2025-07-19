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