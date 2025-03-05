/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens_fill_tokens.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:01:51 by dagudelo          #+#    #+#             */
/*   Updated: 2024/06/24 16:40:46 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	put_cmd_on_pipe(t_cmd *pipe)
{
	t_token	*current;

	current = pipe->tokens;
	while (current)
	{
		if (current->type == CMD)
		{
			pipe->cmd = ft_strdup(current->value);
			break ;
		}
		current = current->next;
	}
}

int	token_init_pass2(t_cmd *pipe)
{
	t_token	*current;

	current = pipe->tokens;
	while (current)
	{
		is_args_check(current, pipe);
		current = current->next;
	}
	return (0);
}

static void	fill_args_and_cmd(t_cmd *pipe, t_shell_data *shell,
		t_token *current, int *i)
{
	if (current->type == CMD)
	{
		pipe->cmd = ft_strdup(current->value);
		pipe->args[*i] = ft_strdup(pipe->cmd);
		shell->exist_cmd = true;
		(*i)++;
	}
	if (current->type == ARG && *i != 0)
	{
		pipe->args[*i] = ft_strdup(current->value);
		(*i)++;
	}
}

int	tokens_to_chars(t_cmd *pipe, t_shell_data *shell)
{
	t_token	*current;
	int		nodes;
	int		i;

	(void)shell;
	current = pipe->tokens;
	nodes = count_token_nodes(current);
	pipe->args = (char **)malloc(sizeof(char *) * (nodes + 1));
	if (!pipe->args)
		exit_1_malloc(&shell);
	i = 0;
	while (current)
	{
		fill_args_and_cmd(pipe, shell, current, &i);
		current = current->next;
	}
	pipe->args[i] = NULL;
	return (0);
}

int	token_init(t_cmd *pipe, t_shell_data *shell)
{
	t_token	*current;

	pipe->len_args = 0;
	current = pipe->tokens;
	while (current)
	{
		basic_token_checker(current, pipe);
		is_variable_check(current, pipe);
		is_command_check(current, pipe->tokens);
		pipe->index++;
		current = current->next;
	}
	token_init_pass2(pipe);
	return (tokens_to_chars(pipe, shell));
}
