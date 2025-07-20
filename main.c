/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 15:37:26 by jaeklee           #+#    #+#             */
/*   Updated: 2025/07/20 16:16:48 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path(char **envp)
{
	char	**temp;

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

void	try_exe(char **paths, char *cmd_n, char **cmd, char **envp)
{
	char	full_path[1024];
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path[0] = '\0';
		ft_strlcat(full_path, paths[i], 1024);
		ft_strlcat(full_path, "/", 1024);
		ft_strlcat(full_path, cmd_n, 1024);
		if (access(full_path, X_OK) == 0)
			execve(full_path, cmd, envp);
		i++;
	}
	free_all(cmd);
	free_all(paths);
	perror("command not found");
	exit(127);
}

void	execute(char *av, char **envp)
{
	char	**cmd;
	char	**paths;

	cmd = ft_split(av, ' ');
	if (!cmd || !cmd[0] || cmd[0][0] == '\0')
	{
		free_all(cmd);
		perror("Empty command");
		exit(127);
	}
	paths = get_path(envp);
	try_exe(paths, cmd[0], cmd, envp);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (ac != 5)
		perror_exit("args error");
	init_pipex(&pipex);
	pipex.pid1 = fork();
	if (pipex.pid1 == -1)
		perror_exit("fork error");
	if (pipex.pid1 == 0)
	{
		pid1_set(&pipex, pipex.fd, av);
		execute(av[2], envp);
	}
	pipex.pid2 = fork();
	if (pipex.pid2 == -1)
		perror_exit("fork error");
	if (pipex.pid2 == 0)
	{
		pid2_set(&pipex, pipex.fd, av);
		execute(av[3], envp);
	}
	parent_closed(&pipex, pipex.fd);
	return (0);
}
