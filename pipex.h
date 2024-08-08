/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:08:19 by crystal           #+#    #+#             */
/*   Updated: 2024/08/08 15:02:01 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
 #include <sys/types.h>
#include <sys/wait.h>

typedef struct s_pipex
{
	pid_t	pid;
	int		pipefd[2];
	int		file;
	char	*env;
	char	*exec;
	char	**args;
	char	**paths;
	
	
}t_pipex;

int	child_process(char *argv[], char *env[], int *pipefd, t_pipex *pid);
char	*ft_join_free(char **s1, const char *s2);
int	parent_process(char *argv[], char *env[], int *pipefd, t_pipex *pid);
char	*ft_getenv(char *str, char *env[]);
int	open_fd(char *str, t_pipex *pipex);