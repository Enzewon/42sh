/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 12:55:59 by skavunen          #+#    #+#             */
/*   Updated: 2017/08/22 17:15:13 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void			ft_set_redirect(char ***str, int i, t_fds *fds)
{
	char		**arg;
	char		*file;

	arg = *str;
	file = ft_strdup(arg[++i]);
	if ((fds->in = open(file, O_RDONLY)) < 0)
	{
		ft_fprintf(2, "42sh: No Such File: %s\n", file);
		fds->in = -3;
	}
	i--;
	while (arg[i])
	{
		ft_strdel(&arg[i]);
		i++;
	}
	ft_strdel(&file);
}

void			ft_set_amper(char ***str, int i, t_fds *fds)
{
	char		**arg;

	arg = *str;
	fds->close = arg[i][0] - '0';
	if (arg[i][3] && arg[i][3] != '-')
		fds->open = arg[i][3] - '0';
	else
		fds->open = -2;
	while (arg[i])
	{
		ft_strdel(&arg[i]);
		i++;
	}
}

void			ft_set_heredoc(char ***str, int i, t_fds *fds)
{
	char		**arg;

	arg = *str;
	fds->hered = ft_strdup(arg[i + 1]);
	fds->hdoc = 1;
	while (arg[i])
	{
		ft_strdel(&arg[i]);
		i++;
	}
}

void			ft_renew(t_fds *fds)
{
	fds->close = -1;
	fds->open = -1;
}

void			ft_set_fds(t_fds *fds, char ***str)
{
	int			i;
	char		**arg;

	arg = *str;
	i = -1;
	ft_renew(fds);
	pipe(fds->fd);
	while (arg[++i])
	{
		if (arg[i][0] == '<' && arg[i][1] == '\0')
			ft_set_redirect(str, i, fds);
		else if (ft_isdigit(arg[i][0]) && arg[i][1] == '>' && arg[i][2] == '&')
			ft_set_amper(str, i, fds);
		else if (ft_strcmp(arg[i], "<<") == 0)
			ft_set_heredoc(str, i, fds);
	}
}
