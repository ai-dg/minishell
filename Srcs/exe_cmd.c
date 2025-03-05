/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:40:37 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/27 13:21:40 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static void	fill_variable(t_cmd *pipe, t_token *current_token, int *i)
{
	while (current_token)
	{
		if (current_token->type == VARIABLE)
		{
			pipe->variables[*i] = ft_strdup(current_token->value);
			(*i)++;
		}
		current_token = current_token->next;
	}
	pipe->variables[*i] = NULL;
}

void	add_variables_to_char(t_cmd *pipe, t_shell_data *shell)
{
	int		len;
	t_token	*current_token;
	int		i;

	if (only_affectation(pipe) == false)
		return ;
	len = 0;
	current_token = pipe->tokens;
	while (current_token)
	{
		if (current_token->type == VARIABLE)
			len++;
		current_token = current_token->next;
	}
	pipe->variables = (char **)malloc(sizeof(char *) * (len + 1));
	if (pipe->variables == NULL)
		exit_1_malloc(&shell);
	i = 0;
	current_token = pipe->tokens;
	fill_variable(pipe, current_token, &i);
}

static void	malloc_variables_in_exe_cmd(t_shell_data *shell, int *i)
{
	shell->pid_list = NULL;
	shell->env_char = expand_env_to_char(shell->env, shell->env_char, shell);
	shell->pid_list = malloc(sizeof(pid_t) * (shell->total_pipes + 1));
	if (shell->pid_list == NULL)
		exit_1_malloc(&shell);
	*i = 0;
	while (*i < shell->total_pipes + 1)
	{
		shell->pid_list[*i] = 0;
		(*i)++;
	}
	if (shell->pid_list == NULL)
	{
		perror("malloc");
		free_malloc_exit_system(&shell);
		exit(errno);
	}
}

static void	put_values_to_false(t_shell_data *shell)
{
	if (shell->in_env_cmd_error == true)
		shell->exit_status = 127;
	shell->in_env_cmd_error = false;
	shell->dollar_expansion = false;
	shell->echo_in_pipe = false;
	shell->just_one_pipe = false;
	shell->count_in_doc = 0;
}

void	exe_cmd(t_shell_data *shell)
{
	int	i;

	malloc_variables_in_exe_cmd(shell, &i);
	shell->i = 0;
	add_variables_to_char(shell->pipe, shell);
	shell->exit_status = 0;
	if (shell->pipe->variables)
		add_session(shell, shell->pipe->variables);
	if (shell->exit_status != 0)
		return ;
	print_tokens_status(shell);
	check_path_infile_outfile_error(shell->pipe);
	if (is_cmd_buildin(shell->pipe->cmd) == true && shell->pipe->next == NULL)
	{
		shell->just_one_pipe = true;
		exe_builtin_cmd(shell->pipe->cmd, shell->pipe->args, shell);
	}
	else
		shell->exit_status = pipex(shell->pipe, shell);
	put_values_to_false(shell);
}
