/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens_put_types.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:01:51 by dagudelo          #+#    #+#             */
/*   Updated: 2024/06/14 20:48:14 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	is_variable_check(t_token *token, t_cmd *pipe)
{
	(void)pipe;
	if (find_index('=', token->value) > 0 && token->value[0] != '-')
	{
		token->type = VARIABLE;
	}
}

bool	found_cmd_in_pipes(t_cmd *pipes)
{
	while (pipes)
	{
		if (found_cmd(pipes->tokens, CMD))
			return (true);
		pipes = pipes->next;
	}
	return (false);
}

bool	found_cmd(t_token *token, t_token_type type)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (current->type == type)
			return (true);
		current = current->next;
	}
	return (false);
}

void	is_command_check(t_token *token, t_token *head)
{
	if (found_cmd(head, CMD) == true)
		return ;
	if (token->prev == NULL && token->type == NO_TYPE)
	{
		token->type = CMD;
	}
	else if (token->prev != NULL && token->type == NO_TYPE
		&& token->prev->type != NO_TYPE && token->prev->type != CMD)
		token->type = CMD;
}

void	is_args_check(t_token *token, t_cmd *pipe)
{
	if (token->type == NO_TYPE || (token->type == VARIABLE
			&& token->prev != NULL && (token->prev->type == CMD
				|| token->prev->type == ARG)))
	{
		token->type = ARG;
		pipe->len_args++;
	}
}
