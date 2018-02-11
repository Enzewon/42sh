/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_show_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 20:34:42 by dvdovenk          #+#    #+#             */
/*   Updated: 2018/01/22 20:34:43 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	ft_place_tab(size_t len, int max)
{
	size_t	count;
	size_t	i;

	count = (max - len) / 8;
	ft_place_shift_fd((max - len) % 8, 1);
	i = 0;
	while (i < count)
	{
		ft_putchar('\t');
		i++;
	}
}

void	ft_make_print(t_read *read, char **table, int i, int *size)
{
	int		k;
	int		tm;
	int		j;

	j = -1;
	while (++j < i)
	{
		tm = i;
		k = j;
		while (k < *size)
		{
			ft_putstr(table[k]);
			if (k + i < *size)
				ft_place_tab(ft_strlen(table[k]), read->height);
			k += i;
		}
		termcap_do("do");
		termcap_do("cr");
		i = tm;
	}
}

int		take_max(t_list *list, int *size)
{
	t_list	*tmp;
	int		max;
	int		z;

	tmp = list;
	max = 0;
	(*size) = 0;
	while (tmp)
	{
		z = ft_strlen(tmp->content);
		if (z > max)
			max = z;
		(*size)++;
		tmp = tmp->next;
	}
	return (max);
}

void	ft_print_multicolumn(t_read *read, t_list *lst, int k, int col)
{
	char	**table;
	int		j;
	int		i;

	termcap_end(read);
	termcap_do("do");
	termcap_do("cr");
	read->height = take_max(lst, &j) + 8;
	col = g_width / read->height;
	if (g_width - ((col * read->height) - 8) >= read->height)
		col++;
	i = j / col;
	if (j % col != 0)
		i++;
	table = (char**)ft_memalloc(sizeof(char*) * (j + 1));
	k = -1;
	while (lst)
	{
		table[++k] = ft_strdup(lst->content);
		lst = lst->next;
	}
	table[++k] = NULL;
	ft_make_print(read, table, i, &j);
	ft_strdel_array(table);
}
