/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 18:25:14 by dvdovenk          #+#    #+#             */
/*   Updated: 2018/01/05 18:25:15 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int		ft_arrlen(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	update_winsize(int sig)
{
	struct winsize	w;

	(void)sig;
	ioctl(0, TIOCGWINSZ, &w);
	g_width = w.ws_col;
}

int		ft_is_executable(char *cmd, int flag)
{
	if (flag == 0 && access(cmd, F_OK) == 0)
		return (1);
	if (flag == 1 && access(cmd, X_OK) == 0)
		return (1);
	return (0);
}

int		is_builtin_command(char *str)
{
	if (ft_strequ(str, "env") || ft_strequ(str, "echo") ||
		ft_strequ(str, "cd") || ft_strequ(str, "setenv") ||
		ft_strequ(str, "unsetenv") || ft_strequ(str, "exit") ||
		ft_strequ(str, "history"))
		return (1);
	return (0);
}

void	shell_error(char *cmd, int error_code)
{
	if (error_code == BAD_ACCESS)
		ft_fprintf(2, "42sh: Permission Denied: %s\n", cmd);
	else if (error_code == NO_SUCH)
		ft_fprintf(2, "42sh: No Such File or Directory: %s\n", cmd);
	else if (error_code == IS_DIR)
		ft_fprintf(2, "42sh: Is Directory: %s\n", cmd);
	else if (error_code == NO_CMD)
		ft_fprintf(2, "42sh: Command Not Found: %s\n", cmd);
}
