/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 15:42:46 by jaeklee           #+#    #+#             */
/*   Updated: 2025/07/20 16:16:36 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_all(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
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

void	init_pipex(t_pipex *pipex)
{
	if (pipe(pipex->fd) == -1)
	{
		perror_exit("pipe error");
	}
}
