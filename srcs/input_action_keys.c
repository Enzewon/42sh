/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_action_keys.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 16:53:00 by dvdovenk          #+#    #+#             */
/*   Updated: 2018/01/05 16:53:01 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static t_spec_keys	*get_action_regular(void)
{
	static t_spec_keys	actions[11] = {
	{backspace, {127, 0, 0, 0, 0}},
	{insert_enter, {10, 0, 0, 0, 0}},
	{reset_line, {3, 0, 0, 0, 0}},
	{end_reading, {4, 0, 0, 0, 0}},
	{termcap_home, {1, 0, 0, 0, 0}},
	{termcap_end, {5, 0, 0, 0, 0}},
	{cut_line_left, {21, 0, 0, 0, 0}},
	{paste_str, {16, 0, 0, 0, 0}},
	{cut_line_right, {11, 0, 0, 0, 0}},
	{tab_complete, {9, 0, 0, 0, 0}},
	{history_search, {18, 0, 0, 0, 0}},
	};

	return (actions);
}

static t_spec_keys	*get_action_extended(void)
{
	static t_spec_keys	actions[11] = {
	{history_up, {91, 65, 0, 0, 0}},
	{history_down, {91, 66, 0, 0, 0}},
	{cursor_right_key, {91, 67, 0, 0, 0}},
	{cursor_left_key, {91, 68, 0, 0, 0}},
	{delete_key, {91, 51, 126, 0, 0}},
	{cursor_right_word, {91, 49, 59, 50, 67}},
	{cursor_left_word, {91, 49, 59, 50, 68}},
	{termcap_home, {91, 72, 0, 0, 0}},
	{termcap_end, {91, 70, 0, 0, 0}},
	{cursor_up_key, {91, 49, 59, 50, 65}},
	{cursor_down_key, {91, 49, 59, 50, 66}},
	};

	return (actions);
}

static int			cmp_values(int *value, char *buf, int len)
{
	int	i;

	i = -1;
	while (++i < len)
	{
		if (buf[i] != value[i])
			return (1);
	}
	return (0);
}

int					actions_regular(t_read *read)
{
	int			i;
	t_spec_keys	*actions;

	i = -1;
	actions = get_action_regular();
	while (++i < 11)
	{
		if (cmp_values((int *)actions[i].value, read->key, 1) == 0)
			return (actions[i].function(read));
	}
	if (ft_isprint(read->key[0]))
		insert_char(read, read->key[0]);
	return (1);
}

int					actions_extended(t_read *r)
{
	int			i;
	t_spec_keys	*actions;

	i = -1;
	ft_bzero(r->key_extended, 5);
	read(0, &r->key_extended, 5);
	actions = get_action_extended();
	while (++i < 11)
		if (cmp_values((int *)actions[i].value, r->key_extended, 5) == 0)
			actions[i].function(r);
	return (1);
}
