/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 13:13:36 by skavunen          #+#    #+#             */
/*   Updated: 2017/08/22 13:12:54 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void			ft_un_fds(t_fds **del)
{
	t_fds		*fds;

	fds = *del;
	if (fds->file > 0)
		close(fds->file);
	close(fds->fd[0]);
	close(fds->fd[1]);
	if (!fds->in)
	{
		close(fds->ex[0]);
		close(fds->ex[1]);
	}
	dup2(fds->mem1, 1);
	dup2(fds->mem2, 0);
	dup2(fds->mem3, 2);
	close(fds->mem1);
	close(fds->mem2);
	close(fds->mem3);
	if (fds->hered)
		ft_strdel(&fds->hered);
	free(fds);
	*del = NULL;
}

void			ft_last_command(t_fds *fds, t_list *node, char ***env)
{
	if (fds->in != 0)
	{
		dup2(fds->in, 0);
		close(fds->in);
		fds->in = 0;
	}
	ft_execute(node, env, fds);
	ft_un_fds(&fds);
}

void			ft_exe_pipes(t_list **list, char ***env)
{
	t_fds		*fds;
	t_list		*node;
	char		**arg;

	node = *list;
	fds = ft_init_fds();
	ft_check_for_file(fds, &node);
	while (node->next != NULL)
	{
		if (!(arg = ft_lstochar((t_list**)&node->content)))
			return ;
		ft_set_fds(fds, &arg);
		if (fds->hdoc == 1)
			ft_heredoc(fds, arg, *env, 1);
		else
			ft_exec_pipe(fds, arg, *env);
		close(fds->fd[1]);
		if (fds->in != 0)
			close(fds->in);
		fds->in = fds->fd[0];
		ft_del_arg(&arg);
		ft_del_list((t_list**)&node->content);
		node = node->next;
	}
	ft_last_command(fds, node, env);
}
