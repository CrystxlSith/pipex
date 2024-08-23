/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 12:12:33 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/08/23 09:56:12 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

char	*path_finder(char *env[])
{
	while (ft_strncmp("PATH", *env, 4))
		env++;
	return (*env + 5);
}

char	*access_cmd(char **paths, char *cmd)
{
	int			i;
	char		*search;
	char		*cmdpath;

	i = 0;
	while (paths[i])
	{
		search = ft_strjoin(paths[i], "/");
		cmdpath = ft_strjoin(search, cmd);
		free(search);
		if (access(cmdpath, F_OK) == 0)
		{
			return (cmdpath);
		}
		free(cmdpath);
		i++;
	}
	return (NULL);
}

void	child2(char *env[], char *argv[], t_pipex pipex)
{
	dup2(pipex.pipefd[0], STDIN_FILENO);
	close(pipex.pipefd[1]);
	dup2(pipex.outfile, STDOUT_FILENO);
	pipex.cmd_args = ft_split(argv[3], ' ');
	if (access(pipex.cmd_args[0], F_OK) != 0)
		pipex.cmd = access_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
	else
		pipex.cmd = pipex.cmd_args[0];
	if (!pipex.cmd)
	{
		sub_process_free(&pipex);
		error_mess("Error : command not found");
	}
	execve(pipex.cmd, pipex.cmd_args, env);
}

void	child(char *env[], char *argv[], t_pipex pipex)
{
	dup2(pipex.pipefd[1], STDOUT_FILENO);
	close(pipex.pipefd[0]);
	dup2(pipex.infile, STDIN_FILENO);
	pipex.cmd_args = ft_split(argv[2], ' ');
	if (access(pipex.cmd_args[0], F_OK) != 0)
		pipex.cmd = access_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
	else
		pipex.cmd = pipex.cmd_args[0];
	if (!pipex.cmd)
	{
		sub_process_free(&pipex);
		error_mess("Error : command not found");
	}
	execve(pipex.cmd, pipex.cmd_args, env);
}
