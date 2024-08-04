/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crystal <crystal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:04:59 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/08/03 12:53:29 by crystal          ###   ########.fr       */
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
	t_pipex pipex;

	// init(pipex);
	pipex.pid = fork();
	// int i = 0;
	if (argv[1])
	{
		if (pipe(pipex.pipefd) == -1)
			return (2); 
		if (argc != 5)
		{
			ft_printf("Error: wrong number of arguments\n");
			return (1);
		}
		if (pipex.pid == -1)
		{
			ft_printf("Error: fork failed\n");
			return (2);
		}
		if (pipex.pid == 0)
			child_process(&pipex, argv, env);
		else
			parent_process(&pipex, argv, env);
		
	}
		// parent_process(argv);
}