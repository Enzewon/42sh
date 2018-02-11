/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 14:09:34 by skavunen          #+#    #+#             */
/*   Updated: 2017/06/14 12:57:32 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static int	take_env_name(char *str)
{
	int	i;

	i = 0;
	while (ft_isalnum(str[i]) || str[i] == '_')
	{
		if (str[i + 1] == '=' && str[i + 2] != '=')
			return (1);
		else if (str[i + 1] == '=' && str[i + 2] == '=')
			return (2);
		i++;
	}
	return (0);
}

static char	*split_env_var(char *n)
{
	int i;

	i = -1;
	while (n[++i])
		if (n[i] == '=')
			return (ft_strsub(n, 0, i));
	return (NULL);
}

void		place_env(char *n, char **env)
{
	int		i;
	char	*tmp;

	tmp = split_env_var(n);
	i = find_env_var(tmp, env);
	if (i == -1)
	{
		i = ft_arrlen(env) - 1;
		env[i + 1] = env[i];
		env[i] = ft_strdup(n);
		env[i + 2] = NULL;
	}
	else
	{
		ft_strdel(&env[i]);
		env[i] = ft_strdup(n);
	}
	if (ft_strcmp(tmp, "PATH") == 0)
	{
		free_table(g_hash);
		make_hash_table(env);
	}
	ft_strdel(&tmp);
}

void		place_exepath_env(char *n, char **env, int j)
{
	char	*tmp;
	char	*line;
	char	*tmp2;
	t_item	*exe;

	line = ft_strchr(n, '=') + 2;
	if ((j = find_env_var("PATH", env)) != -1 &&
		(exe = lookup_string(g_hash, line)))
	{
		tmp = split_env_var(n);
		tmp2 = ft_strjoin(tmp, "=");
		ft_strdel(&tmp);
		tmp = ft_strjoin(tmp2, exe->value);
		ft_strdel(&tmp2);
		place_env(tmp, env);
		ft_strdel(&tmp);
	}
	else
		ft_fprintf(2, "42sh: %s not found\n", line);
}

void		ft_m_setenv(t_list *list, char ***env)
{
	t_list	*node;
	int		z;

	node = list->next;
	while (node)
	{
		z = take_env_name(node->content);
		if (z == 1)
			place_env(node->content, *env);
		else if (z == 2)
			place_exepath_env(node->content, *env, 0);
		else
			ft_fprintf(2, "42sh: invalid argument: %s\n", node->content);
		node = node->next;
	}
}
