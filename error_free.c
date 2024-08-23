/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 12:13:35 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/08/23 09:56:19 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	check_args(char *argv[])
{
	int	i;

	i = 0;
	if (argv[2][0] == ' ' || argv[3][0] == ' ')
	{
		ft_putstr_fd("Not a valid argument\n", 2);
		exit(EXIT_FAILURE);
	}
	while (argv[2][i])
		i++;
	if (argv[2][i - 1] == ' ')
	{
		ft_putstr_fd("Not a valid argument\n", 2);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (argv[3][i])
		i++;
	if (argv[3][i - 1] == ' ')
	{
		ft_putstr_fd("Not a valid argument\n", 2);
		exit(EXIT_FAILURE);
	}
}

void	close_pipes(t_pipex pipex)
{
	close(pipex.pipefd[0]);
	close(pipex.pipefd[1]);
}

void	error_mess(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	sub_process_free(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmd_args[i])
	{
		free(pipex->cmd_args[i]);
		i++;
	}
	free(pipex->cmd_args);
	free(pipex->cmd);
	main_process_free(pipex);
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
	close(pipex->infile);
	close(pipex->outfile);
}
