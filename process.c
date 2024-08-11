/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crystal <crystal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:08:01 by crystal           #+#    #+#             */
/*   Updated: 2024/08/11 15:51:20 by crystal          ###   ########.fr       */
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

char	*exec(t_pipex *pipex, char **cmd)
{
	int	i;
	char	*search;
	char	*cmdpath;

	i = 0;
	while (pipex->paths[i])
	{
		search = ft_strjoin(pipex->paths[i], "/");
		cmdpath = ft_strjoin(search, cmd[0]);
		free(search);
		if (access(cmdpath, F_OK | X_OK) == 0)
		{
			return (cmdpath);
		}
		free(cmdpath);
		i++;
	}
	return (NULL);
}

void	start(t_pipex *pipex, char *env[], char *cmd)
{
	char *executable;
	char	**base_cmd;

	pipex->env = ft_getenv("PATH", env);
	pipex->paths = ft_split(pipex->env, ':');
	base_cmd = ft_split(cmd, ' ');
	executable = exec(pipex, base_cmd);
	if (!executable)
	{
		ft_putstr_fd("i need a valid executable\n", 2);
		exit(2);
	}
	
	// if (pipex->pid == 0)
	// {
		if (execve(executable, base_cmd, env) == -1)
		{
			ft_putstr_fd("execution missed\n", 2);
			exit(2);
		}
	// }
}
	
int	child_process(t_pipex *pipex, char *argv[], char *env[])
{
	int	fd_in;

	fd_in = open(argv[1], O_RDONLY, 0777);
	if (fd_in == -1)
		perror("no file");
	dup2(pipex->pipefd[1], STDOUT_FILENO);
	dup2(fd_in, STDIN_FILENO);
	close(pipex->pipefd[0]);
	start(pipex, env, argv[2]);
	// int	infile;

	// infile =  open(argv[1], O_RDONLY, 0777);
	// if (infile < 0)
	// 	perror("no infile");
	// if (!env)
	// 	exit(1);
	// if (dup2(infile, STDIN_FILENO) == -1) {
	// 	perror("Error with dup2 infile to STDIN");
	// 	exit(1);
	// }
	// dup2(pipex->pipefd[1], STDOUT_FILENO);
	// close(pipex->pipefd[0]);
	// start(pipex, env, argv[2]);
	// close(infile);
	return (0);
}

int	parent_process(t_pipex *pipex, char *argv[], char *env[])
{
	int	fd_out;

	fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_out == -1)
		perror("no file");
	dup2(pipex->pipefd[0], STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(pipex->pipefd[1]);
	start(pipex, env, argv[3]);
	// int	outfile;

	// outfile = open(argv[4],O_CREAT | O_WRONLY | O_TRUNC, 0777);
	// if (outfile < 0)
	// 	perror("no outfile");
	// if (!env)
	// 	exit(1);
	// pipex->env = ft_getenv("PATH", env);
	// pipex->paths = ft_split(pipex->env, ':');
	// dup2(outfile, STDOUT_FILENO);
	// dup2(pipex->pipefd[0], STDIN_FILENO);
	// close(pipex->pipefd[1]);
	// start(pipex, env, argv[3]);
	// close(outfile);
	return (0);
}