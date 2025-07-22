/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:36:19 by jaeklee           #+#    #+#             */
/*   Updated: 2025/07/21 10:21:26 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	pid_t	pid1;
	pid_t	pid2;
	int		fd[2];
}			t_pipex;

void		free_all(char **arr);
void		perror_exit(char *str);
void		init_pipex(t_pipex *pipex);
void		pid1_set(t_pipex *pipex, int *fd, char **av);
void		pid2_set(t_pipex *pipex, int *fd, char **av);
void		parent_closed(t_pipex *pipex, int *fd);
char		**get_path(char **envp);
void		try_exe(char **paths, char *cmd_n, char **cmd, char **envp);
void		execute(char *av, char **envp);
#endif
