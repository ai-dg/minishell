/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:23:43 by calbor-p          #+#    #+#             */
/*   Updated: 2024/07/01 12:07:54 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static void	increment_loop(t_write_in_here_doc **write, int pipefd[2],
		t_cmd *cmd, t_shell_data *shell)
{
	(void)pipefd;
	free_variable((void **)&(*write)->line);
	(*write)->line = readline("> ");
	if ((*write)->line == NULL && g_receipt == SIGINT)
	{
		free_variable((void **)&(*write)->line);
		free_variable((void **)&(*write)->line_to_history);
		free_variable((void **)&cmd->cmd);
		free_array(&cmd->args);
		if (g_receipt != 0)
			shell->exit_signals2 = get_status_from_sig(shell);
		g_receipt = 0;
		reopen_stdin_if_needed();
		(*write)->in_signals = true;
	}
	(*write)->i++;
}

static bool	check_if_go_out(t_write_in_here_doc **write, t_cmd *cmd)
{
	if (condition_to_go_out_here(write))
	{
		free_variable((void **)&(*write)->line);
		return (true);
	}
	if ((*write)->line == NULL)
	{
		free_variable((void **)&(*write)->line);
		free_variable((void **)&cmd->cmd);
		free_array(&cmd->args);
		(*write)->error = true;
		return (true);
	}
	return (false);
}

static void	readline_loop(t_write_in_here_doc **write, int pipefd[2],
		t_cmd *cmd, t_shell_data *shell)
{
	bool	result;

	result = false;
	while (1)
	{
		save_position(write, shell);
		if ((*write)->line != NULL)
			fill_line_history(write);
		result = check_if_go_out(write, cmd);
		if (result == true)
			break ;
		increment_loop(write, pipefd, cmd, shell);
	}
	if ((*write)->error == false)
		print_to_pipe(pipefd, write, shell);
	free_variable((void **)&cmd->delimiter);
	free_variable((void **)&(*write)->line_to_history);
}

static void	check_if_ctrlc_pressed(int pipefd[2], t_write_in_here_doc *write,
		t_cmd *cmd, t_shell_data *shell)
{
	if (write->line == NULL && g_receipt == SIGINT)
	{
		free_variable((void **)&write->line);
		free_variable((void **)&cmd->cmd);
		free_array(&cmd->args);
		if (g_receipt != 0)
			shell->exit_signals2 = get_status_from_sig(shell);
		g_receipt = 0;
		reopen_stdin_if_needed();
		write->in_signals = true;
	}
	else
		readline_loop(&write, pipefd, cmd, shell);
}

void	write_in_here_doc(int pipefd[2], t_cmd *cmd, char *delimiter,
		t_shell_data *shell)
{
	t_write_in_here_doc	write;
	int					saved_stdout;

	saved_stdout = 0;
	init_write_in_here_doc(&write, delimiter, shell);
	process_here_doc_writing(&saved_stdout, &write, shell);
	check_if_ctrlc_pressed(pipefd, &write, cmd, shell);
	init_signals(shell);
	shell->count_in_doc++;
	if (write.error == true && write.in_signals == false)
		error_here_doc(&write, cmd);
	if (shell->in_script == true && shell->in_parentheses == true)
	{
		if (dup2(saved_stdout, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(saved_stdout);
	}
	free_variable((void **)&write.tester);
	free_variable((void **)&write.line);
	free_variable((void **)&write.line_to_print);
}
