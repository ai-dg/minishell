/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:01:51 by dagudelo          #+#    #+#             */
/*   Updated: 2024/06/23 16:49:59 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	put_index_pipes(t_shell_data *shell)
{
	int		i;
	t_cmd	*current;

	i = 0;
	current = shell->pipe;
	shell->total_pipes = 0;
	while (current)
	{
		current->index = i;
		current = current->next;
		i++;
	}
	shell->total_pipes = i;
}

bool	there_is_a_path(t_token *token, t_token_type type)
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

static void	fill_path_files(t_cmd *current, t_shell_data *shell)
{
	if (there_is_a_path(current->tokens, PATH_INFILE) == true)
		current->path_infiles = get_path_files(current->tokens, current,
				PATH_INFILE, shell);
	else
		current->path_infiles = NULL;
	if (there_is_a_path(current->tokens, PATH_OUTFILE) == true)
		current->path_outfiles = get_path_files(current->tokens, current,
				PATH_OUTFILE, shell);
	else
		current->path_outfiles = NULL;
	if (there_is_a_path(current->tokens, APPEND_REDIR_OUT) == true)
		current->path_append_outfiles = get_path_files(current->tokens, current,
				APPEND_REDIR_OUT, shell);
	else
		current->path_append_outfiles = NULL;
	if (there_is_a_path(current->tokens, DELIMITER) == true)
		current->delimiter_var = get_path_files(current->tokens, current,
				DELIMITER, shell);
	else
		current->delimiter_var = NULL;
}

int	args_init(t_shell_data *shell)
{
	t_cmd	*current;

	if (shell->pipe == NULL)
	{
		return (0);
	}
	current = shell->pipe;
	shell->exist_cmd = false;
	while (current)
	{
		token_init(current, shell);
		current = current->next;
	}
	put_index_pipes(shell);
	current = shell->pipe;
	while (current)
	{
		fill_path_files(current, shell);
		current = current->next;
	}
	return (0);
}
