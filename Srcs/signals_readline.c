/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_readline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 07:32:33 by ls                #+#    #+#             */
/*   Updated: 2024/06/22 15:53:17 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	handle_sigint_parent_alt(int sig)
{
	g_receipt = sig;
	set_cursor_down(1);
	rl_replace_line("", 0);
	rl_redisplay();
	close(STDIN_FILENO);
}

void	handle_sigquit_parent_alt(int sig)
{
	g_receipt = sig;
}

void	handle_signals_parent_alt(int sig)
{
	if (sig == SIGINT)
		handle_sigint_parent_alt(sig);
	else if (sig == SIGQUIT)
		handle_sigquit_parent_alt(sig);
}

int	init_signals_alt(t_shell_data *shell)
{
	struct sigaction	action;
	struct sigaction	ignore_action;

	(void)shell;
	ft_memset(&action, 0, sizeof(action));
	action.sa_handler = handle_signals_parent_alt;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
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
