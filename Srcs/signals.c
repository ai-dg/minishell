/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:38:10 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/26 07:53:56 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

volatile sig_atomic_t	g_receipt = 0;

void	handle_sigint_parent(int sig)
{
	g_receipt = sig;
	set_cursor_down(1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigquit_parent(int sig)
{
	g_receipt = sig;
}

void	handle_signals_parent(int sig)
{
	if (sig == SIGINT)
		handle_sigint_parent(sig);
	else if (sig == SIGQUIT)
		handle_sigquit_parent(sig);
}

void	handle_sigs_in_child(int sig)
{
	static const char	quit_msg[] = "Quit child (core dumped)\n";

	if (sig == SIGQUIT)
	{
		g_receipt = sig;
		write(STDERR_FILENO, quit_msg, sizeof(quit_msg) - 1);
	}
	else
	{
		g_receipt = sig;
		set_cursor_down(1);
	}
}

int	init_signals(t_shell_data *shell)
{
	struct sigaction	action;
	struct sigaction	ignore_action;

	(void)shell;
	ft_memset(&action, 0, sizeof(action));
	action.sa_handler = handle_signals_parent;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &action, NULL) == -1)
		perror("Failed to set SIGINT handler");
	ft_memset(&ignore_action, 0, sizeof(ignore_action));
	ignore_action.sa_handler = SIG_IGN;
	sigemptyset(&ignore_action.sa_mask);
	ignore_action.sa_flags = 0;
	if (sigaction(SIGQUIT, &ignore_action, NULL) == -1)
		perror("Failed to ignore SIGQUIT");
	if (sigaction(SIGTSTP, &ignore_action, NULL) == -1)
		perror("Failed to ignore SIGTSTP");
	return (0);
}
