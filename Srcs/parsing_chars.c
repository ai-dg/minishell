/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_chars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 22:11:14 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/14 20:39:58 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static void	fill_token_with_redir(t_token *current, t_token *next_next,
	t_shell_data *shell)
{
	current->value = ft_fstrjoin(current->value, ">", FIRST);
	debug_char(current->value, VIOLET, shell);
	next_next = current->next->next;
	free_env_node_token(current->next);
	current->next = next_next;
	if (next_next != NULL)
		next_next->prev = current;
}

void	cat_char_to_one(t_token *token, t_shell_data *shell)
{
	t_token	*current;
	t_token	*next_next;

	current = token;
	while (current != NULL && current->next != NULL)
	{
		if (ft_strncmp(current->value, ">", 1) == 0
			&& ft_strncmp(current->next->value, ">", 1) == 0)
			fill_token_with_redir(current, next_next, shell);
		else if (ft_strncmp(current->value, "<", 1) == 0
			&& ft_strncmp(current->next->value, "<", 1) == 0)
		{
			current->value = ft_fstrjoin(current->value, "<", FIRST);
			debug_char(current->value, VIOLET, shell);
			next_next = current->next->next;
			free_env_node_token(current->next);
			current->next = next_next;
			if (next_next != NULL)
				next_next->prev = current;
		}
		else
			current = current->next;
	}
}

void	double_to_char(t_cmd *pipe, t_shell_data *shell)
{
	t_cmd	*current;

	current = pipe;
	while (current != NULL)
	{
		cat_char_to_one(current->tokens, shell);
		current = current->next;
	}
}
