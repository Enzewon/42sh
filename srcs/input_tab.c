/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 16:54:21 by dvdovenk          #+#    #+#             */
/*   Updated: 2018/01/05 16:54:22 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	complete_word(t_read *read, t_list *lst, char *tmp)
{
	int		size;

	if (read->size < 1000 && (size = ft_strlen(lst->content) - ft_strlen(tmp)))
	{
		read->remember_insert = read->pos + size;
		if (lst->next)
		{
			ft_print_multicolumn(read, lst, 0, 0);
			ft_fprintf(2, "{#bold}{#yellow}%s {#green}/~> {#eoc}",
						read->prompt);
			read->pos = 0;
		}
		termcap_home(read);
		ft_memmove(read->cmd + read->remember_insert,
			read->cmd + read->remember_insert - size,
			ft_strlen(read->cmd + read->remember_insert - size) + 1);
		ft_memcpy(read->cmd + read->remember_insert - size,
				lst->content + ft_strlen(tmp), size);
		print_str(read);
		termcap_home(read);
		place_cursor(read);
		read->size += size;
	}
}

t_list	*find_exec_path(t_hash *hash, char *exe)
{
	int		j;
	t_item	*tmp;
	t_list	*lst;

	j = -1;
	lst = NULL;
	while (++j < MAX_HASH_SIZE)
	{
		tmp = hash->table[j];
		while (tmp)
		{
			if (tmp && tmp->name[0] == exe[0] &&
				ft_strncmp(tmp->name, exe, ft_strlen(exe)) == 0)
				ft_lstpushsort(&lst,
				ft_lstnew(tmp->name, ft_strlen(tmp->name) + 1), &ft_strcmp);
			tmp = tmp->next;
		}
	}
	return (lst);
}

void	take_file(t_read *read, char *tmp)
{
	char	*exe;
	char	*path;
	t_list	*lst;

	path = take_path(tmp, read);
	exe = take_exe(tmp);
	if (!path)
		path = ft_strdup(".");
	lst = ft_find_in_dir(path, exe);
	if (lst)
	{
		complete_word(read, lst, exe);
		ft_del_list(&lst);
	}
	else
	{
		termcap_do("vb");
		termcap_do("bl");
	}
	ft_strdel(&path);
	ft_strdel(&exe);
}

void	take_first_command(t_read *read, char *tmp)
{
	t_list	*lst;

	if (read->hash && (lst = find_exec_path(read->hash, tmp)))
	{
		complete_word(read, lst, tmp);
		ft_del_list(&lst);
	}
	else
		take_file(read, tmp);
}

int		tab_complete(t_read *read)
{
	char	*tmp;
	t_list	*lst;

	tmp = take_word(read->cmd, read->pos, ' ');
	if (!tmp)
		return (1);
	else if (tmp[0] == '\0')
	{
		ft_strdel(&tmp);
		return (1);
	}
	else if (ft_first_cmd(read->cmd, read->pos))
	{
		if ((lst = ft_builtin(tmp)))
		{
			complete_word(read, lst, tmp);
			ft_del_list(&lst);
		}
		else
			take_first_command(read, tmp);
	}
	else
		take_file(read, tmp);
	ft_strdel(&tmp);
	return (1);
}
