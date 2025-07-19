/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:36:19 by jaeklee           #+#    #+#             */
/*   Updated: 2025/07/18 11:10:41 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	pid_t	pid1;
	pid_t	pid2;
	int		fd[2];
}	t_pipex;

void	free_all(char **arr);
void	perror_exit(char *str);
void	init_pipex(t_pipex *pipex, char **av);

#endif
