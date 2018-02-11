/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 12:58:03 by skavunen          #+#    #+#             */
/*   Updated: 2017/08/23 14:02:26 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	ft_file_fds(t_list **list, t_fds *fds, int flag)
{
	t_list	*node;
	char	*str;

	node = *list;
	node = node->next;
	if (node)
	{
		str = (char*)node->content;
		if (flag == 1)
			fds->file = open(str, O_WRONLY | O_CREAT | O_TRUNC,
			S_IWUSR | S_IRUSR);
		if (flag == 2)
			fds->file = open(str, O_WRONLY | O_CREAT | O_APPEND,
			S_IWUSR | S_IRUSR);
	}
}

void	ft_check_for_file(t_fds *fds, t_list **list)
{
	t_list	*check;
	char	*str;
	t_list	*node;
	int		flag;
	t_list	*prev;

	node = *list;
	while (node->next)
		node = node->next;
	check = (t_list*)node->content;
	while (check)
	{
		str = check->content;
		if (!ft_strcmp(str, ">>") || !ft_strcmp(str, ">"))
		{
			flag = (str[1] == '\0' ? 1 : 2);
			ft_file_fds(&check, fds, flag);
			ft_del_list(&check);
			prev->next = NULL;
			return ;
		}
		prev = check;
		check = check->next;
	}
}

int		ft_special(char *cmd, int *i)
{
	char	ch;
	int		tmp;

	if (SPEC(cmd[(*i)]))
	{
		ch = cmd[(*i)];
		tmp = (*i);
		while (cmd[tmp] == ch)
			tmp++;
		if (tmp - (*i) > 2)
			return (1);
		else if ((cmd[(*i)] == '|' && cmd[(*i) + 1] == '|' && (*i)++) ||
			(cmd[(*i)] == '&' && cmd[(*i) + 1] == '&' && (*i)++) ||
			(cmd[(*i)] == '>' && cmd[(*i) + 1] == '>' && (*i)++) ||
			(cmd[(*i)] == '<' && cmd[(*i) + 1] == '<' && (*i)++) ||
			(cmd[(*i)] == '|') || (cmd[(*i)] == '&') ||
			(cmd[(*i)] == '>' && cmd[(*i) + 1] != '&') ||
			(cmd[(*i)] == '<') || (cmd[(*i)] == ';'))
			return (1);
	}
	return (0);
}

int		ft_check_arg(char **arg)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	while ((*arg)[++i])
	{
		if (QUOTE((*arg)[i]))
			skip_quotes((*arg), &i);
		else if ((*arg)[i] != ' ' && !ft_special((*arg), &i))
			flag = 1;
		else if (ft_special((*arg), &i)
			&& flag == 0 && ft_fprintf(2, "42sh: Syntax Error\n"))
			return (0);
		else if (ft_special((*arg), &i) && flag == 1)
			flag = 0;
	}
	if (flag == 0 && ft_fprintf(2, "42sh: Syntax Error\n"))
		return (0);
	return (1);
}
