/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_shell_prompt_tools.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 22:11:14 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/28 07:26:21 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	initialize_prompt_value(t_shell_data *shell)
{
	if (shell->in_script == false)
	{
		free_variable((void **)&shell->pline);
		shell->pline = prompt_line(shell);
		free_variable((void **)&shell->prompt);
		shell->prompt = readline(shell->pline);
		ft_unallocated_trim(shell->prompt);
	}
	else
	{
		free_variable((void **)&shell->prompt);
		shell->prompt = ft_strdup(shell->line);
		free_variable((void **)&shell->line);
	}
}

void	handle_history_add_readline(char **prompt, t_shell_data *shell)
{
	if (shell->in_script == false)
	{
		shell->tmp_history = ft_strdup(*prompt);
		remove_non_printable_chars(shell->tmp_history);
		add_history(shell->tmp_history);
		add_to_history(shell->tmp_history, shell);
		free_variable((void **)&shell->tmp_history);
	}
}
