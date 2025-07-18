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

# include "../libft/libft.h"
#include <fcntl.h>
#include <unistd.h>

typedef struct s_pipex
{
	char	*infile;
	char	*outfile;
	pid_t	pid;
}	t_pipex;

#endif
