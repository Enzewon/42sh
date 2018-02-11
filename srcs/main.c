/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/15 14:26:22 by skavunen          #+#    #+#             */
/*   Updated: 2017/08/22 15:21:23 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	make_intro(void)
{
	int		fd;
	char	*line;

	fd = open(".intro", O_RDONLY);
	if (fd >= 0)
	{
		while (get_next_line(fd, &line))
		{
			ft_fprintf(2, "%s\n", line);
			ft_strdel(&line);
		}
	}
	else
	{
		ft_fprintf(2, "$$$$$   $$  $$  $$$$$    $$$$   $");
		ft_fprintf(2, "$  $$  $$$$$   $$  $$  $$  $$\n");
		ft_fprintf(2, "$$  $$  $$  $$  $$  $$  $$  $$  $$");
		ft_fprintf(2, "  $$  $$      $$$ $$  $$ $$\n");
		ft_fprintf(2, "$$  $$  $$  $$  $$  $$  $$  $$  $$  $$");
		ft_fprintf(2, "  $$$$    $$ $$$  $$$$\n");
		ft_fprintf(2, "$$  $$   $$$$   $$  $$  $$  $$   ");
		ft_fprintf(2, "$$$$   $$      $$  $$  $$ $$\n");
		ft_fprintf(2, "$$$$$     $$    $$$$$    $$$$     $$");
		ft_fprintf(2, "    $$$$$   $$  $$  $$  $$\n\n");
	}
}

void	handler(int sig)
{
	if (sig == SIGINT && g_proc > 0)
	{
		kill(g_proc, SIGINT);
		write(1, "\n", 1);
	}
	else if (sig == SIGSTOP && g_proc == 0)
		kill(g_proc, SIGSTOP);
	else if (sig == SIGTSTP)
		kill(g_proc, SIGTSTP);
	else if (sig == SIGCONT)
		kill(g_proc, SIGCONT);
	else if (sig == SIGWINCH)
		update_winsize(0);
	else if (sig == SIGABRT || sig == SIGHUP || sig == SIGKILL ||
			sig == SIGPIPE || sig == SIGQUIT || sig == SIGTERM ||
			sig == SIGBUS)
	{
		if (g_shell)
			reset_termios(g_shell);
		ft_printf("\nShell has been interrupted!\n");
		ft_printf("Wooh... Why did you use {%d} code?\n", sig);
		exit(EXIT_FAILURE);
	}
}

t_sh	*ft_shell_init(void)
{
	t_sh	*sh;

	if (!(sh = (t_sh*)ft_memalloc(sizeof(t_sh))))
		return (NULL);
	sh->prompt = "21sh";
	sh->history = (char**)ft_memalloc(sizeof(char*) * (HISTORY_COUNT + 1));
	sh->terminal = STDIN_FILENO;
	sh->is_interactive = isatty(sh->terminal);
	if (sh->is_interactive)
	{
		while (tcgetpgrp(sh->terminal) != (sh->pgid = getpgrp()))
			kill(-sh->pgid, SIGTTIN);
		sh->pgid = getpid();
		if (setpgid(sh->pgid, sh->pgid) < 0)
		{
			ft_fprintf(2, "Couldn't put the shell in its own process group\n");
			exit(EXIT_FAILURE);
		}
		tcsetpgrp(sh->terminal, sh->pgid);
		tcgetattr(STDIN_FILENO, &sh->term);
	}
	return (sh);
}

int		main(int ac, char **av, char **env)
{
	char	**nenv;
	int		i;

	g_hist = NULL;
	(void)ac;
	(void)av;
	make_hash_table(env);
	i = 0;
	while (++i < 32)
		signal(i, handler);
	nenv = ft_init_env(env);
	g_shell = ft_shell_init();
	g_shell->env = nenv;
	ft_21sh(&nenv);
	exit(EXIT_SUCCESS);
}
