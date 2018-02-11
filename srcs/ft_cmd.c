/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 11:37:05 by skavunen          #+#    #+#             */
/*   Updated: 2017/08/21 17:35:01 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

t_list			*ft_node_split(t_list *list, char *split)
{
	t_list		*new;
	t_list		*ret;
	char		*str;
	t_list		*node;

	node = list;
	new = ft_lstnew(NULL, 0);
	ret = new;
	while (node)
	{
		str = node->content;
		if (ft_strcmp(str, split) == 0)
		{
			new->next = ft_lstnew(NULL, 0);
			new = new->next;
		}
		else
			ft_lstpushback((t_list**)&new->content, node->content,
			node->content_size);
		node = node->next;
	}
	return (ret);
}
