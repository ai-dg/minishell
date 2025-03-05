/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 20:52:54 by ls                #+#    #+#             */
/*   Updated: 2024/06/14 15:53:06 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	ft_alt_putchar(int c)
{
	return (write(1, &c, 1));
}

int	clear_m(t_shell_data *shell, char **inst)
{
	char		*term;
	const char	*clear = "\033[2J\033[H";

	(void)inst;
	term = get_value_from_key(shell->env, "TERM");
	if (!term)
	{
		printf("TERM environment variable not set.\n");
		return (shell->exit_status = 1);
	}
	if (write(STDOUT_FILENO, clear, 7) == -1)
	{
		perror("Error clearing the screen");
		return (shell->exit_status = 1);
	}
	return (shell->exit_status = 0);
}
