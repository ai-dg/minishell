/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc_readline_tools.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:23:43 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/27 17:03:01 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	error_here_doc(t_write_in_here_doc *write, t_cmd *cmd)
{
	(void)cmd;
	write->msg = ft_itoa(write->position);
	error_msg("minishell: warning: here-document at line ");
	error_msg(write->msg);
	error_msg(" delimited by end-of-file (wanted `");
	error_msg(write->delimiter);
	error_msg("')\n");
	free_variable((void **)&write->msg);
	free_variable((void **)&write->line_to_history);
	free_variable((void **)&write->tester);
}

void	init_write_in_here_doc(t_write_in_here_doc *write, char *delimiter,
		t_shell_data *shell)
{
	(void)shell;
	write->line = NULL;
	write->tester = NULL;
	write->msg = NULL;
	write->i = 0;
	write->error = false;
	write->in_signals = false;
	write->position = 0;
	write->line_to_history = NULL;
	write->line_to_print = NULL;
	write->delimiter = delimiter;
	write->lenght = 3 + ft_strlen(write->delimiter);
	add_history(shell->prompt);
	add_to_history(shell->prompt, shell);
	write->i = 0;
}

void	save_position(t_write_in_here_doc **write, t_shell_data *shell)
{
	if (shell->to_expand_in_doc[shell->count_in_doc] == false)
	{
		if (ft_strstr((*write)->delimiter, (*write)->line) == NULL)
		{
			shell->in_here_doc = true;
			(*write)->line = expand_variable((*write)->line, shell);
			shell->in_here_doc = false;
		}
	}
	shell->number_line_here_docs++;
	if ((*write)->i == 0)
		(*write)->position = shell->number_line_here_docs;
}

void	fill_line_history(t_write_in_here_doc **write)
{
	(*write)->line_to_history = ft_fstrjoin((*write)->line_to_history,
			(*write)->line, FIRST);
	(*write)->line_to_history = ft_fstrjoin((*write)->line_to_history, "\n",
			FIRST);
}
