/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_termios.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 16:51:37 by dvdovenk          #+#    #+#             */
/*   Updated: 2018/01/05 16:51:37 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	controlled_termios(t_sh *shell)
{
	struct termios	term;
	int				j;

	tcgetattr(STDIN_FILENO, &term);
	if ((j = find_env_var("TERM", shell->env)) != -1)
	{
		term.c_lflag &= ~ICANON & ~ECHO & ~ISIG;
		term.c_oflag &= (OPOST);
		term.c_cc[VMIN] = 1;
		term.c_cc[VTIME] = 0;
		tcsetattr(STDIN_FILENO, TCSADRAIN, &term);
		tgetent(NULL, ft_strchr(shell->env[j], '=') + 1);
	}
}

void	reset_termios(t_sh *shell)
{
	tcsetattr(STDIN_FILENO, TCSADRAIN, &shell->term);
}
