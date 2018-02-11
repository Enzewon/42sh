/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 15:20:37 by skavunen          #+#    #+#             */
/*   Updated: 2017/08/22 19:44:55 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char	*ft_chjoin(char const *str, char ch)
{
	char	*new;
	int		a;

	a = 0;
	if (!str)
		return (NULL);
	new = (char*)malloc(sizeof(char) * ft_strlen(str) + 2);
	while (str[a] != '\0')
	{
		new[a] = str[a];
		a++;
	}
	new[a] = ch;
	new[++a] = '\0';
	return (new);
}

void	ft_args_smpl(char *arg, int *i, char **str)
{
	int	a;

	a = *i;
	while (arg[a] && (arg[a] == ' ' || arg[a] == '\t'))
		a++;
	*i = a;
	while (ARGWL(arg[a]) && arg[a] != '\'' && arg[a] != '"')
		a++;
	*str = ft_strsub(arg, *i, a - *i);
	if (arg[a] == ';' || arg[a] == '|' || QUOTE(arg[a]) || arg[a] == '|' ||
		arg[a] == '>' || arg[a] == '<')
		--a;
	*i = a;
}

void	ft_spec_var(char *str, int *i, char **ar)
{
	char	ch;
	int		count;
	char	*new;

	ch = str[(*i)];
	count = 0;
	while (str[(*i)] == ch)
	{
		count++;
		(*i)++;
	}
	(*i)--;
	new = ft_strnew(count);
	while (--count >= 0)
		new[count] = ch;
	*ar = new;
}

void	ft_env_var(char *arg, int *a, char **ar, char **env)
{
	char	*var;
	int		ind;
	int		find;
	int		cmp;

	ind = *a;
	while (arg[(*a)] && arg[(*a)] != ' ')
		(*a)++;
	var = ft_strsub(arg, ind + 1, (*a) - ind - 1);
	if (arg[ind] == '~' && (find = find_env_var("HOME", env)) != -1)
		*ar = ft_strjoin(env[find] + 5, var);
	else
	{
		cmp = ft_strlen(var);
		if ((find = find_env_var(var, env)) == -1 && (*a)--)
			*ar = NULL;
		else
			*ar = ft_strsub(env[find], cmp + 1, ft_strlen(env[find]) - cmp - 1);
	}
	ft_strdel(&var);
}

t_list	*ft_get_args(char **read, char ***env, t_list *node, int i)
{
	char	*ar;
	char	*str;

	str = *read;
	ar = NULL;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] == '`')
			ft_exe_quote(read, &i, &node, env);
		else if (QUOTE(str[i]))
			ft_is_quote(read, &i, &ar, env);
		else if (str[i] == '$' || str[i] == '~')
			ft_env_var(str, &i, &ar, *env);
		else if (SPEC(str[i]))
			ft_spec_var(str, &i, &ar);
		else
			ft_args_smpl(str, &i, &ar);
		clear_slash(&ar);
		ar ? ft_lstpushback(&node, ar, ft_strlen(ar) + 1) : NULL;
		ar ? ft_strdel(&ar) : NULL;
		i += (str[i] == '\0' ? 0 : 1);
	}
	return (node);
}
