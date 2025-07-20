/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 15:56:24 by jaeklee           #+#    #+#             */
/*   Updated: 2025/07/20 16:06:31 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pid1_set(t_pipex *pipex, int *fd, char **av)
{
	pipex->infile = open(av[1], O_RDONLY);
	if (pipex->infile == -1)
		perror_exit("infile error");
	dup2(pipex->infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(pipex->infile);
}

void	pid2_set(t_pipex *pipex, int *fd, char **av)
{
	pipex->outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile == -1)
	{
		perror_exit("outfile error");
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(pipex->outfile, STDOUT_FILENO);
	close(fd[1]);
	close(pipex->outfile);
}

void	parent_closed(t_pipex *pipex, int *fd)
{
	int	status;

	close(fd[0]);
	close(fd[1]);
	waitpid(pipex->pid1, NULL, 0);
	waitpid(pipex->pid2, &status, 0);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	else
		exit(1);
}
