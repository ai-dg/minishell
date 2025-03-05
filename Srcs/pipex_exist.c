/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:46:34 by dagudelo          #+#    #+#             */
/*   Updated: 2024/06/14 19:01:48 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

bool	if_double_redir_input_exist(t_cmd *pipes)
{
	t_token	*current;

	current = pipes->tokens;
	while (current)
	{
		if (current->type == DELIMITER)
			return (true);
		current = current->next;
	}
	return (false);
}

bool	if_double_redir_input_is_last(t_cmd *pipes)
{
	t_token	*current;
	int		type;

	current = pipes->tokens;
	type = 0;
	while (current)
	{
		if (current->type == DELIMITER || current->type == PATH_INFILE)
			type = current->type;
		current = current->next;
	}
	if (type == DELIMITER)
		return (true);
	return (false);
}

bool	if_double_redir_output_exist(t_cmd *pipes)
{
	t_token	*current;

	current = pipes->tokens;
	while (current)
	{
		if (current->type == APPEND_REDIR_OUT)
			return (true);
		current = current->next;
	}
	return (false);
}
