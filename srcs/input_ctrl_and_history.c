/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_ctrl_and_history.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 16:53:52 by dvdovenk          #+#    #+#             */
/*   Updated: 2018/01/05 16:53:53 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int		history_up(t_read *read)
{
	if (read->his && read->his[read->his_pos + 1])
	{
		read->his_pos++;
		termcap_home(read);
		termcap_do("cd");
		read->cmd = read->his[read->his_pos];
		print_str(read);
		read->size = read->pos;
	}
	return (1);
}

int		history_down(t_read *read)
{
	if (read->his && read->his_pos > 0 && read->his[read->his_pos - 1])
	{
		read->his_pos--;
		termcap_home(read);
		termcap_do("cd");
		read->cmd = read->his[read->his_pos];
		print_str(read);
		read->size = read->pos;
	}
	return (1);
}

int		reset_line(t_read *read)
{
	if (!read->heredoc)
	{
		termcap_end(read);
		read->cmd = read->his[0];
		ft_bzero(read->cmd, 1024);
		termcap_do("do");
		termcap_do("cr");
		ft_fprintf(2, "{#bold}{#yellow}%s {#green}/~> {#eoc}", read->prompt);
		read->his_pos = 0;
		read->pos = 0;
		read->size = 0;
	}
	else
		read->work = -2;
	return ((read->work == -2 ? 0 : 1));
}

int		end_reading(t_read *read)
{
	if (read->cmd[0])
		return (1);
	read->work = -1;
	return (0);
}
