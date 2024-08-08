/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:04:59 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/08/08 15:02:51 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init(t_pipex *pipex)
{
	pipex->args = NULL;
	pipex->env = NULL;
	pipex->file = 0;
	// pipex->pipefd = NULL;
}

int	main(int argc, char *argv[], char *env[])
{
	t_pipex	pid;
	int pipefd[2];


	// init(pipex);
	pid.pid = fork();
	// int i = 0;
	if (argv[1])
	{
		if (pipe(pipefd) == -1)
			return (2); 
		if (argc != 5)
			return (1);
		if (pid.pid == -1)
			return (2);
		if (pid.pid == 0)
			child_process(argv, env, pipefd, &pid);
		else
			parent_process(argv, env, pipefd, &pid);
		return 3;
	}
}