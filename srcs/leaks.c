/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 14:21:08 by skavunen          #+#    #+#             */
/*   Updated: 2017/08/22 19:00:42 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void			ft_del_tmp(t_list **tmp)
{
	t_list		*node;
	t_list		*next;

	node = *tmp;
	while (node)
	{
		next = node->next;
		free(node);
		node = next;
	}
}

void			ft_del_list(t_list **list)
{
	t_list		*node;
	t_list		*next;

	node = *list;
	while (node)
	{
		next = node->next;
		if (node->content)
			ft_memdel(&node->content);
		ft_memdel((void**)&node);
		node = next;
	}
	*list = NULL;
}

void			ft_del_split(t_list **list)
{
	t_list		*node;
	t_list		*next;
	t_list		*del;

	node = *list;
	while (node)
	{
		next = node->next;
		if (node->content)
		{
			del = node->content;
			ft_del_list(&del);
		}
		ft_memdel((void**)&node);
		node = next;
	}
	*list = NULL;
}

void			ft_del_arg(char ***str)
{
	char		**arg;
	int			a;

	arg = *str;
	a = 0;
	while (arg[a])
		ft_strdel(&arg[a++]);
	free(arg);
	*str = NULL;
}

void			ft_reset_tab(t_inp *inp)
{
	inp->cplind = -1;
	if (inp->cpl)
		ft_del_list(&inp->cpl);
}
