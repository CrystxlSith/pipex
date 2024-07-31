/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crystal <crystal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:08:01 by crystal           #+#    #+#             */
/*   Updated: 2024/07/31 17:48:59 by crystal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(char *argv[])
{
	int file;
	if (argv)
		file = open("child.txt", O_WRONLY | O_CREAT, 0777);
	ft_printf("%d\n", file);
}

void	parent_process(char *argv[])
{
	int file;
	if (argv)
		file = open("parent.txt", O_WRONLY | O_CREAT, 0777);
	if (!)
	ft_printf("%d\n", file);
}