/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_shell_execute_shell.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 22:11:14 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/26 16:59:22 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	execute_shell(char *prompt, t_shell_data *shell, int *count,
		bool have_to_free)
{
	if (prompt)
	{
		free_variable((void **)&shell->prompt);
		shell->prompt = prompt;
	}
	parsing_and_stack_malloc(shell);
	if (args_parsed_to_stack(shell) == -1)
	{
		free_loop_malloc_system(&shell);
		return ;
	}
	args_init(shell);
	(*count)++;
	if (ft_strcmp(shell->prompt, "|\0") == 0)
		case_bar_vertical_command(shell);
	exe_cmd(shell);
	if (have_to_free)
		free_loop_malloc_system(&shell);
}
