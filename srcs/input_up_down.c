/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_up_down.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 16:59:04 by dvdovenk          #+#    #+#             */
/*   Updated: 2018/01/05 16:59:05 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int		insert_enter(t_read *read)
{
	read->work = 0;
	termcap_end(read);
	return (read->work);
}

void	cursor_down_tools_2(t_read *read, int current_x)
{
	int	need_x;

	if (current_x - read->pos > g_width - ((read->pos - read->linez) % g_width))
	{
		while (read->cmd[read->pos] != '\n')
			term_go_forward(read);
	}
	else
	{
		need_x = (read->pos - read->linez) % g_width;
		while (read->cmd[read->pos] != '\n')
			term_go_forward(read);
		need_x--;
		if (read->pos != read->size - 1)
			term_go_forward(read);
		while (need_x-- && read->cmd[read->pos] != '\n' &&
			read->pos != read->size - 1)
			term_go_forward(read);
	}
}

void	cursor_down_tools_1(t_read *read, int current_x)
{
	int	need_x;

	if (current_x - read->pos > g_width - ((read->pos +
		read->cursor_start) % g_width))
	{
		while (read->cmd[read->pos] != '\n')
			term_go_forward(read);
	}
	else
	{
		need_x = (read->pos + read->cursor_start) % g_width;
		while (read->cmd[read->pos] != '\n')
			term_go_forward(read);
		if (read->pos != read->size - 1)
			term_go_forward(read);
		while (need_x-- && read->cmd[read->pos] != '\n' &&
				read->pos != read->size - 1)
			term_go_forward(read);
	}
}

int		cursor_down_key(t_read *r)
{
	int		current_x;

	if (ft_strchr(r->cmd + r->pos, '\n'))
	{
		current_x = r->pos;
		while (r->cmd[current_x] != '\n')
			current_x++;
		if (current_x - r->pos > g_width)
		{
			termcap_do("do");
			r->pos += g_width;
		}
		else if ((r->linez = ft_strrnchr_pos(r->cmd, '\n', r->pos)) == -1)
			cursor_down_tools_1(r, current_x);
		else
			cursor_down_tools_2(r, current_x);
	}
	else if (r->size - 1 < r->pos + g_width)
		termcap_end(r);
	else
	{
		termcap_do("do");
		r->pos += g_width;
	}
	return (1);
}
