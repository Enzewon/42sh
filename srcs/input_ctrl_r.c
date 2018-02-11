/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_ctrl_r.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 16:58:20 by dvdovenk          #+#    #+#             */
/*   Updated: 2018/01/05 16:58:20 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static void	print_find_str(char *big, char *little, int i, int j)
{
	while (big[++i] != '\0')
	{
		j = 0;
		while (big[i + j] && big[i + j] == little[j])
			j++;
		if (little[j] == '\0')
		{
			termcap_do("so");
			termcap_do("us");
			ft_putstr(little);
			termcap_do("se");
			termcap_do("ue");
			i += j;
		}
		if (big[i] == '\n')
		{
			termcap_do("do");
			termcap_do("cr");
		}
		else
			ft_putchar(big[i]);
	}
}

static void	find_str(char *tmp, t_read *read)
{
	int		i;

	i = -1;
	while (read->his[++i])
		if (ft_strstr(read->his[i], tmp) != NULL)
			break ;
	if (read->his[i] == NULL)
	{
		termcap_do("cr");
		termcap_do("cd");
		ft_printf("failed history search > %s_", tmp);
	}
	else
	{
		termcap_do("cr");
		termcap_do("cd");
		ft_printf("history search > ");
		print_find_str(read->his[i], tmp, -1, 0);
		read->cmd = read->his[i];
		read->his_pos = i;
	}
}

static void	add_char(char tmp[], int *i, t_read *read, char buf)
{
	tmp[(*i)] = buf;
	find_str(tmp, read);
	(*i)++;
}

static void	delete_char(char tmp[], int *i, t_read *read)
{
	(*i)--;
	tmp[(*i)] = '\0';
	find_str(tmp, read);
}

int			history_search(t_read *r)
{
	char	tmp[1024];
	int		i;

	termcap_home(r);
	termcap_do("cd");
	termcap_do("do");
	termcap_do("cr");
	termcap_do("vi");
	ft_printf("history search > ");
	i = 0;
	ft_bzero(tmp, 1024);
	while ((r->key[0] = ft_getchar()))
	{
		if (r->key[0] == 127 && i > 0)
			delete_char(tmp, &i, r);
		else if (!ft_isprint(r->key[0]))
			break ;
		else
			add_char(tmp, &i, r, r->key[0]);
	}
	termcap_do("ve");
	termcap_do("up");
	termcap_goto("ch", 0, r->cursor_start);
	print(r);
	return (1);
}
