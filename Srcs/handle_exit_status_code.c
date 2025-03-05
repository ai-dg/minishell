/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit_status_code.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:26:45 by dagudelo          #+#    #+#             */
/*   Updated: 2024/06/21 18:46:01 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static void	handle_exit_status1(int *exit_status1, t_shell_data *shell)
{
	if (WIFEXITED(*exit_status1))
	{
		*exit_status1 = WEXITSTATUS(*exit_status1);
		if (*exit_status1 == 141)
			*exit_status1 = 0;
		if (shell->input == -1 && shell->output != -1)
			*exit_status1 = 0;
	}
	else if (WIFSIGNALED(*exit_status1))
	{
		*exit_status1 = 128 + WTERMSIG(*exit_status1);
		if (*exit_status1 == 141)
			*exit_status1 = 0;
		if (shell->input == -1 && shell->output != -1)
			*exit_status1 = 0;
	}
}

static void	handle_exit_status2(int *exit_status2, t_shell_data *shell)
{
	if (WIFEXITED(*exit_status2))
	{
		*exit_status2 = WEXITSTATUS(*exit_status2);
		if (*exit_status2 == 141)
			*exit_status2 = 0;
		if (shell->input == -1 && shell->output != -1)
			*exit_status2 = 0;
	}
	else if (WIFSIGNALED(*exit_status2))
	{
		*exit_status2 = 128 + WTERMSIG(*exit_status2);
		if (*exit_status2 == 141)
			*exit_status2 = 0;
		if (shell->input == -1 && shell->output != -1)
			*exit_status2 = 0;
	}
}

void	handle_exit(int *exit_status1, int *exit_status2, t_shell_data *shell)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < shell->i)
	{
		shell->pid_current = waitpid(shell->pid_list[i], &status, 0);
		if ((shell->i - 1) >= 0
			&& shell->pid_current == shell->pid_list[shell->i - 1])
		{
			*exit_status1 = status;
		}
		else if (shell->pid_current == shell->pid_list[shell->i])
		{
			*exit_status2 = status;
		}
		i++;
	}
	handle_exit_status1(exit_status1, shell);
	handle_exit_status2(exit_status2, shell);
}
