/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 17:07:00 by dvdovenk          #+#    #+#             */
/*   Updated: 2018/01/16 17:07:01 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static void	replace_env(int *i, int p, char **env, char **new)
{
	char	*tmp;
	char	*save;
	int		j;
	int		z;
	int		k;

	tmp = ft_strsub(*new, (*i), p);
	j = find_env_var(tmp, env);
	free(tmp);
	if (j == -1)
		return ;
	z = ft_strlen(ft_strchr(env[j], '=') + 1);
	k = ft_strlen(*new + (*i) + p);
	save = ft_strsub((*new), 0, (*i) - 1);
	tmp = ft_strsub((*new), (*i) + p, k + 1);
	ft_strdel(new);
	*new = ft_strjoin(save, ft_strchr(env[j], '=') + 1);
	ft_strdel(&save);
	save = ft_strjoin(*new, tmp);
	ft_strdel(new);
	ft_strdel(&tmp);
	*new = save;
	(*i) += z;
}

static void	replace_home(char **env, int *i, char **new)
{
	char	*save;
	char	*tmp;
	int		j;
	int		z;
	int		k;

	j = find_env_var("HOME", env);
	if (j != -1)
	{
		z = ft_strlen(env[j] + 5);
		k = ft_strlen(*new + (*i));
		save = ft_strsub((*new), 0, (*i));
		tmp = ft_strsub((*new), (*i) + 1, k + 1);
		ft_strdel(new);
		*new = ft_strjoin(save, env[j] + 5);
		ft_strdel(&save);
		save = ft_strjoin(*new, tmp);
		ft_strdel(new);
		ft_strdel(&tmp);
		*new = save;
		(*i) += z;
	}
}

static void	fill_env(char **input, char **env)
{
	int		i;
	char	*new;
	int		p;

	i = 0;
	p = 0;
	new = ft_strdup(*input);
	while (new[i])
	{
		p = 0;
		if (new[i] == '~' && (new[i - 1] == ' ' || i == 0) &&
			(new[i + 1] == '/' || new[i + 1] == '\0' || new[i + 1] == ' '))
			replace_home(env, &i, &new);
		if (new[i] == '$')
		{
			i++;
			while (ft_isalnum(new[i + p]) ||
				new[i + p] == '_')
				p++;
			p > 0 ? replace_env(&i, p, env, &new) : NULL;
		}
		i++;
	}
	ft_strdel(input);
	*input = new;
}

void		ft_is_quote(char **str, int *a, char **ar, char ***env)
{
	char	ch;
	char	*arg;
	char	*save;
	int		st;

	st = (*a) + 1;
	arg = *str;
	ch = arg[(*a)];
	while (arg[++(*a)] && arg[(*a)] != ch)
		;
	*ar = ft_strsub(arg, st, (*a) - st);
	if (ch == '\"')
	{
		fill_env(ar, *env);
		save = (*ar);
		*ar = ft_strdup(save);
		ft_strdel(&save);
	}
}

void		ft_exe_quote(char **str, int *a, t_list **node, char ***env)
{
	int		st;
	char	*save;
	char	*tmp;
	char	*cmd;
	int		fd[2];

	st = (*a) + 1;
	tmp = *str;
	while (tmp[++(*a)] && tmp[(*a)] ^ tmp[st - 1])
		;
	cmd = ft_strsub(tmp, st, (*a) - st);
	if (cmd[0] == '\0')
	{
		free(cmd);
		return ;
	}
	tmp = cmd;
	cmd = ft_strjoin(cmd, " 1>&");
	free(tmp);
	pipe(fd);
	tmp = ft_itoa(fd[1]);
	save = ft_strjoin(cmd, tmp);
	free(tmp);
	free(cmd);
	read_exe_quote(save, env, fd, node);
}
