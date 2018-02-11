/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 16:56:03 by dvdovenk          #+#    #+#             */
/*   Updated: 2018/01/05 16:56:04 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int		check_correct(t_read *r)
{
	int		i;

	i = 0;
	while (r->cmd[i])
	{
		if (r->cmd[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

void	ft_lstpushsort(t_list **lst, t_list *new, int (*cmp)())
{
	t_list	*tmp;
	t_list	*last;

	if (!(*lst))
		*lst = new;
	else
	{
		tmp = *lst;
		last = NULL;
		while (tmp && (*cmp)(tmp->content, new->content) < 0)
		{
			last = tmp;
			tmp = tmp->next;
		}
		if (!last)
			ft_lstadd(lst, new);
		else
		{
			new->next = last->next;
			last->next = new;
		}
	}
}

char	ft_getchar(void)
{
	unsigned char	buf;
	ssize_t			len;

	len = read(0, &buf, 1);
	if (!len)
		return (0);
	else
		return (buf);
}

t_list	*ft_builtin(char *str)
{
	int		i;
	t_list	*lst;

	i = ft_strlen(str);
	lst = NULL;
	if (ft_strnequ("echo", str, i))
		ft_lstpushsort(&lst, ft_lstnew("echo", 5), &ft_strcmp);
	if (ft_strnequ("setenv", str, i))
		ft_lstpushsort(&lst, ft_lstnew("setenv", 7), &ft_strcmp);
	if (ft_strnequ("unsetenv", str, i))
		ft_lstpushsort(&lst, ft_lstnew("unsetenv", 9), &ft_strcmp);
	if (ft_strnequ("env", str, i))
		ft_lstpushsort(&lst, ft_lstnew("env", 4), &ft_strcmp);
	if (ft_strnequ("cd", str, i))
		ft_lstpushsort(&lst, ft_lstnew("cd", 3), &ft_strcmp);
	if (ft_strnequ("exit", str, i))
		ft_lstpushsort(&lst, ft_lstnew("exit", 5), &ft_strcmp);
	if (ft_strnequ("history", str, i))
		ft_lstpushsort(&lst, ft_lstnew("history", 8), &ft_strcmp);
	return (lst);
}

void	update_history(void)
{
	int	i;

	i = HISTORY_COUNT;
	if ((g_shell->history[0] &&
		ft_strequ(g_shell->history[0], g_shell->read->cmd)))
		return ;
	if (g_shell->history[i - 1])
	{
		ft_strdel(&g_shell->history[i - 1]);
		g_shell->history[i - 1] = NULL;
	}
	while (--i)
		g_shell->history[i] = g_shell->history[i - 1];
	g_shell->history[0] = ft_strdup(g_shell->read->cmd);
}
