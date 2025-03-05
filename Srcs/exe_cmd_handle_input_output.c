/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd_handle_input_output.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:42:45 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/19 18:34:38 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static void	init_remove_data(t_remove_input_output *remove, t_token *tokens)
{
	remove->current_token = tokens;
	remove->i = 0;
	remove->j = 0;
	remove->k = 0;
}

static void	remove_if_error_open_or_create_file(t_cmd *pipe, t_token *tokens)
{
	t_remove_input_output	remove;

	init_remove_data(&remove, tokens);
	while (remove.current_token)
	{
		if (remove.current_token->type == PATH_INFILE)
		{
			if (check_input_filest(pipe, &remove.i, &remove.j,
					&remove.k) == true)
				break ;
		}
		else if (remove.current_token->type == PATH_OUTFILE)
		{
			if (check_output_files(pipe, &remove.i, &remove.j,
					&remove.k) == true)
				break ;
		}
		else if (remove.current_token->type == APPEND_REDIR_OUT)
		{
			if (check_append_files(pipe, &remove.i, &remove.j,
					&remove.k) == true)
				break ;
		}
		remove.current_token = remove.current_token->next;
	}
}

void	check_path_infile_outfile_error(t_cmd *pipe)
{
	t_cmd	*current_pipe;

	current_pipe = pipe;
	while (current_pipe)
	{
		remove_if_error_open_or_create_file(current_pipe, current_pipe->tokens);
		current_pipe = current_pipe->next;
	}
}
