/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_close_and_open.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:08:41 by dagudelo          #+#    #+#             */
/*   Updated: 2024/07/01 12:08:56 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	close_all_pipefd(t_shell_data *shell)
{
	t_pipefd	*current;

	current = shell->pipefd1;
	while (current)
	{
		if (current->values[0] != -1)
			close(current->values[0]);
		if (current->values[1] != -1)
			close(current->values[1]);
		current = current->next;
	}
}

void	close_all_fds(t_shell_data *shell)
{
	t_fds	*current;

	current = shell->fds;
	while (current)
	{
		if (*current->input != -1 && *current->input != STDIN_FILENO)
			close(*current->input);
		if (*current->output != -1 && *current->output != STDOUT_FILENO)
			close(*current->output);
		current = current->next;
	}
	close(shell->fd);
	if (shell->fd_null[0] != -1)
		close(shell->fd_null[0]);
	if (shell->fd_null[1] != -1)
		close(shell->fd_null[1]);
}

void	open_all_pipes(t_shell_data *shell)
{
	t_pipefd	*head;
	int			i;

	if (shell->total_pipes == 0)
		return ;
	shell->pipefd1 = push_pipefd(shell->pipefd1, shell);
	head = shell->pipefd1;
	i = 0;
	while (i < shell->total_pipes)
	{
		shell->pipefd1 = push_pipefd(shell->pipefd1, shell);
		shell->pipefd1 = shell->pipefd1->next;
		i++;
	}
	shell->pipefd1 = head;
}

void	open_all_fds(t_shell_data *shell)
{
	t_fds	*head;
	int		i;

	if (shell->total_pipes == 0)
		return ;
	shell->fds = push_fds(shell->fds, shell);
	head = shell->fds;
	i = 0;
	while (i < shell->total_pipes)
	{
		shell->fds = push_fds(shell->fds, shell);
		shell->fds = shell->fds->next;
		i++;
	}
	shell->fds = head;
}

int	*clear_pipe(int *pipefd, t_shell_data *shell)
{
	int	*new_pipefd;

	close(pipefd[0]);
	close(pipefd[1]);
	free_variable((void **)&pipefd);
	new_pipefd = malloc(sizeof(int) * 2);
	if (new_pipefd == NULL)
	{
		exit_1_malloc(&shell);
	}
	if (pipe(new_pipefd) == -1)
	{
		perror("pipe");
		free_variable((void **)&new_pipefd);
		free_malloc_exit_system(&shell);
		exit(EXIT_FAILURE);
	}
	return (new_pipefd);
}
