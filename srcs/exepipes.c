/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exepipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 13:34:18 by skavunen          #+#    #+#             */
/*   Updated: 2017/08/11 15:56:25 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void			ft_exe_no_fork(char **arg, char **env)
{
	char		*exe;

	exe = ft_findexe(arg[0]);
	if (exe)
	{
		execute_command(exe, arg, env);
		ft_strdel(&exe);
	}
	else
	{
		shell_error(arg[0], NO_CMD);
		exit(EXIT_FAILURE);
	}
}

void			ft_dup_fds(t_fds *fds, int fl)
{
	if (fl == 0)
	{
		if (fds->close != 1 && fds->close != -1)
		{
			if (fds->open == 1)
				dup2(fds->fd[1], fds->close);
		}
		else if (fds->close == 1)
		{
			dup2(fds->open, fds->close);
			close(fds->open);
		}
		else
			dup2(fds->fd[1], 1);
		close(fds->fd[0]);
		close(fds->fd[1]);
		dup2(fds->in, 0);
		close(fds->in);
	}
	else
	{
		dup2(fds->fd[1], 1);
		close(fds->fd[0]);
		close(fds->fd[1]);
	}
}

void			ft_exec_pipe(t_fds *fds, char **arg, char **env)
{
	pid_t		pid;
	int			flag;

	flag = 0;
	pid = fork();
	if (pid == 0)
	{
		ft_fdsfile(fds, &flag);
		ft_dup_fds(fds, 0);
		ft_exe_no_fork(arg, env);
		if (flag == 1)
			close(fds->close);
		exit(EXIT_SUCCESS);
	}
}
