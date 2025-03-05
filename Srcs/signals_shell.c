/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 07:32:33 by ls                #+#    #+#             */
/*   Updated: 2024/06/26 07:44:19 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	handle_sigint_parent_new_shell(int sig)
{
	(void)sig;
	g_receipt = sig;
	set_cursor_down(1);
	rl_replace_line("", 0);
	rl_redisplay();
	close(STDIN_FILENO);
}

void	handle_sigquit_parent_new_shell(int sig)
{
	g_receipt = sig;
}

void	handle_signals_parent_new_shell(int sig)
{
	if (sig == SIGINT)
		handle_sigint_parent_new_shell(sig);
	else if (sig == SIGQUIT)
		handle_sigquit_parent_new_shell(sig);
}

int	init_signals_new_shell(void)
{
	struct sigaction	ignore_action_alt;

	ignore_action_alt.sa_flags = SA_RESTART;
	ft_memset(&ignore_action_alt, 0, sizeof(ignore_action_alt));
	ignore_action_alt.sa_handler = SIG_IGN;
	sigemptyset(&ignore_action_alt.sa_mask);
	if (sigaction(SIGINT, &ignore_action_alt, NULL) == -1)
		perror("Failed to set SIGINT handler");
	return (0);
}
