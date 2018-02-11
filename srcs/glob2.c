/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 13:48:21 by skavunen          #+#    #+#             */
/*   Updated: 2018/01/25 13:48:21 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static int		valid_star(char *file, char *s, int *k, int *j)
{
	int			i;
	int			a;
	int			tmp;

	i = *k;
	a = *j;
	while (!(s[a] ^ '*') || !(s[a] ^ '?'))
		a++;
	if (!s[a])
		return (ft_strlen(file) + 1);
	while (file[i])
	{
		if (!(file[i] ^ s[a]) || s[a] == '[' || s[a] == '{')
			if ((tmp = file_valid(file + i, s + a)))
				return (tmp + i);
		i++;
	}
	if (!file[i])
		return (-1);
	a++;
	i++;
	*k = i;
	*j = a;
	return (0);
}

static int		brackets_2(char *file, char *s, int *k, int *j)
{
	int			fl;

	fl = 0;
	while (s[(*j)] ^ ']')
	{
		if (!s[(*j)])
			return (-1);
		if (!(s[(*j)] ^ ','))
			if (!(file[(*k)] ^ s[(*j) + 1]))
				fl |= SUCCESS;
		if (!(s[(*j)] ^ '-'))
			if (file[(*k)] >= s[(*j) - 1] && file[(*k)] <= s[(*j) + 1])
				fl |= SUCCESS;
		(*j)++;
	}
	if ((fl & SUCCESS) ^ SUCCESS)
		return (-1);
	(*k)++;
	(*j)++;
	return (0);
}

static int		valid_brackets(char *file, char *s, int *k, int *j)
{
	if (!s[++(*j)])
		return (-1);
	if (!(file[(*k)] ^ s[(*j)]))
	{
		(*k)++;
		while (s[++(*j)] ^ ']')
			if (!s[(*j)])
				return (-1);
		(*j)++;
		return (0);
	}
	return (brackets_2(file, s, k, j));
}

static int		control_valid(char *file, char *s, int *i, int *a)
{
	int			tmp;

	if (!(s[(*a)] ^ '*'))
	{
		if ((tmp = valid_star(file, s, i, a)) < 0)
			return (-1);
		else if (tmp > 0)
			return (tmp);
	}
	else if (!(s[(*a)] ^ '?'))
	{
		while (s[(*a)] && !(s[(*a)] ^ '?'))
		{
			if (!file[(*i)])
				return (-1);
			(*a)++;
			(*i)++;
		}
	}
	else if (!(s[(*a)] ^ '['))
		if ((tmp = valid_brackets(file, s, i, a)) < 0)
			return (-1);
	return (0);
}

int				file_valid(char *file, char *s)
{
	int			i;
	int			a;
	int			tmp;

	i = 0;
	a = 0;
	while (file[i])
	{
		if (!s[a])
			return (0);
		else if (s[a] == '?' || s[a] == '*' || s[a] == '[')
		{
			if ((tmp = control_valid(file, s, &i, &a)) < 0)
				return (0);
			else if (tmp > 0)
				return (tmp);
		}
		else if (s[a] ^ file[i])
			return (0);
		else
			i += a++ ? 1 : 1;
	}
	return (s[a] && s[a] ^ '*' ? 0 : i + 1);
}
