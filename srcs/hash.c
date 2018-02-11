/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 18:18:36 by dvdovenk          #+#    #+#             */
/*   Updated: 2018/01/05 18:18:37 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

unsigned int	hash_function(const char *data, int size)
{
	unsigned int	hash;

	hash = 0;
	while (*data)
	{
		hash = *data + (hash << 5) - hash;
		data++;
	}
	return (hash % size);
}

t_item			*lookup_string(t_hash *hash, char *str)
{
	t_item			*lst;
	unsigned int	val;

	val = hash_function(str, hash->size);
	lst = hash->table[val];
	while (lst)
	{
		if (ft_strcmp(str, lst->name) == 0)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

int				add_string(t_hash *hash, char *name, char *path)
{
	t_item			*new_list;
	char			*tmp;
	unsigned int	val;

	val = hash_function(name, hash->size);
	new_list = lookup_string(hash, name);
	if (new_list != NULL)
		return (2);
	if (!(new_list = (t_item*)ft_memalloc(sizeof(t_item))))
		return (1);
	tmp = ft_strjoin(path, "/");
	new_list->name = ft_strdup(name);
	new_list->value = ft_strjoin(tmp, name);
	new_list->next = hash->table[val];
	ft_strdel(&tmp);
	hash->table[val] = new_list;
	return (0);
}

void			free_table(t_hash *hash)
{
	int		i;
	t_item	*lst;
	t_item	*tmp;

	if (hash == NULL)
		return ;
	i = -1;
	while (++i < hash->size)
	{
		lst = hash->table[i];
		while (lst)
		{
			tmp = lst;
			lst = lst->next;
			ft_strdel(&tmp->name);
			ft_strdel(&tmp->value);
			free(tmp);
		}
	}
	free(hash->table);
	free(hash);
}

t_hash			*create_hash_table(int size)
{
	t_hash	*new_hash;
	int		i;

	if (!(new_hash = (t_hash*)ft_memalloc(sizeof(t_hash))))
		exit(EXIT_FAILURE);
	if (!(new_hash->table = (t_item**)ft_memalloc(sizeof(t_item*) * size)))
		exit(EXIT_FAILURE);
	i = -1;
	while (++i < size)
		new_hash->table[i] = NULL;
	new_hash->size = size;
	return (new_hash);
}
