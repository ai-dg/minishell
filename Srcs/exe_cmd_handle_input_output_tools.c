/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd_handle_input_output_tools.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:42:45 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/20 18:19:46 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	remove_nodes_after_i_and_j_and_k(t_cmd *pipe, int i, int j, int k)
{
	while (pipe->path_infiles != NULL && pipe->path_infiles[i] != NULL)
	{
		free_variable((void **)&pipe->path_infiles[i]);
		pipe->path_infiles[i] = NULL;
		i++;
	}
	while (pipe->path_outfiles != NULL && pipe->path_outfiles[j] != NULL)
	{
		free_variable((void **)&pipe->path_outfiles[j]);
		pipe->path_outfiles[j] = NULL;
		j++;
	}
	while (pipe->path_append_outfiles != NULL
		&& pipe->path_append_outfiles[k] != NULL)
	{
		free_variable((void **)&pipe->path_append_outfiles[k]);
		pipe->path_append_outfiles[k] = NULL;
		k++;
	}
}

bool	check_input_filest(t_cmd *pipe, int *i, int *j, int *k)
{
	if (pipe->path_infiles != NULL)
	{
		if (access(pipe->path_infiles[*i], F_OK | R_OK) == -1)
		{
			remove_nodes_after_i_and_j_and_k(pipe, *i + 1, *j, *k);
			return (true);
		}
		(*i)++;
	}
	return (false);
}

bool	check_output_files(t_cmd *pipe, int *i, int *j, int *k)
{
	if (pipe->path_outfiles != NULL && pipe->path_outfiles[*j] != NULL)
	{
		if (access(pipe->path_outfiles[*j], F_OK) != -1)
		{
			if (access(pipe->path_outfiles[*j], W_OK) == -1)
			{
				remove_nodes_after_i_and_j_and_k(pipe, *i, *j + 1, *k);
				return (true);
			}
		}
		(*j)++;
	}
	return (false);
}

bool	check_append_files(t_cmd *pipe, int *i, int *j, int *k)
{
	if (pipe->path_append_outfiles != NULL
		&& pipe->path_append_outfiles[*k] != NULL)
	{
		if (access(pipe->path_append_outfiles[*k], F_OK) != -1)
		{
			if (access(pipe->path_append_outfiles[*k], W_OK) == -1)
			{
				remove_nodes_after_i_and_j_and_k(pipe, *i, *j, *k + 1);
				return (true);
			}
		}
		k++;
	}
	return (false);
}
