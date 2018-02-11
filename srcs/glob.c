/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:29:37 by skavunen          #+#    #+#             */
/*   Updated: 2018/01/11 16:29:37 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

t_list				*parse_files(char *path, char *s, t_list *new, int flag)
{
	struct dirent	*files;
	int				a;
	DIR				*d;

	if (!(d = opendir(path)))
		return (new);
	while ((files = readdir(d)))
	{
		if ((a = file_valid(files->d_name, s)) && files->d_name[0] ^ '.')
		{
			if (!flag || files->d_type == DT_DIR ||
			file_is_dir(path, files->d_name))
			{
				if (!(path[1] ^ 0) && !(path[0] ^ '.'))
					ft_lstpushback(&new, files->d_name, a);
				else
					parse_file_tool(&new, files->d_name, path);
			}
		}
	}
	closedir(d);
	return (new);
}

void				parse_path(t_list *st, char *s, char *path)
{
	int				a;
	char			*pa;
	t_list			*dirs;
	t_list			*tmp;

	a = -1;
	while (s[++a] ^ '/')
		;
	pa = ft_strsub(s, 0, a);
	dirs = parse_files(path, pa, NULL, 1);
	free(pa);
	tmp = dirs;
	while (dirs)
	{
		push_n_glob(st, s + a + 1, dirs->content);
		dirs = dirs->next;
	}
	ft_del_list(&tmp);
}

void				push_n_glob(t_list *st, char *s, char *path)
{
	t_list			*new;

	if (ft_strchr(s, '{'))
		figure_glob(st, s, path);
	else if (!(s[0] ^ '/'))
		push_n_glob(st, s + 1, "/");
	else if (ft_strchr(s, '/'))
		parse_path(st, s, path);
	else
		new = parse_files(path, s, st, 0);
}

int					prepare_glob(char *str, t_list **new)
{
	t_list			*tmp;

	tmp = *new;
	while (tmp && tmp->next)
		tmp = tmp->next;
	push_n_glob(tmp, str, ".");
	if (!tmp || !tmp->next)
	{
		ft_del_list(new);
		ft_printf("42sh: No Matches Found.\n");
		return (-1);
	}
	return (1);
}

int					make_glob(t_list **lst)
{
	t_list			*mv;
	t_list			*new;

	mv = *lst;
	new = NULL;
	while (mv)
	{
		if (need_glob((char*)mv->content))
		{
			if (prepare_glob((char*)mv->content, &new) < 0)
				return (-1);
		}
		else
			ft_lstpushback(&new, mv->content, mv->content_size);
		mv = mv->next;
	}
	ft_del_list(lst);
	*lst = new;
	return (1);
}
