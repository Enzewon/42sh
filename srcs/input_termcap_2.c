/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_termcap_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 16:55:09 by dvdovenk          #+#    #+#             */
/*   Updated: 2018/01/05 16:55:10 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	print_str(t_read *read)
{
	int	a;

	a = read->cursor_start;
	while (read->cmd[read->pos])
	{
		if (read->cmd[read->pos] == '\n')
		{
			termcap_do("do");
			termcap_do("cr");
			a = -1;
		}
		else
			ft_putchar_fd(read->cmd[read->pos], 2);
		if (g_width != 0 && a > 0 &&
			(a + 1) % (g_width) == 0)
		{
			termcap_do("do");
			termcap_do("cr");
			a = -1;
		}
		read->pos++;
		a++;
	}
}

void	print(t_read *read)
{
	termcap_home(read);
	termcap_do("cd");
	print_str(read);
}

void	go_up(t_read *read)
{
	int	i;

	i = read->pos - 2;
	while (i > 0 && read->cmd[i] != '\n')
		i--;
	termcap_do("up");
	i <= 0 ? termcap_goto("ch", 0,
			(read->pos - 1 + read->cursor_start) % g_width) :
			(termcap_goto("ch", 0, ((read->pos - 2 - i)) % g_width));
}

int		term_go_backward(t_read *read)
{
	if ((read->linez = ft_strrnchr_pos(read->cmd, '\n', read->pos)) != -1)
	{
		if (read->cmd[read->pos - 1] == '\n')
			go_up(read);
		else if (g_width != 0 && ((read->pos - read->linez - 1) % g_width) == 0)
		{
			termcap_do("up");
			termcap_goto("ch", 0, g_width - 1);
		}
		else
			termcap_do("le");
	}
	else if (g_width != 0 &&
		((read->pos + read->cursor_start) % g_width) == 0)
	{
		termcap_do("up");
		termcap_goto("ch", 0, g_width - 1);
	}
	else
		termcap_do("le");
	read->pos--;
	return (1);
}

int		term_go_forward(t_read *read)
{
	read->pos++;
	if ((read->linez = ft_strrnchr_pos(read->cmd, '\n', read->pos)) != -1)
	{
		if (read->cmd[read->pos - 1] == '\n')
		{
			termcap_do("do");
			termcap_do("cr");
		}
		else if (g_width != 0 && ((read->pos - read->linez - 1) % g_width) == 0)
		{
			termcap_do("do");
			termcap_do("cr");
		}
		else
			termcap_do("nd");
	}
	else if (g_width != 0 &&
		((read->pos + read->cursor_start) % g_width) == 0)
	{
		termcap_do("do");
		termcap_do("cr");
	}
	else
		termcap_do("nd");
	return (1);
}
