/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 16:19:58 by skavunen          #+#    #+#             */
/*   Updated: 2018/01/26 16:19:58 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int		ft_is_dir(char *path)
{
	struct stat statbuf;

	if (lstat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

void	skip_quotes(char *s, int *i)
{
	char	ch;

	ch = s[(*i)];
	(*i)++;
	while (s[(*i)] && s[(*i)] != ch)
		(*i)++;
}

char	*clear_quotes(char *argv)
{
	int	p;
	int	j;
	int	size;

	j = -1;
	size = ft_strlen(argv);
	while (++j < size)
	{
		if (SPEC(argv[j]))
		{
			p = j;
			skip_quotes(argv, &j);
			ft_memmove(argv + j, argv + j + 1,
				ft_strlen(argv + j + 1) + 1);
			ft_memmove(argv + p, argv + p + 1,
				ft_strlen(argv + p) + 1);
			j -= 2;
		}
	}
	return (argv);
}

int		mini_echo(char **argv, int i, int j, int z)
{
	int flag;

	flag = 0;
	if (argv[1] && ft_strcmp(argv[1], "-n") == 0 && (i = 1))
		flag = 1;
	while (argv[++i])
	{
		j = 0;
		while (argv[i][j])
		{
			z = 0;
			if (argv[i][j] == '\\' && find_spec(argv[i], j) == 1)
				j += 2;
			if (argv[i][j])
				write(1, &argv[i][j], 1);
			if (argv[i][j])
				j++;
		}
		if (argv[i + 1])
			ft_putchar(' ');
	}
	if (flag == 0)
		ft_putchar('\n');
	return (1);
}

void	execute_command(char *cmd, char **argv, char **env)
{
	int	exe;
	int	i;

	i = 0;
	while (argv[++i])
		argv[i] = clear_quotes(argv[i]);
	cmd = clear_quotes(cmd);
	if (!builtin_command(cmd, argv, env))
	{
		exe = execve(cmd, argv, env);
		if (exe == -1 && !ft_is_executable(cmd, 1))
			shell_error(cmd, BAD_ACCESS);
		if (exe == -1 && ft_is_dir(cmd))
			shell_error(cmd, IS_DIR);
	}
}
