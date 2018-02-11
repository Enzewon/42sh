/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_termcap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 16:54:48 by dvdovenk          #+#    #+#             */
/*   Updated: 2018/01/05 16:54:48 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int		termcap_putchar(int c)
{
	write(2, &c, 1);
	return (0);
}

int		termcap_do(char *key)
{
	char	*tmp;

	if ((tmp = tgetstr(key, NULL)) == NULL)
		return (1);
	tputs(tmp, 0, termcap_putchar);
	return (0);
}

int		termcap_goto(char *key, int col, int row)
{
	char	*tmp;

	if ((tmp = tgetstr(key, NULL)) == NULL)
		return (1);
	tmp = tgoto(tmp, col, row);
	tputs(tmp, 0, termcap_putchar);
	return (0);
}

int		termcap_end(t_read *read)
{
	while (read->cmd[read->pos])
		term_go_forward(read);
	return (1);
}

void	place_cursor(t_read *read)
{
	while (read->pos != read->remember_insert)
		term_go_forward(read);
}
