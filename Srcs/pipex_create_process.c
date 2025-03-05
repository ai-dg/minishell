/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_create_process.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:31:31 by dagudelo          #+#    #+#             */
/*   Updated: 2024/07/01 11:37:43 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static void	handle_end_children(t_shell_data *shell)
{
	close_all_pipefd(shell);
	close_all_fds(shell);
	handle_exit(&shell->exit_status1, &shell->exit_status2, shell);
	init_signals(shell);
}

static void	handle_main_child_process(t_cmd *current_pipe,
		t_pipefd *current_pipefd1, t_fds *current_fds, t_shell_data *shell)
{
	if (current_pipe->next)
	{
		if (pipe(current_pipefd1->next->values) == -1)
			exit_errno("pipe", &shell);
	}
	fill_all_fds(current_pipe, current_pipefd1, current_fds, shell);
	write_input_to_pipes(current_pipe, current_pipefd1, shell);
	remove_line_break(current_pipe, current_pipefd1, shell);
	if (current_pipe->exit_status == 0)
		start_children_process(current_fds, current_pipe, shell);
	handle_exit_status_children(current_pipe, shell);
	if (current_pipefd1->prev)
	{
		close(current_pipefd1->prev->values[0]);
		close(current_pipefd1->prev->values[1]);
	}
	close(shell->fd);
}

void	create_pid_process(t_cmd *pipes, t_shell_data *shell)
{
	t_pipefd	*current_pipefd1;
	t_fds		*current_fds;
	t_cmd		*current_pipe;

	config_children_process(shell);
	current_pipefd1 = shell->pipefd1;
	current_fds = shell->fds;
	current_pipe = pipes;
	if (pipe(current_pipefd1->values) == -1)
		exit_errno("pipe", &shell);
	while (current_pipe != NULL)
	{
		handle_main_child_process(current_pipe, current_pipefd1, current_fds,
			shell);
		current_pipe = current_pipe->next;
		current_pipefd1 = current_pipefd1->next;
		current_fds = current_fds->next;
	}
	handle_end_children(shell);
}
