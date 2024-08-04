/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crystal <crystal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:08:01 by crystal           #+#    #+#             */
/*   Updated: 2024/08/04 15:45:03 by crystal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// int	start(int *fd, int file, char *str)
// {
	
// }

char	*ft_getenv(char *str, char *env[])
{
	int 	i;
	int 	j;
	char	*substring;

	i = 0;
	if (!str || !env)
		return (NULL);
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		substring = ft_substr(env[i], 0, j);
		if (ft_strncmp(substring, str, ft_strlen(str)) == 0)
		{
			free(substring);
			return (env[i] + j + 1);
		}
		free(substring);
		i++;
	}
	return (NULL);
}

int	child_process(t_pipex *pipex, char *argv[], char *env[])
{
	if (!env)
		exit(1);
	int i = 0;
	if (pipex->args)
		pipex->file = open_fd(pipex->args[1]);
	pipex->args = ft_split(argv[2], ' ');
	pipex->env = ft_getenv("PATH", env);
	pipex->paths = ft_split(pipex->env, ':');
	ft_printf("%s\n", pipex->env);
	while (pipex->paths[i])
	{
		ft_printf("%s\n", pipex->paths[i]);
		i++;
	}
	dup2(pipex->file, STDIN_FILENO);
	dup2(pipex->pipefd[1], STDOUT_FILENO);
	close(pipex->pipefd[0]);
	// start(pipefd, file, argv[1]);
	return (0);
}

int	parent_process(t_pipex *pipex, char *argv[], char *env[])
{
	// int i = 0;
	if (!env)
		exit(1);
	if (pipex->args)
		pipex->file = open_fd(pipex->args[4]);
	// while (env[i])
	// {
	// 	ft_printf("%s\n", env[i]);
	// 	i++;
	// }
	
	pipex->args = ft_split(argv[3], ' ');
	pipex->env = ft_getenv("PATH", env);
	ft_printf("%s\n", pipex->env);
	pipex->env = NULL;
	dup2(pipex->file, STDOUT_FILENO);
	dup2(pipex->pipefd[0], STDIN_FILENO);
	close(pipex->pipefd[1]);
	// start(pipefd, file, argv[4]);
	return (0);
}