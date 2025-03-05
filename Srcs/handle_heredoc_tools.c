/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc_tools.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:23:43 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/27 17:01:36 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	free_before_return(t_write_in_here_doc **write)
{
	free_variable((void **)&(*write)->line);
	free_variable((void **)&(*write)->line_to_history);
}

bool	condition_to_go_out_here(t_write_in_here_doc **write)
{
	return (ft_strncmp((*write)->line, (*write)->delimiter,
			ft_strlen((*write)->delimiter) + 1) == 0);
}

void	print_to_pipe(int pipefd[2], t_write_in_here_doc **write,
		t_shell_data *shell)
{
	if (ft_strncmp((*write)->line_to_history, (*write)->delimiter,
			ft_strlen((*write)->delimiter)) == 0)
	{
		(*write)->line_to_print = NULL;
	}
	else
	{
		(*write)->line_to_print = ft_substr((*write)->line_to_history, 0,
				ft_strlen((*write)->line_to_history)
				- ft_strlen((*write)->delimiter) - 2);
	}
	if ((*write)->line_to_print != NULL)
		write_line_to_pipe(pipefd, (*write)->line_to_print, (*write)->delimiter,
			shell);
	free_variable((void **)&(*write)->line_to_history);
}
