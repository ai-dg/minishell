/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_fill_all_fds_doc.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:46:34 by dagudelo          #+#    #+#             */
/*   Updated: 2024/07/01 12:08:12 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	fill_all_fds_doc(t_cmd *current_pipe, t_pipefd *current_pipefd1,
		t_fds *current_fds, t_shell_data *shell)
{
	int	i;

	i = 0;
	while (current_pipe->delimiter_var[i])
	{
		if (if_double_redir_input_exist(current_pipe) == true)
		{
			if (if_double_redir_input_is_last(current_pipe) == true)
			{
				current_pipefd1->values = clear_pipe(current_pipefd1->values,
						shell);
				write_in_here_doc(current_pipefd1->values, current_pipe,
					current_pipe->delimiter_var[i], shell);
			}
			else
				write_in_here_doc(shell->fd_null, current_pipe,
					current_pipe->delimiter_var[i], shell);
		}
		i++;
	}
	*current_fds->input = current_pipefd1->values[0];
}
