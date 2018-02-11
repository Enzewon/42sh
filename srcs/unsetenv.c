/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 20:30:55 by dvdovenk          #+#    #+#             */
/*   Updated: 2018/01/22 20:30:56 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void		ft_m_unsetenv(t_list *list, char **env)
{
	t_list	*node;
	int		i;
	int		a;

	a = -1;
	node = list->next;
	while (node)
	{
		i = find_env_var(node->content, env);
		if (i != -1)
		{
			if (ft_strcmp(node->content, "PATH") == 0)
			{
				free_table(g_hash);
				g_hash = NULL;
			}
			ft_strdel(&env[i]);
			env[i] = env[i + 1];
			while (env[++i])
				env[i] = env[i + 1];
		}
		node = node->next;
	}
}
