/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens_checker.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:48:25 by dagudelo          #+#    #+#             */
/*   Updated: 2024/06/27 16:42:44 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static void	double_redir_token(t_token *token, t_cmd *pipe)
{
	(void)pipe;
	if (token->value && ft_strncmp(token->value, "<<", 2) == 0)
	{
		token->type = DBLE_REDIR_IN;
		if (token->next != NULL)
		{
			token->next->type = DELIMITER;
		}
	}
	if (ft_strncmp(token->value, ">>", 2) == 0)
	{
		token->type = DBLE_REDIR_OUT;
		if (token->next != NULL)
			token->next->type = APPEND_REDIR_OUT;
	}
}

void	basic_token_checker(t_token *token, t_cmd *pipe)
{
	(void)pipe;
	if (token == NULL)
		return ;
	if (ft_strncmp(token->value, ">", 1) == 0)
	{
		token->type = REDIR_OUT;
		if (token->next != NULL && token->next->value
			&& ft_strcmp(token->next->value, ">") != 0)
		{
			token->next->type = PATH_OUTFILE;
		}
	}
	if (ft_strncmp(token->value, "<", 1) == 0)
	{
		token->type = REDIR_IN;
		if (token->next != NULL && token->next->value != NULL
			&& ft_strcmp(token->next->value, "<") != 0)
		{
			token->next->type = PATH_INFILE;
		}
	}
	double_redir_token(token, pipe);
}
