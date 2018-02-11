/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 14:20:50 by skavunen          #+#    #+#             */
/*   Updated: 2017/08/08 14:43:52 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static void	replace_pwds(char **env)
{
	char	*tmp;
	char	*p;
	int		j;
	int		k;

	if ((p = getcwd(NULL, 4096)) != NULL)
	{
		if ((j = find_env_var("PWD", env)) != -1)
		{
			if ((k = find_env_var("OLDPWD", env)) != -1)
			{
				tmp = ft_strjoin("OLDPWD=", ft_strchr(env[j], '=') + 1);
				place_env(tmp, env);
				ft_strdel(&tmp);
			}
			tmp = ft_strjoin("PWD=", p);
			place_env(tmp, env);
			ft_strdel(&tmp);
		}
		ft_strdel(&p);
	}
}

static void	take_cd_error(char *path)
{
	struct stat	info;

	if (lstat(path, &info) == 0)
	{
		if (!(info.st_mode & S_IFDIR))
			ft_fprintf(2, "42sh: Not a Directory: %s\n", path);
		else if (access(path, X_OK) == -1)
			ft_fprintf(2, "42sh: Permission Denied\n");
	}
	else
		ft_fprintf(2, "42sh: No Such File or Directory: %s\n", path);
}

void		ft_mini_cd(t_list *list, char **env)
{
	int	j;

	if (list->next != NULL && list->next->next != NULL)
		ft_fprintf(2, "42sh: String is not in pwd: %s\n", list->next->content);
	else if (list->next == NULL)
	{
		if ((j = find_env_var("HOME", env)) != -1 &&
			!chdir(ft_strchr(env[j], '=') + 1))
			replace_pwds(env);
		else
			ft_fprintf(2, "42sh: No argument to cd\n");
	}
	else if (ft_strequ(list->next->content, "-") &&
		(j = find_env_var("OLDPWD", env)) != -1 &&
		!chdir(ft_strchr(env[j], '=') + 1))
	{
		ft_printf("%s\n", ft_strchr(env[j], '=') + 1);
		replace_pwds(env);
	}
	else if (chdir(list->next->content) != 0)
		take_cd_error(list->next->content);
	else
		replace_pwds(env);
}
