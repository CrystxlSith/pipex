/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:23:07 by crystal           #+#    #+#             */
/*   Updated: 2024/08/23 09:56:26 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>

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
}	t_pipex;

/*			ERROR_FREE			*/

void	close_pipes(t_pipex pipex);
void	main_process_free(t_pipex *pipex);
void	sub_process_free(t_pipex *pipex);
void	check_args(char *argv[]);
void	error_mess(char *str);

/*			PROCESS				*/

char	*path_finder(char *env[]);
char	*access_cmd(char **paths, char *cmd);
void	child2(char *env[], char *argv[], t_pipex pipex);
void	child(char *env[], char *argv[], t_pipex pipex);

#endif