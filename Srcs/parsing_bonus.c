/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:24:09 by ls                #+#    #+#             */
/*   Updated: 2024/06/24 07:13:21 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static void	execution_procedure(t_shell_data *shell, t_exec_unit *exec_unit)
{
	free_variable((void **)&shell->prompt);
	shell->prompt = ft_strdup(exec_unit->prompt);
	execute_commands(shell);
	shell->last_status = shell->exit_status;
}

int	exec_cmd_tree(t_exec_unit *exec_unit, t_shell_data *shell, int *count)
{
	if (!exec_unit)
		return (-1);
	if (exec_unit->type == IS_A_LEAF)
		return (execution_procedure(shell, exec_unit), shell->last_status);
	else if (exec_unit->type == IS_A_BRANCH)
	{
		if (ft_strncmp(exec_unit->prompt, "&&", 2) == 0)
		{
			if (exec_cmd_tree(exec_unit->l_unit, shell, count) == 0)
				return (exec_cmd_tree(exec_unit->r_unit, shell, count));
			else
				return (-1);
		}
		else if (ft_strncmp(exec_unit->prompt, "||", 2) == 0)
		{
			if (exec_cmd_tree(exec_unit->l_unit, shell, count) != 0)
				return (exec_cmd_tree(exec_unit->r_unit, shell, count));
			else
				return (0);
		}
	}
	return (-1);
}

void	breakdown_parenthesis(char *prompt, t_shell_data *shell, int *count)
{
	static char	*tokens[] = {"||", "&&", "(", ")", NULL};

	shell->exec_units = NULL;
	if (ft_strsstr(prompt, tokens))
	{
		sanithize_prompt(prompt);
		if (ft_strsstr(prompt, tokens))
		{
			if (shell->exec_units)
				free_exec_unit(&shell->exec_units);
			shell->exec_units = split_in_exec_units(prompt, shell->exec_units);
			if (shell->exec_units)
				exec_cmd_tree(shell->exec_units, shell, count);
		}
		else
		{
			execute_commands(shell);
		}
	}
	else
		execute_commands(shell);
}
