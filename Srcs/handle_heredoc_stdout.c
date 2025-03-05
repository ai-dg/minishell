/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc_stdout.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:23:43 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/24 12:51:01 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	stdout_checks(int *saved_stdout, t_shell_data *shell)
{
	if (*saved_stdout == -1)
	{
		perror("dup");
		exit(EXIT_FAILURE);
	}
	if (dup2(shell->output_to_change, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
}

void	process_here_doc_writing(int *saved_stdout,
	t_write_in_here_doc *write, t_shell_data *shell)
{
	if (shell->in_script == true && shell->in_parentheses == false)
	{
		free_variable((void **)&(*write).line);
		write->line = NULL;
	}
	else if (shell->in_script == true && shell->in_parentheses == true)
	{
		*saved_stdout = dup(STDOUT_FILENO);
		stdout_checks(saved_stdout, shell);
		rl_outstream = stdout;
		write->line = readline("> ");
	}
	else
	{
		init_signals_alt(shell);
		write->line = readline("> ");
	}
}
