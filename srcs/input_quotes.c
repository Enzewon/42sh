/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 16:57:42 by dvdovenk          #+#    #+#             */
/*   Updated: 2018/01/05 16:57:43 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static void	ft_quote_job(t_read *read, t_quote *quote)
{
	if (read->cmd[read->remember_insert] == '\\')
		quote->es ^= 1;
	else if (read->cmd[read->remember_insert] == '\"' &&
			quote->sq == 0 && quote->bq == 0)
		quote->dq ^= !quote->es;
	else if (read->cmd[read->remember_insert] == '\'' &&
			quote->dq == 0 && quote->bq == 0)
		quote->sq ^= !quote->es;
	else if (read->cmd[read->remember_insert] == '`' &&
			quote->sq == 0)
		quote->bq ^= !quote->es;
	else
		quote->es = 0;
	read->remember_insert++;
}

static int	check_quotes(t_read *read, t_quote *quote)
{
	while (read->cmd[read->remember_insert])
		ft_quote_job(read, quote);
	return (!quote->bq && !quote->sq && !quote->dq && !quote->es);
}

static int	close_quotes(t_quote *q, t_read *r, char *prompt, char *tmp)
{
	t_read	*new_read;

	if (q->sq == 1)
		prompt = "quote";
	else if (q->dq == 1)
		prompt = "dquote";
	else if (r->cmd[r->size - 1] == '\\')
		prompt = " ";
	else if (prompt == NULL)
		return (1);
	r->cmd[r->size - 1] == '\\' ? (tmp = ft_strsub(r->cmd, 0, r->size - 1)) :
				(tmp = ft_strjoin(r->cmd, "\n"));
	termcap_do("do");
	termcap_do("cr");
	new_read = read_init(NULL, prompt, r->env, NULL);
	new_read->heredoc = 1;
	upwrite_quote(new_read);
	if (new_read->work != -2)
	{
		ft_strdel(&r->cmd);
		r->cmd = ft_strjoin(tmp, new_read->cmd);
		r->his[r->his_pos] = r->cmd;
	}
	delete_it(new_read, tmp);
	return ((new_read->work != -2 ? 0 : 1));
}

int			check_quote(t_read *read)
{
	t_quote	quote;

	quote.bq = 0;
	quote.sq = 0;
	quote.dq = 0;
	quote.es = 0;
	read->remember_insert = 0;
	while (!check_quotes(read, &quote))
		if (close_quotes(&quote, read, (quote.bq == 1) ? "bquote" : NULL, NULL))
			break ;
	return (1);
}

void		upwrite_quote(t_read *r)
{
	r->pos = 0;
	r->size = 0;
	ft_fprintf(2, "{#bold}{#yellow}%s {#green}/~> {#eoc}", r->prompt);
	while (r->work > 0)
	{
		r->key[0] = ft_getchar();
		if (processing_key(r) == 0)
			break ;
	}
}
