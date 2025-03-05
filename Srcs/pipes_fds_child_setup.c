/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_fds_child_setup.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:09:51 by dagudelo          #+#    #+#             */
/*   Updated: 2024/06/26 17:01:21 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static void	setup_child_process(t_fds *fds, t_cmd *pipe, t_shell_data *shell)
{
	if (*fds->input != STDIN_FILENO)
	{
		dup2(*fds->input, STDIN_FILENO);
		if (*fds->input != STDOUT_FILENO)
			close(*fds->input);
	}
	if (*fds->output != STDOUT_FILENO)
	{
		dup2(*fds->output, STDOUT_FILENO);
		if (*fds->output != STDOUT_FILENO)
			close(*fds->output);
	}
	close_all_fds(shell);
	close_all_pipefd(shell);
	execute_cmd(pipe, shell);
	close_all_fds(shell);
	close_all_pipefd(shell);
	free_malloc_exit_system(&shell);
	exit(0);
}

void	handle_child_signals(t_shell_data *shell)
{
	struct sigaction	sa_child;

	sa_child.sa_handler = handle_sigs_in_child;
	sigemptyset(&sa_child.sa_mask);
	sa_child.sa_flags = 0;
	if (sigaction(SIGINT, &sa_child, NULL) < 0)
	{
		perror("sigaction");
		free_malloc_exit_system(&shell);
		exit(EXIT_FAILURE);
	}
	if (sigaction(SIGQUIT, &sa_child, NULL) < 0)
	{
		perror("sigaction");
		free_malloc_exit_system(&shell);
		exit(EXIT_FAILURE);
	}
}

pid_t	create_child_process(t_fds *fds, t_cmd *pipe, t_shell_data *shell)
{
	pid_t	pid;

	pid = fork();
	if (shell->pid == 0 && ft_strncmp(pipe->cmd, "./minishell",
			ft_strlen("./minishell")))
		handle_child_signals(shell);
	else if (ft_strncmp(pipe->cmd, "./minishell", ft_strlen("./minishell")) == 0
		&& pid != 0)
		init_signals_new_shell();
	pipe->pid = pid;
	if (pid < 0)
	{
		perror("fork");
		free_malloc_exit_system(&shell);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		shell->in_child_process = true;
		setup_child_process(fds, pipe, shell);
		free_malloc_exit_system(&shell);
		exit(0);
	}
	return (pid);
}
