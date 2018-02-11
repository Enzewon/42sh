/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_making_read.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 16:50:13 by dvdovenk          #+#    #+#             */
/*   Updated: 2018/01/05 16:50:20 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static char	**tmp_history(char **history, t_read *read)
{
	int		i;
	char	**new_his;

	new_his = NULL;
	if (history)
	{
		i = 0;
		new_his = (char**)ft_memalloc(sizeof(char*) * (HISTORY_COUNT + 1));
		while (++i < HISTORY_COUNT && history[i - 1])
			new_his[i] = ft_strcpy(ft_strnew(1024), history[i - 1]);
		*new_his = read->cmd;
	}
	return (new_his);
}

static char	*remake_pwd(char *pwd, char **env)
{
	int		k;
	char	*trash;
	char	*tmp;

	if ((k = find_env_var("HOME", env)) != -1)
	{
		tmp = ft_strchr(env[k], '=') + 1;
		k = ft_strlen(tmp);
		if (k > 0 && ft_strncmp(tmp, pwd, k) == 0)
		{
			trash = pwd;
			pwd = ft_strjoin("~", trash + k);
			ft_strdel(&trash);
		}
	}
	return (pwd);
}

static char	*make_prompt(char **env, char *prompt)
{
	int		k;
	char	*usr;
	char	*p;

	usr = NULL;
	if (env && (p = getcwd(NULL, 4096)))
	{
		p = remake_pwd(p, env);
		if ((k = find_env_var("USER", env)) != -1)
		{
			usr = ft_strchr(env[k], '=') + 1;
			usr = ft_strjoin(usr, "@");
			prompt = ft_strjoin(usr, p);
			ft_strdel(&usr);
		}
		else
			prompt = ft_strjoin("@", p);
		ft_strdel(&p);
		return (prompt);
	}
	return (ft_strdup(prompt));
}

t_read		*read_init(char **his, char *prompt, char **env, t_hash *hash)
{
	t_read	*read;

	read = NULL;
	if (!(read = (t_read*)ft_memalloc(sizeof(t_read))))
		exit(EXIT_FAILURE);
	update_winsize(0);
	read->hash = hash;
	read->work = 42;
	read->heredoc = 0;
	if (ft_strcmp(prompt, "21sh") == 0)
		read->prompt = make_prompt(env, prompt);
	else
		read->prompt = ft_strdup(prompt);
	read->cursor_start = ft_strlen(read->prompt) + 5;
	read->cmd = ft_strnew(1024);
	read->his = tmp_history(his, read);
	read->env = env;
	return (read);
}

void		delete_read(t_read *read)
{
	if (read->prompt)
		ft_strdel(&read->prompt);
	if (read->his)
		ft_strdel_array(read->his);
}
