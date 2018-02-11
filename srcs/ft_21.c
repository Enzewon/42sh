/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_21.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/15 15:20:18 by skavunen          #+#    #+#             */
/*   Updated: 2017/08/23 14:02:13 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	ft_add_hist(char *arg)
{
	t_list	*new;

	new = ft_lstnew(arg, ft_strlen(arg) + 1);
	ft_lstadd(&g_hist, new);
}

void	ft_shell(char *arg, char ***env)
{
	t_list	*node;
	t_list	*split;
	t_list	*comm;
	t_list	*tmp;

	if (arg && arg[0] != '\0')
	{
		node = ft_get_args(&arg, env, NULL, 0);
		ft_add_hist(arg);
		comm = ft_node_split(node, ";");
		tmp = comm;
		while (comm)
		{
			split = comm->content;
			msh_logical(split, env);
			ft_del_list(&split);
			comm = comm->next;
		}
		ft_del_tmp(&tmp);
		ft_del_list(&node);
	}
	ft_strdel(&arg);
}

void	ft_21sh(char ***env)
{
	char	*arg;

	ft_printf("\033c");
	make_intro();
	if (env)
		while (42)
		{
			g_proc = -1;
			arg = read_input();
			if (!ft_strncmp(arg, "exit", 4) || !ft_strncmp(arg, "exit ", 5))
				exit(EXIT_SUCCESS);
			termcap_do("cd");
			if (ft_check_arg(&arg))
				ft_shell(arg, env);
			else
				ft_strdel(&arg);
			g_shell->env = *env;
		}
}
