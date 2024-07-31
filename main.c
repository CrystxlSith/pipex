/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crystal <crystal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:04:59 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/07/31 17:44:42 by crystal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[])
{
	// int fd[2];
	int pid = fork();

	if (argc != 5)
	{
		ft_printf("Error: wrong number of arguments\n");
		return (1);
	}
	if (pid == -1)
	{
		ft_printf("Error: fork failed\n");
		return (2);
	}
	if (pid == 0)
		child_process(argv);
	if (pid > 0)
		parent_process(argv);
}