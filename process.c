/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:08:01 by crystal           #+#    #+#             */
/*   Updated: 2024/08/05 15:02:32 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec(t_pipex *pipex)
{
	int	i;
	char	*search;
	char	*cmdpath;

	i = 0;
	while (pipex->paths[i])
	{
		search = ft_join_free(&pipex->paths[i], "/");
		cmdpath = ft_join_free(&search, pipex->args[0]);
		if (access(cmdpath, F_OK | X_OK) == 0)
		{
			pipex->exec = cmdpath;
			break ;
		}
		i++;
	}
	return ;
}

void	start(t_pipex *pipex, char *env[])
{
	exec(pipex);
	if (!pipex->exec)
	{
		ft_putstr_fd("i need a valid executable\n", 2);
		exit(2);
	}
			printf("cmd path = %s", pipex->exec);
	if (execve(pipex->exec, pipex->args, env) == -1)
	{
		ft_putstr_fd("execution missed\n", 2);
		exit(2);
	}
}

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
	pipex->args = ft_split(argv[2], ' ');
	pipex->env = ft_getenv("PATH", env);
	pipex->paths = ft_split(pipex->env, ':');
	if (argv)
		pipex->file = open_fd(pipex->args[1], pipex);
	dup2(pipex->file, STDIN_FILENO);
	dup2(pipex->pipefd[1], STDOUT_FILENO);
	close(pipex->pipefd[0]);
	start(pipex, env);
	return (0);
}

int	parent_process(t_pipex *pipex, char *argv[], char *env[])
{
	// int i = 0;
	if (!env)
		exit(1);
	// while (env[i])
	// 
	// 	ft_printf("%s\n", env[i]);
	// 	i++;
	// }
	
	pipex->args = ft_split(argv[3], ' ');
	pipex->env = ft_getenv("PATH", env);
	pipex->paths = ft_split(pipex->env, ':');
	if (argv)
		pipex->file = open_fd(pipex->args[4], pipex);
	// ft_printf("%s\n", pipex->env);
	dup2(pipex->file, STDOUT_FILENO);
	dup2(pipex->pipefd[0], STDIN_FILENO);
	close(pipex->pipefd[1]);
	start(pipex, env);
	return (0);
}