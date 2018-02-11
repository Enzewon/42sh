/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 13:08:53 by skavunen          #+#    #+#             */
/*   Updated: 2018/01/26 13:08:53 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void		clear_slash(char **str)
{
	int		p;
	int		i;

	i = 0;
	if (!*str)
		return ;
	while ((*str)[i])
	{
		p = 0;
		while ((*str)[i + p] == '\\')
			p++;
		if (p != 0)
		{
			ft_memmove((*str) + i + p / 2, (*str) + i + p,
				ft_strlen((*str) + i + p) + 3);
			i += p / 2;
		}
		i++;
	}
}

void		read_exe_quote(char *s, char ***env, int fd[], t_list **node)
{
	char	*cmd;

	g_proc = -1;
	ft_shell(s, env);
	close(fd[1]);
	while (get_next_line(fd[0], &cmd) > 0)
	{
		ft_lstpushback(node, cmd, ft_strlen(cmd) + 1);
		free(cmd);
	}
	close(fd[0]);
}
