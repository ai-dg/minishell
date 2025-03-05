/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils_status_print.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:21:51 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/30 17:15:40 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	print_splitted(char **chars)
{
	int	i;

	i = 0;
	while (chars[i])
	{
		printf("word[%d]: ", i);
		print_string(chars[i]);
		i++;
	}
}

void	handle_redirection_types(t_token *token)
{
	if (token->type == REDIR_IN)
	{
		printf("REDIR_IN\n");
	}
	else if (token->type == REDIR_OUT)
	{
		printf("REDIR_OUT\n");
	}
	else if (token->type == DBLE_REDIR_IN)
	{
		printf("DBLE_REDIR_IN\n");
	}
	else if (token->type == DBLE_REDIR_OUT)
	{
		printf("DBLE_REDIR_OUT\n");
	}
	else if (token->type == APPEND_REDIR_OUT)
	{
		printf("APPEND_REDIR_OUT\n");
	}
}

void	handle_path_types(t_token *token)
{
	if (token->type == PATH_INFILE)
	{
		printf("PATH_INFILE\n");
	}
	else if (token->type == PATH_OUTFILE)
	{
		printf("PATH_OUTFILE\n");
	}
}

void	handle_other_types(t_token *token)
{
	if (token->type == DOLLAR_IN)
		printf("DOLLAR_IN\n");
	else if (token->type == VARIABLE)
		printf("VARIABLE\n");
	else if (token->type == CMD)
		printf("CMD\n");
	else if (token->type == ARG)
		printf("ARG\n");
	else if (token->type == DELIMITER)
		printf("DELIMITER\n");
	else if (token->type == NO_TYPE)
		printf("NO_TYPE\n");
	else
		printf("UNKNOWN_TYPE\n");
}

void	status(t_token *token, t_shell_data *shell)
{
	if (shell->debug_mode == DEV)
	{
		if (!token)
		{
			return ;
		}
		if (token->type <= DBLE_REDIR_OUT || token->type == APPEND_REDIR_OUT)
		{
			handle_redirection_types(token);
		}
		else if (token->type == PATH_INFILE || token->type == PATH_OUTFILE)
		{
			handle_path_types(token);
		}
		else
		{
			handle_other_types(token);
		}
	}
}
