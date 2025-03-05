/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 10:56:46 by ls                #+#    #+#             */
/*   Updated: 2024/06/26 16:59:15 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	count_exec_unit_nodes(t_exec_unit *exec_unit)
{
	if (!exec_unit)
		return (0);
	return (count_exec_unit_nodes(exec_unit->l_unit)
		+ count_exec_unit_nodes(exec_unit->r_unit) + 1);
}

int	execute_commands(t_shell_data *shell)
{
	if (shell->exit_signals2 != 0)
	{
		shell->exit_status = shell->exit_signals2;
		shell->exit_signals2 = 0;
	}
	else if (g_receipt != 0)
	{
		shell->exit_status = get_status_from_sig(shell);
	}
	shell->exit_signals = shell->exit_status;
	parsing_and_stack_malloc(shell);
	if (args_parsed_to_stack(shell) == -1)
	{
		free_loop_malloc_system(&shell);
		return (0);
	}
	args_init(shell);
	if (ft_strcmp(shell->prompt, "|\0") == 0)
		case_bar_vertical_command(shell);
	exe_cmd(shell);
	free_loop_malloc_system(&shell);
	return (shell->status);
}
