/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:21:38 by crystal           #+#    #+#             */
/*   Updated: 2024/08/14 15:02:30 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

static void	init(t_pipex *pipex, char *argv[])
{
	pipex->cmd = NULL;
	pipex->infile = open(argv[1], O_RDONLY, 0777);
	pipex->outfile = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0777);
	if (pipex->infile == -1 || pipex->outfile == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char *argv[], char *env[])
{
	t_pipex	pipex;

	if (argc != 5)
		exit(1);
	init(&pipex, argv);
	check_args(argv);
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
	return (0);
}
