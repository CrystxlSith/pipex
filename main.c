/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crystal <crystal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:04:59 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/08/11 15:56:38 by crystal          ###   ########.fr       */
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
	t_pipex	pipex;

	pipex.pid = fork();
	if (argv[1])
	{
		if (pipe(pipex.pipefd) == -1)
			return (2); 
		if (argc != 5)
			return (1);
		if (pipex.pid == -1)
			return (2);
		if (pipex.pid == 0)
			child_process(&pipex, argv, env);
		waitpid(pipex.pid, NULL, 0);
		parent_process(&pipex, argv, env);
		return 3;
	}
}