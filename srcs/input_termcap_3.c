/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_termcap_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 22:03:19 by dvdovenk          #+#    #+#             */
/*   Updated: 2018/01/19 22:03:19 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int		ft_first_cmd(char *line, int count)
{
	int	i;

	i = count;
	if (line[i] == ' ' && line[i - 1] != ' ')
		i--;
	while (i > 0 && line[i] != ' ')
		i--;
	while (i > 0 && line[i] == ' ')
		i--;
	if (i == 0 || line[i] == ';' || line[i] == '|')
		return (1);
	return (0);
}

int		ft_strrnchr_pos(char const *src, int c, int len)
{
	int	pos;
	int	i;

	pos = -1;
	i = 0;
	while (src[i] && len)
	{
		if (src[i] == (unsigned char)c)
			pos = i;
		len--;
		i++;
	}
	if ((char)c == '\0')
		return (i);
	return (pos);
}

char	*ft_strnchr(char const *src, int c, int len)
{
	while (*src && len)
	{
		if (*src == (unsigned char)c)
			return ((char*)src);
		src++;
		len--;
	}
	if ((char)c == '\0')
		return ((char*)src);
	return (NULL);
}

int		termcap_home(t_read *read)
{
	while (read->pos > 0)
		term_go_backward(read);
	return (1);
}
