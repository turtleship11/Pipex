/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 15:56:24 by jaeklee           #+#    #+#             */
/*   Updated: 2025/07/22 13:46:58 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pid1_set(t_pipex *pipex, int *fd, char **av)
{
	pipex->infile = open(av[1], O_RDONLY);
	if (pipex->infile == -1)
	{
		close(fd[0]);
		close(fd[1]);
		perror_exit("infile error");
	}
	if (dup2(pipex->infile, STDIN_FILENO) == -1)
	{
		close(pipex->infile);
		perror_exit("dup2 for STDIN_FILENO failed");
	}
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		close(pipex->infile);
		close(fd[0]);
		perror_exit("dup2 for STDOUT_FILENO failed");
	}
	close(fd[0]);
	close(fd[1]);
	close(pipex->infile);
}

void	pid2_set(t_pipex *pipex, int *fd, char **av)
{
	pipex->outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile == -1)
	{
		close(fd[0]);
		close(fd[1]);
		perror_exit("outfile error");
	}
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		close(pipex->outfile);
		close(fd[1]);
		perror_exit("dup2 for STDIN_FILENO failed");
	}
	if (dup2(pipex->outfile, STDOUT_FILENO) == -1)
	{
		close(pipex->outfile);
		close(fd[0]);
		perror_exit("dup2 for STDOUT_FILENO failed");
	}
	close(fd[1]);
	close(fd[0]);
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
