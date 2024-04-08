/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:18:47 by jlabonde          #+#    #+#             */
/*   Updated: 2024/03/07 16:37:35 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define USAGE\
	"Usage: ./pipex[_bonus] (INFILE | here_doc LIMITER) cmd1 ... cmdn \
OUTFILE"
# include "libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct t_struct
{
	int		infile_fd;
	int		outfile_fd;
	int		pipe_fd[2];
	int		is_bonus;
	int		is_first;
	int		exit_code_child;
	int		wstatus;
	pid_t	last_pid;
	char	*outfile_name;
	char	*infile_name;
	char	*delimiter;
	char	*path;
	char	**command;
	char	**env;
}			t_struct;
void	exit_error(char *str, t_struct *pipex, int close_fds, int exit_code);
char	*find_path(t_struct *pipex);
char	*check_path(char *cmd, t_struct *pipex);
void	get_path(t_struct *pipex);
void	open_infile(t_struct *pipex);
int		wait_commands(t_struct *pipex);

#endif