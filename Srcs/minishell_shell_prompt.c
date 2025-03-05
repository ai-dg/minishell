/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_shell_prompt.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 22:11:14 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/27 17:01:05 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static void	handle_all_readlines_in_prompt(t_shell_data **shell)
{
	if (readline_needed((*shell)->prompt) == true
		&& check_and_system(&(*shell)->prompt, (*shell), SILENT) == 0)
		(*shell)->prompt = handle_and_readline((*shell)->prompt, (*shell));
	if (check_and_system(&(*shell)->prompt, (*shell), SILENT) == 0)
		handle_readline_parentheses(&(*shell)->prompt, (*shell));
	special_bar_non_printable_add(&(*shell)->prompt, (*shell));
}

static void	execute_minishell_program(t_shell_data **shell, int *count)
{
	(*shell)->home = get_home_path();
	if (ft_strstr((*shell)->prompt, "<<") == 0)
	{
		while (find_isolated('~', (*shell)->prompt) > -1)
			(*shell)->prompt = expand_char(&(*shell)->prompt, "~",
					&(*shell)->home, (*shell));
		if (!ft_strstr((*shell)->prompt, "echo"))
			(*shell)->prompt = expand_aliases((*shell)->prompt, (*shell));
	}
	free_variable((void **)&(*shell)->home);
	handle_all_readlines_in_prompt((shell));
	if (handle_basic_invalid_args(&(*shell)->prompt, (*shell)))
	{
		(*shell)->prompt = write_in_here_doc_prompt((*shell)->prompt, (*shell));
		(*shell)->prompt_in = ft_strdup((*shell)->prompt);
		if ((*shell)->write_in_here_doc == false)
			handle_history_add_readline(&(*shell)->prompt, (*shell));
		else
			(*shell)->write_in_here_doc = false;
		breakdown_parenthesis((*shell)->prompt, (*shell), count);
		if ((*shell)->exec_units)
			free_exec_unit(&(*shell)->exec_units);
		(*shell)->exec_units = NULL;
	}
	free_loop_malloc_system(shell);
}

static void	exit_in_ctrl_d_case(t_shell_data *shell, int *count)
{
	if (*count > 0)
		free_array(&shell->env_char);
	rl_clear_history();
	free_malloc_exit_system_ctrl_d(&shell);
}

static void	free_loop_in_prompt(t_shell_data *shell)
{
	if (shell->exec_units)
		free_exec_unit(&shell->exec_units);
	shell->exec_units = NULL;
	free_variable((void **)&shell->prompt);
	shell->prompt = NULL;
}

int	shell_prompt(t_shell_data *shell)
{
	static int	count;

	count = 0;
	while (1)
	{
		reopen_stdin_if_needed();
		initialize_prompt_value(shell);
		if (shell->prompt && ft_strlen(shell->prompt) == 0)
		{
			free_variable((void **)&shell->prompt);
			continue ;
		}
		else if (shell->prompt)
			execute_minishell_program(&shell, &count);
		else if (shell->in_script == true)
			break ;
		else
		{
			exit_in_ctrl_d_case(shell, &count);
			break ;
		}
		free_loop_in_prompt(shell);
	}
	return (0);
}
