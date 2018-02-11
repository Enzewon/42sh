/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 14:09:47 by skavunen          #+#    #+#             */
/*   Updated: 2017/08/22 19:54:11 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char				**ft_init_env(char **env)
{
	char			**new;
	int				a;

	a = 0;
	while (env[a])
		a++;
	new = (char**)malloc(sizeof(char*) * (a + 1));
	a = -1;
	while (env[++a])
		new[a] = ft_strdup(env[a]);
	new[a] = NULL;
	return (new);
}

t_fds				*ft_init_fds(void)
{
	t_fds			*new;

	new = (t_fds*)malloc(sizeof(t_fds));
	new->in = 0;
	new->close = -1;
	new->open = -1;
	new->file = -1;
	new->hdoc = -1;
	new->hered = NULL;
	new->mem1 = dup(1);
	new->mem2 = dup(0);
	new->mem3 = dup(2);
	return (new);
}
