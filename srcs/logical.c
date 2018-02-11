/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_logical.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 16:43:01 by skavunen          #+#    #+#             */
/*   Updated: 2017/12/07 16:43:01 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	msh_logical2(t_list *and, char ***env, int *status)
{
	t_list	*or;
	t_list	*tmp;
	t_list	*pipes;

	or = ft_node_split(and, "||");
	tmp = or;
	while (or)
	{
		pipes = ft_node_split(or->content, "|");
		ft_exe_pipes(&pipes, env);
		waitpid(g_proc, status, 0);
		if (g_proc > 0)
			kill(g_proc, SIGKILL);
		ft_del_split(&pipes);
		if (WIFEXITED(*status) && WEXITSTATUS(*status) == EXIT_SUCCESS)
			break ;
		or = or->next;
	}
	ft_del_split(&tmp);
}

int		msh_logical(t_list *split, char ***env)
{
	t_list	*and;
	t_list	*tmp;
	int		status;

	and = ft_node_split(split, "&&");
	tmp = and;
	while (and)
	{
		msh_logical2((t_list*)and->content, env, &status);
		if (WIFEXITED(status) && WEXITSTATUS(status) != EXIT_SUCCESS)
			break ;
		and = and->next;
	}
	ft_del_split(&tmp);
	return (1);
}
