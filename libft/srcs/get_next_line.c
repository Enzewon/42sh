/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 08:58:26 by dvdovenk          #+#    #+#             */
/*   Updated: 2017/02/01 14:14:56 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list			*destroy_part(t_list *curr, char *content)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (content[i] && content[i] != '\n')
		i++;
	j = i;
	while (content[j])
		j++;
	tmp = ft_strsub(content, i + 1, j - i);
	ft_memdel(&curr->content);
	curr->content = tmp;
	return (curr);
}

char			*take_part(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (ft_strsub(str, 0, i));
}

static t_list	*get_file(t_list **file, int fd)
{
	t_list	*tmp;

	tmp = *file;
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = ft_lstnew("\0", fd);
	ft_lstadd(file, tmp);
	tmp = *file;
	return (tmp);
}

t_list			*take_content(t_list *curr, char buf[BUFF_SIZE + 1])
{
	char	*tmp;

	if (!curr->content)
		curr->content = ft_strnew(0);
	tmp = curr->content;
	curr->content = ft_strjoin(curr->content, buf);
	ft_strdel(&tmp);
	return (curr);
}

int				get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	static t_list	*pull;
	int				ret;
	int				i;
	t_list			*curr;

	if ((fd < 0 || line == NULL || read(fd, buf, 0) < 0))
		return (-1);
	i = 0;
	curr = get_file(&pull, fd);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		curr = take_content(curr, buf);
		if (ft_strchr(curr->content, '\n'))
			break ;
	}
	if (ret == 0 && !ft_strlen(curr->content))
		return (0);
	*line = take_part(curr->content);
	curr = destroy_part(curr, curr->content);
	return (1);
}
