/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crystal <crystal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:23:07 by crystal           #+#    #+#             */
/*   Updated: 2024/08/11 16:36:42 by crystal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
 #include <sys/types.h>
#include <sys/wait.h>


typedef struct s_pipex
{
	pid_t	pid;
	pid_t	pid2;
	int		pipefd[2];
	int		infile;
	int		outfile;
	char	*paths;
	char	*cmd;
	char	**cmd_args;
	char	**cmd_paths;
	
	
}t_pipex;