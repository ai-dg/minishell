/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_shell_prompt_init.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 22:11:14 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/26 11:23:49 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	parsing_and_stack_malloc(t_shell_data *shell)
{
	fill_args_to_parsed(shell->prompt, shell);
	if (ft_strcmp(shell->prompt, "*/*") == 0 && (!shell->initial_parsed
			|| !shell->initial_parsed[0]))
	{
		print_error(shell->prompt, " No such file or directory\n", shell);
		shell->exit_status = 127;
	}
}

void	case_bar_vertical_command(t_shell_data *shell)
{
	shell->pipe->cmd = ft_strdup(shell->prompt);
	shell->pipe->args = (char **)malloc(sizeof(char *) * 2);
	if (!shell->pipe->args)
		exit_1_malloc(&shell);
	shell->pipe->args[0] = ft_strdup(shell->pipe->cmd);
	shell->pipe->args[1] = NULL;
	exe_cmd(shell);
}
