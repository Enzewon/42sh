/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 18:18:40 by dvdovenk          #+#    #+#             */
/*   Updated: 2018/01/05 18:18:41 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int			ft_chrlen(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i);
	return (-1);
}

int			find_env_var(char *n, char **env)
{
	int	i;
	int	j;

	i = -1;
	while (env[++i])
	{
		if (env[i][0] == n[0] &&
			(j = ft_chrlen(env[i], '=')) == (int)ft_strlen(n) &&
			ft_strncmp(n, env[i], j) == 0)
			return (i);
	}
	return (-1);
}

static void	hash_table_path(t_hash *hash, char *str, int start, int end)
{
	struct dirent	*ent;
	DIR				*dir;
	char			*path;

	path = ft_strsub(str, start, end - start);
	if (!(dir = opendir(path)))
	{
		ft_strdel(&path);
		return ;
	}
	while ((ent = readdir(dir)))
	{
		if (ft_strcmp(ent->d_name, ".") != 0 &&
			ft_strcmp(ent->d_name, "..") != 0)
			add_string(hash, ent->d_name, path);
	}
	ft_strdel(&path);
	closedir(dir);
}

void		make_hash_table(char **env)
{
	t_hash	*hash;
	char	*str;
	int		k;
	int		j;
	int		p;

	j = -1;
	p = 0;
	g_hash = NULL;
	if ((k = find_env_var("PATH", env)) == -1 ||
		!(str = (ft_strchr(env[k], '=') + 1)))
		return ;
	hash = create_hash_table(MAX_HASH_SIZE);
	while (str[++j])
	{
		if (str[j] == ':' || (str[j + 1] == '\0' && j++))
		{
			hash_table_path(hash, str, p, j);
			p = j + 1;
		}
	}
	g_hash = hash;
}
