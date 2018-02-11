/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_tools_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 16:56:37 by dvdovenk          #+#    #+#             */
/*   Updated: 2018/01/05 16:56:38 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	replace_home_input(char **env, int i, char *new)
{
	int		j;
	int		z;
	int		k;

	j = find_env_var("HOME", env);
	if (j != -1)
	{
		z = ft_strlen(env[j] + 5);
		k = ft_strlen(new + i);
		ft_memmove(new + i + z - 1, new + i, k + 1);
		ft_memcpy(new + i, env[j] + 5, z);
	}
}

char	*take_word(char *line, int count, char ch)
{
	int		i;
	char	*tmp;

	if (count == 0)
		return (NULL);
	i = count;
	if (i > 0 && line[i] == ch && line[i - 1] != ch)
		i--;
	while (i > 0 && line[i] != ch)
		i--;
	if (line[i] == ch)
		i++;
	if (count == i)
		return (NULL);
	tmp = ft_strnew(count - i + 2);
	ft_memcpy(tmp, line + i, count - i);
	tmp[count - i] = '\0';
	return (tmp);
}

char	*take_path(char *tmp, t_read *read)
{
	int		i;
	int		p;
	char	*path;

	i = 0;
	p = -1;
	if (tmp[0] == '~')
		p = 0;
	while (tmp[i])
	{
		if (tmp[i] == '/')
			p = i;
		i++;
	}
	if (p == -1)
		return (NULL);
	path = ft_strnew(200);
	ft_memcpy(path, tmp, p + 1);
	if (path[0] == '~')
		replace_home_input(read->env, 0, path);
	return (path);
}

char	*take_exe(char *tmp)
{
	int		i;
	int		p;
	char	*exe;

	i = 0;
	p = -1;
	while (tmp[i])
	{
		if (tmp[i] == '/')
			p = i;
		i++;
	}
	if (p == -1)
		return (ft_strdup(tmp));
	p++;
	exe = ft_strnew(i - p + 1);
	ft_memcpy(exe, tmp + p, i - p);
	return (exe);
}

t_list	*ft_find_in_dir(char *path, char *exe)
{
	DIR				*dir;
	struct dirent	*ent;
	t_list			*lst;

	lst = NULL;
	if (!(dir = opendir(path)))
		return (NULL);
	while ((ent = readdir(dir)) != NULL)
		if (exe[0] != '\0' &&
			ft_strncmp(ent->d_name, exe, ft_strlen(exe)) == 0)
			ft_lstpushsort(&lst, ft_lstnew(ent->d_name,
						ft_strlen(ent->d_name) + 1), &ft_strcmp);
	closedir(dir);
	return (lst);
}
