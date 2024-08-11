/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crystal <crystal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:21:38 by crystal           #+#    #+#             */
/*   Updated: 2024/08/11 17:27:41 by crystal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

char	*access_cmd(char **paths, char *cmd)
{
	int	i;
	char	*search;
	char	*cmdpath;

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
	dup2(pipex.pipefd[0], 0);
	close(pipex.pipefd[1]);
	dup2(pipex.outfile, 1);
	pipex.cmd_args = ft_split(argv[3], ' ');
	pipex.cmd = access_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
	execve(pipex.cmd, pipex.cmd_args, env);
	close(pipex.outfile);
}

void	child(char *env[], char *argv[], t_pipex pipex)
{
	dup2(pipex.pipefd[1], 1);
	close(pipex.pipefd[0]);
	dup2(pipex.infile, 0);
	pipex.cmd_args = ft_split(argv[2], ' ');
	pipex.cmd = access_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
	execve(pipex.cmd, pipex.cmd_args, env);
	close(pipex.infile);
}	
	
char	*path_finder(char **env)
{
	while (ft_strncmp("PATH", *env, 4))
		env++;
	return (*env + 5);
	
}

void	close_pipes(t_pipex pipex)
{
	close(pipex.pipefd[0]);
	close(pipex.pipefd[1]);
}

void	error_mess(char *str)
{
	perror(str);
	exit(3);
}

void	main_process_free(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmd_paths[i])
	{
		free(pipex->cmd_paths[i]);
		i++;
	}
	free(pipex->cmd_paths);
}

int main(int argc, char *argv[], char *env[])
{
	t_pipex pipex;

	if (argc != 5)
		exit(1);
	pipex.infile = open(argv[1], O_RDONLY, 0777);
	pipex.outfile = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0777);
	if (pipex.infile < 0 || pipex.outfile < 0)
		error_mess("Missing file open");
	if (pipe(pipex.pipefd) == -1)
		error_mess("pipe error");
	pipex.paths = path_finder(env);
	pipex.cmd_paths = ft_split(pipex.paths, ':');
	pipex.pid = fork();
	if (!pipex.pid)
		child(env, argv, pipex);
	pipex.pid2 = fork();
	if (!pipex.pid2)
		child2(env, argv, pipex);
	close_pipes(pipex);
	main_process_free(&pipex);
	return 0;
}
