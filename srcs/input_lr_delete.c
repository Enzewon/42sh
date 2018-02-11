/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_lr_delete.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 16:52:10 by dvdovenk          #+#    #+#             */
/*   Updated: 2018/01/05 16:52:11 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int		cursor_left_key(t_read *read)
{
	if (read->pos > 0)
		term_go_backward(read);
	return (1);
}

int		cursor_right_key(t_read *read)
{
	if (read->cmd[read->pos])
		term_go_forward(read);
	return (1);
}

int		delete_key(t_read *read)
{
	if (read->pos >= 0 && read->cmd[read->pos])
	{
		read->size--;
		ft_memmove((read->cmd + read->pos), (read->cmd + read->pos + 1),
		ft_strlen(read->cmd + read->pos + 1) + 1);
		read->remember_insert = read->pos;
		print(read);
		termcap_home(read);
		place_cursor(read);
	}
	return (1);
}

int		backspace(t_read *read)
{
	if (read->pos > 0)
	{
		read->size--;
		read->remember_insert = read->pos;
		if (read->cmd[read->pos - 1] == '\n' || read->cmd[read->pos] == '\n')
			termcap_home(read);
		ft_memmove((read->cmd + read->remember_insert - 1),
			(read->cmd + read->remember_insert),
		ft_strlen(read->cmd + read->remember_insert) + 1);
		read->remember_insert--;
		print(read);
		termcap_home(read);
		place_cursor(read);
	}
	return (1);
}
