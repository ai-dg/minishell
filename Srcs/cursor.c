/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 07:17:01 by ls                #+#    #+#             */
/*   Updated: 2024/06/14 15:52:54 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	init_termcaps(void)
{
	int	termcap;

	termcap = tgetent(NULL, getenv("TERM"));
	return (termcap);
}

int	set_cursor_above(int times)
{
	char	*up;

	while (times--)
	{
		up = tgetstr("up", NULL);
		tputs(up, 1, ft_alt_putchar);
	}
	return (0);
}

int	set_cursor_down(int times)
{
	char	*down;

	while (times--)
	{
		down = tgetstr("do", NULL);
		tputs(down, 1, ft_alt_putchar);
	}
	return (0);
}

int	set_enter(int times)
{
	char	*down;

	while (times--)
	{
		down = tgetstr(" @8", NULL);
		tputs(down, 1, ft_alt_putchar);
	}
	return (0);
}
