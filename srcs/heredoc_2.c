/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 16:12:26 by skavunen          #+#    #+#             */
/*   Updated: 2018/01/26 16:12:26 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void		put_heredoc(char *ret, int fd[])
{
	ft_putstr_fd(ret, fd[1]);
	close(fd[1]);
	free(ret);
	wait(NULL);
}

void		delete_it(t_read *new_read, char *tmp)
{
	ft_strdel(&tmp);
	ft_strdel(&new_read->prompt);
	ft_strdel(&new_read->cmd);
	free(new_read);
}
