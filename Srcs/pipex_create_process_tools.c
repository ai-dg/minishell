/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_create_process_tools.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:31:31 by dagudelo          #+#    #+#             */
/*   Updated: 2024/07/01 13:07:29 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static int	safe_open_fd(char *path, int mode)
{
	int	fd;

	fd = open(path, mode);
	if (fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	config_children_process(t_shell_data *shell)
{
	shell->input = STDIN_FILENO;
	shell->output = STDOUT_FILENO;
	open_all_pipes(shell);
	open_all_fds(shell);
	shell->fd_null[1] = safe_open_fd("/dev/null", O_WRONLY);
	shell->fd_null[0] = safe_open_fd("/dev/null", O_RDONLY);
}

void	start_children_process(t_fds *current_fds, t_cmd *current_pipe,
		t_shell_data *shell)
{
	shell->pid_list[shell->i] = create_child_process(current_fds, current_pipe,
			shell);
	if (shell->pid_list[shell->i] == -1)
	{
		perror("fork");
		close_pipes_and_files(shell);
		exit(EXIT_FAILURE);
	}
	shell->i++;
}

void	handle_exit_status_children(t_cmd *current_pipe, t_shell_data *shell)
{
	if (current_pipe->next == NULL)
	{
		if (current_pipe->output_result == -1)
			shell->exit_status = 1;
		else if (current_pipe->input_result == -1)
			shell->exit_status = 1;
		else if (current_pipe->exit_status > 0)
			shell->exit_status = current_pipe->exit_status;
		else
			shell->exit_status = 0;
	}
}
