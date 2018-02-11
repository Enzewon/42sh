/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globtools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 13:57:40 by skavunen          #+#    #+#             */
/*   Updated: 2018/01/25 13:57:41 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void			parse_file_tool(t_list **new, char *name, char *path)
{
	char		*tmp;
	char		*tmp2;

	tmp = ft_strjoin(path, "/");
	tmp2 = ft_strjoin(!(path[1] ^ 0) && !(path[0] ^ '/') ?
	path : tmp, name);
	ft_lstpushback(new, tmp2, ft_strlen(tmp2) + 1);
	free(tmp);
	free(tmp2);
}

int				need_glob(char *str)
{
	int			i;

	i = -1;
	while (str[++i])
	{
		if (!(str[i] ^ '"') || !(str[i] ^ '\'') || !(str[i] ^ '`'))
			return (0);
		if (!(str[i] ^ '*') || !(str[i] ^ '?') || !(str[i] ^ '[') ||
		!(str[i] ^ '{'))
			return (1);
	}
	return (0);
}

int				file_is_dir(char *path, char *name)
{
	char		*tmp;
	char		*tmp2;
	struct stat buf;

	tmp = ft_strjoin(path, "/");
	tmp2 = ft_strjoin(!(path[1] ^ 0) && !(path[0] ^ '/') ? path : tmp, name);
	lstat(tmp2, &buf);
	free(tmp);
	free(tmp2);
	return (S_ISDIR(buf.st_mode) || S_ISLNK(buf.st_mode) ? 1 : 0);
}

void			figure_glob(t_list *st, char *s, char *path)
{
	int			i;
	int			pos;
	char		*tmp;
	char		*glob;

	if (ft_strchr(s, ','))
	{
		if ((tmp = ft_strstr(s, "{")) != s || !ft_strchr(tmp, '}'))
			return ;
		i = -1;
		pos = 1;
		while (tmp[++i])
			if (!(tmp[i] ^ ',') || !(tmp[i] ^ '}'))
			{
				glob = ft_strsub(tmp, pos, i - pos);
				push_n_glob(st, glob, path);
				pos = i + 1;
				free(glob);
			}
	}
}
