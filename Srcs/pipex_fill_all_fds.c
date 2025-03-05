/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_fill_all_fds.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:46:34 by dagudelo          #+#    #+#             */
/*   Updated: 2024/06/29 13:54:32 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static void	handle_output_children(t_cmd *current_pipe,
		t_pipefd *current_pipefd1, t_fds *current_fds, t_shell_data *shell)
{
	current_pipe->output_result = open_fd_output(current_pipe, shell);
	if (current_pipe->next == NULL && current_pipe->output_result < 0)
		*current_fds->output = STDOUT_FILENO;
	else if (current_pipe->output_result > 0)
		*current_fds->output = current_pipe->output_result;
	else if (current_pipe->next != NULL)
	{
		*current_fds->output = current_pipefd1->next->values[1];
		if (current_pipe->next->path_infiles != NULL)
			*current_fds->output = shell->fd;
	}
	if (current_pipe->output_result == -1)
		*current_fds->output = shell->fd;
}

static void	handle_input_children(t_cmd *current_pipe,
		t_pipefd *current_pipefd1, t_fds *current_fds, t_shell_data *shell)
{
	if (current_pipe && if_double_redir_input_exist(current_pipe) == false)
	{
		current_pipe->input_result = open_fd_input(current_pipe, shell, 0);
		if (current_pipe->input_result > 0)
			*current_fds->input = current_pipefd1->values[0];
		else if (current_pipe->input_result < 0
			&& current_pipe->path_infiles != NULL)
			*current_fds->input = current_pipefd1->values[0];
		else if (current_pipe->prev != NULL)
			*current_fds->input = current_pipefd1->values[0];
		else
			*current_fds->input = STDIN_FILENO;
	}
	else
	{
		fill_all_fds_doc(current_pipe, current_pipefd1, current_fds, shell);
	}
}

static void	handle_exit_status_output_input(t_cmd *current_pipe)
{
	if (current_pipe->input_result == -1 && current_pipe->path_infiles != NULL)
	{
		if (current_pipe->input_result == -1)
			current_pipe->input_result = 1;
		current_pipe->exit_status = current_pipe->input_result;
	}
	if (current_pipe->output_result == -1
		&& current_pipe->path_outfiles != NULL)
	{
		if (current_pipe->output_result == -1)
			current_pipe->output_result = 1;
		current_pipe->exit_status = current_pipe->output_result;
	}
}

void	fill_all_fds(t_cmd *current_pipe, t_pipefd *current_pipefd1,
		t_fds *current_fds, t_shell_data *shell)
{
	shell->fd = open("/dev/null", O_WRONLY);
	handle_output_children(current_pipe, current_pipefd1, current_fds,
		shell);
	handle_input_children(current_pipe, current_pipefd1, current_fds,
		shell);
	handle_exit_status_output_input(current_pipe);
}
