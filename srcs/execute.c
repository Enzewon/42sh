/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 13:11:47 by skavunen          #+#    #+#             */
/*   Updated: 2017/08/22 19:13:50 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	ft_fdsfile(t_fds *fds, int *flag)
{
	if (fds->file > 0)
		dup2(fds->file, 1);
	if (fds->close != -1)
	{
		if (fds->open != -1)
		{
			if (fds->open == -2)
				close(fds->close);
			else
			{
				dup2(fds->open, fds->close);
				close(fds->open);
				*flag = 1;
			}
		}
	}
	if (fds->in == -3)
		exit(EXIT_FAILURE);
	if (fds->in != 0)
	{
		dup2(fds->in, 0);
		close(fds->in);
	}
}

int		find_spec(char *str, int j)
{
	int	z;

	z = 0;
	j++;
	if (str[j] == 'n' || str[j] == 't' || str[j] == 'r' || str[j] == 'b' ||
		str[j] == 'v')
		z = 1;
	if (z != 1)
		return (0);
	if (str[j] == 'n')
		write(1, "\n", 1);
	else if (str[j] == 't')
		write(1, "\t", 1);
	else if (str[j] == 'r')
		write(1, "\r", 1);
	else if (str[j] == 'b')
		write(1, "\b", 1);
	else if (str[j] == 'v')
		write(1, "\v", 1);
	return (1);
}

int		builtin_command(char *exe, char **argv, char **env)
{
	if (ft_strequ(exe, "echo") && env)
		return (mini_echo(argv, 0, 0, 0));
	else if (env && ft_strequ(exe, "env"))
		return (mini_env(env));
	else if (ft_strequ(exe, "history"))
		return (mini_history());
	else
		return (0);
}

void	ft_exec(char **arg, char **env, t_fds *fds)
{
	char	*exe;
	int		flag;

	pipe(fds->ex);
	g_proc = fork();
	flag = 0;
	if (g_proc == 0)
	{
		if ((exe = ft_findexe(arg[0])))
		{
			ft_fdsfile(fds, &flag);
			execute_command(exe, arg, env);
			ft_strdel(&exe);
			if (fds->file > 0)
				close(fds->file);
			if (flag == 1)
				close(fds->open);
			exit(EXIT_SUCCESS);
		}
		else
		{
			shell_error(arg[0], NO_CMD);
			exit(EXIT_FAILURE);
		}
	}
}

void	ft_execute(t_list *node, char ***env, t_fds *fds)
{
	char	**arg;

	ft_check_for_file(fds, &node);
	if (!(arg = ft_lstochar((t_list**)&node->content)))
		return ;
	if (arg[0])
	{
		ft_set_fds(fds, &arg);
		if (MYCMD(arg[0]) || MYCMD2(arg[0]))
			ft_command(arg[0], (t_list*)node->content, env);
		else if (fds->hdoc == 1)
			ft_heredoc(fds, arg, *env, 0);
		else
			ft_exec(arg, *env, fds);
	}
	ft_del_arg(&arg);
}
