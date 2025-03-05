/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 22:11:14 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/14 20:23:23 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	welcome_message(void)
{
	ft_printf("%s", BOLD_YELLOW);
	ft_printf("WELCOLME TO MINISHELL\n\n");
	ft_printf("%s", RESET);
}

void	restore_terminal(t_shell_data *shell)
{
	tcsetattr(STDIN_FILENO, 0, &shell->old);
}

void	handle_sigtstp(int sig)
{
	(void)sig;
}
