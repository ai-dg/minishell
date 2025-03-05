/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_and_close.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:48:25 by dagudelo          #+#    #+#             */
/*   Updated: 2024/06/13 20:55:40 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	close_pipes_and_files(t_shell_data *shell)
{
	if (shell->pipefd[0] != -1)
		close(shell->pipefd[0]);
	if (shell->pipefd[1] != -1)
		close(shell->pipefd[1]);
	if (*shell->fds->input != -1)
		close(*shell->fds->input);
	if (*shell->fds->output != -1)
		close(*shell->fds->output);
}
