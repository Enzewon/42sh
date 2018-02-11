/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_pro.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 16:35:35 by dvdovenk          #+#    #+#             */
/*   Updated: 2018/01/05 16:35:36 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	get_line_again(t_read *read)
{
	ft_bzero(read->cmd, 1024);
	read->his_pos = 0;
	termcap_do("do");
	termcap_goto("ch", 0, 0);
	termcap_do("cd");
	read->work = 42;
	get_line(read);
}

void	insert_char(t_read *read, char key)
{
	if (read->size < 1000)
	{
		ft_memmove((read->cmd + read->pos + 1), (read->cmd + read->pos),
			ft_strlen(read->cmd + read->pos) + 1);
		read->size++;
		read->cmd[read->pos] = key;
		read->remember_insert = read->pos + 1;
		print(read);
		termcap_home(read);
		place_cursor(read);
	}
}

int		processing_key(t_read *read)
{
	int	status;

	if (read->key[0] == '\e')
		status = actions_extended(read);
	else
		status = actions_regular(read);
	return (status);
}

void	get_line(t_read *read)
{
	read->pos = 0;
	read->size = 0;
	ft_fprintf(2, "{#bold}{#yellow}%s {#green}/~> {#eoc}", read->prompt);
	while (read->work)
	{
		read->key[0] = ft_getchar();
		if (processing_key(read) == 0)
			break ;
	}
	if (read->work == 0 && !read->heredoc &&
		(read->cmd[0] == '\0' || !check_correct(read) || !check_quote(read)))
		get_line_again(read);
}

char	*read_input(void)
{
	char	*value;

	g_shell->read = read_init(g_shell->history, g_shell->prompt, g_shell->env,
		g_hash);
	controlled_termios(g_shell);
	get_line(g_shell->read);
	reset_termios(g_shell);
	if (g_shell->read->work == -1)
	{
		ft_printf("exit");
		value = ft_strdup("exit");
	}
	else
		value = ft_strdup(g_shell->read->cmd);
	update_history();
	delete_read(g_shell->read);
	free(g_shell->read);
	write(1, "\n", 1);
	return (value);
}
