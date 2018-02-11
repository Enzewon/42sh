/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 15:39:56 by skavunen          #+#    #+#             */
/*   Updated: 2017/08/21 17:20:16 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	ft_lstpushback(t_list **lst, void *content, size_t size)
{
	t_list	*node;

	node = *lst;
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = ft_lstnew(content, size);
	}
	else
		*lst = ft_lstnew(content, size);
}

int		ft_put(int ch)
{
	write(1, &ch, 1);
	return (1);
}

int		ft_lst_len(t_list *list)
{
	t_list	*node;
	int		len;

	node = list;
	len = 0;
	while (node)
	{
		len++;
		node = node->next;
	}
	return (len);
}

char	**ft_lstochar(t_list **list)
{
	t_list	*node;
	char	**new;
	int		a;

	a = 0;
	if (make_glob(list) ^ 1)
		return (NULL);
	node = *list;
	new = (char**)malloc(sizeof(char*) * ft_lst_len(node) + 1);
	while (node)
	{
		if (g_shell->history[1] && ft_strequ((char*)node->content, "!!"))
			new[a++] = ft_strdup(g_shell->history[1]);
		else
			new[a++] = ft_strdup(node->content);
		node = node->next;
	}
	new[a] = NULL;
	return (new);
}
