/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_up_arrow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 21:56:20 by dvdovenk          #+#    #+#             */
/*   Updated: 2018/01/19 21:56:21 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	cursor_up_tools_2(t_read *read, int current_x, int tmp)
{
	tmp = (read->pos - read->linez) % g_width;
	if (current_x < tmp)
	{
		tmp -= current_x;
		while (tmp--)
			term_go_backward(read);
	}
}

void	cursor_up_tools(t_read *read, int current_x, int tmp)
{
	tmp = read->pos + read->cursor_start;
	if (tmp > g_width)
	{
		tmp %= g_width;
		if (current_x < tmp)
		{
			tmp -= current_x;
			tmp++;
			while (tmp--)
				term_go_backward(read);
		}
	}
	else
	{
		if (current_x < read->cursor_start)
			termcap_home(read);
		else
		{
			termcap_home(read);
			read->remember_insert = current_x - read->cursor_start - 1;
			place_cursor(read);
		}
	}
}

void	cursor_up_tools_main(t_read *read, int current_x)
{
	int	tmp;

	tmp = read->linez;
	while (read->pos != tmp)
		term_go_backward(read);
	if ((read->linez = ft_strrnchr_pos(read->cmd, '\n', read->pos)) == -1)
		cursor_up_tools(read, current_x, tmp);
	else
		cursor_up_tools_2(read, current_x, tmp);
}

int		cursor_up_key(t_read *read)
{
	int	current_x;

	if ((read->linez = ft_strrnchr_pos(read->cmd, '\n', read->pos)) != -1)
	{
		current_x = read->pos - read->linez;
		if (current_x > g_width)
		{
			read->pos -= g_width;
			termcap_do("up");
		}
		else
			cursor_up_tools_main(read, current_x);
	}
	else if (read->pos < g_width)
		termcap_home(read);
	else
	{
		termcap_do("up");
		read->pos -= g_width;
	}
	return (1);
}
