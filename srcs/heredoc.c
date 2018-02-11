/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/07 11:49:25 by skavunen          #+#    #+#             */
/*   Updated: 2017/08/22 18:56:41 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	ft_child_fd(t_fds *fds, int fl, int fd[])
{
	if (fl == 1)
	{
		dup2(fds->fd[1], 1);
		close(fds->fd[0]);
	}
	close(fd[1]);
	dup2(fd[0], 0);
	if (fds->file > 0 && fl == 0)
		dup2(fds->file, 1);
}

int		ft_new_line(char **str, t_fds *fds)
{
	char	red[512];
	int		ret;

	ft_bzero(red, 512);
	if ((ret = read(0, red, 512)) <= 0)
	{
		write(1, "\n", 1);
		if (*str)
			ft_strdel(str);
		return (0);
	}
	red[ret - 1] = '\0';
	*str = ft_strdup(red);
	if (!ft_strcmp(*str, fds->hered))
	{
		if (*str)
			ft_strdel(str);
		return (0);
	}
	return (1);
}

void	here_end(t_read *read, t_fds *fds)
{
	reset_termios(g_shell);
	ft_strdel(&read->prompt);
	ft_strdel(&read->cmd);
	free(read);
	ft_strdel(&fds->hered);
	fds->hdoc = -1;
}

char	*ft_here_parent(t_fds *fds, t_read *read)
{
	char	ret[2048];

	read = read_init(NULL, "heredoc", g_shell->env, NULL);
	ft_bzero(ret, 2048);
	read->heredoc = 1;
	controlled_termios(g_shell);
	while (read->work >= 0)
	{
		read->work = 42;
		ft_bzero(read->cmd, 1024);
		get_line(read);
		termcap_do("do");
		termcap_do("cr");
		if (ft_strequ(fds->hered, read->cmd))
			break ;
		else
		{
			ft_memcpy(ret + ft_strlen(ret), read->cmd, ft_strlen(read->cmd));
			if (read->cmd[0])
				ret[ft_strlen(ret)] = '\n';
		}
	}
	here_end(read, fds);
	return (read->work == -2 ? NULL : ft_strdup(ret));
}

void	ft_heredoc(t_fds *fds, char **arg, char **env, int fl)
{
	int		fd[2];
	char	*exe;
	char	*ret;

	if (pipe(fd) < 0 || !(ret = ft_here_parent(fds, NULL)))
		return ;
	if ((g_proc = fork()) == 0)
	{
		if ((exe = ft_findexe(arg[0])))
		{
			ft_child_fd(fds, fl, fd);
			execute_command(exe, arg, env);
			ft_strdel(&exe);
		}
		else
		{
			shell_error(arg[0], NO_CMD);
			exit(EXIT_FAILURE);
		}
		fds->file > 0 ? (void)close(fds->file) : NULL;
		close(fd[0]);
		close(fds->fd[1]);
		exit(EXIT_SUCCESS);
	}
	g_proc > 0 ? put_heredoc(ret, fd) : NULL;
}
