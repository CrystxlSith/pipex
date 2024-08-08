/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:08:01 by crystal           #+#    #+#             */
/*   Updated: 2024/08/08 15:28:01 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	free_path(char **paths)
{
	int i;

	i = 0;
	while(paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

char	*exec(char *cmd, char **env) 
{
	int	i;
	char	*search;
	char	**base_cmd;
	char	*cmdpath;
	char	**getenv;

	i = 0;
	getenv = ft_split(ft_getenv("PATH", env), ':');
	base_cmd = ft_split(cmd, ' ');
	while (getenv[i])
	{
		search = ft_strjoin(getenv[i], "/");
		cmdpath = ft_strjoin(search, base_cmd[0]);
		free(search);
		if (access(cmdpath, F_OK | X_OK) == 0)
		{
			free_path(base_cmd);
			return (cmdpath);
		}
		free(cmdpath);
		i++;
	}
	// free_path(paths);
	return (cmd);
}

void	start(char *env[], char *cmd, t_pipex *pid)
{
	char	**args;
	char	*executable_path;

	args = ft_split(cmd, ' ');
	executable_path = exec(args[0], env);
	if (pid->pid == 0)
	{
		if (execve(executable_path, args, env) == -1)
		{
			// free_path(paths);
			free(exec);
			ft_putstr_fd("execution missed\n", 2);
			exit(0);
		}
	}
}


int	child_process(char *argv[], char *env[], int *pipefd, t_pipex *pid)
{
	int infile;

	infile = open(argv[1], O_RDONLY, 0777);
	if (!env)
		exit(1);
	dup2(infile, 0);
	dup2(pipefd[1], 1);
	close(pipefd[0]);
	start(env, argv[2], pid);
	return (0);
}

int	parent_process(char *argv[], char *env[], int *pipefd, t_pipex *pid)
{
	int	outfile;

	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (!env)
		exit(1);
	dup2(outfile, 1);
	dup2(pipefd[0],0);
	close(pipefd[1]);
	start(env, argv[3], pid);
	// ft_printf("%s parent \n", pipex->env);
	return (0);
}