/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 15:37:26 by jaeklee           #+#    #+#             */
/*   Updated: 2025/07/22 12:24:07 by jaeklee          ###   ########.fr       */
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
		exit(127);
	}
	temp = ft_split(*envp + 5, ':');
	return (temp);
}

void	try_exe(char **paths, char *cmd_n, char **cmd, char **envp)
{
	char	*full_path;
	int		i;
	char	*temp;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
			perror_exit("Memory allocation failed");
		full_path = ft_strjoin(temp, cmd_n);
		if (!full_path)
			perror_exit("Memory allocation failed");
		free(temp);
		if (access(full_path, X_OK) == 0)
			execve(full_path, cmd, envp);
		free(full_path);
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
	if (ft_strchr(cmd[0], '/'))
	{
		if (access(cmd[0], X_OK) == 0)
			execve(cmd[0], cmd, envp);
		else
		{
			perror("command not found");
			free_all(cmd);
			exit(127);
		}
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
