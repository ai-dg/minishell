/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_args_redir_printers_tools.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:44:50 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/16 17:10:52 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

bool	printable_after_redir(char *inst, int i, int *position)
{
	while (inst[i] && inst[i] != '<' && inst[i] != '>')
	{
		if (inst[i] > 32 && inst[i] < 127)
		{
			return (true);
		}
		i++;
	}
	(*position) = i;
	return (false);
}

void	print_syntax_error(t_shell_data *shell, const char *token)
{
	ft_fprintf(stderr, "minishell : syntax error near unexpected token `%s'\n",
		token);
	shell->exit_status = 2;
}

void	print_number_special_case(t_shell_data *shell,
		t_find_error_case_syntax *find)
{
	if (find->count_consecutive == 1
		&& find->count_consecutive_after_redir == 1)
		print_syntax_error(shell, "newline");
	if (find->count_consecutive == 1
		&& find->count_consecutive_after_redir == 2)
		print_syntax_error(shell, ">");
	if (find->count_consecutive == 1
		&& find->count_consecutive_after_redir >= 3)
		print_syntax_error(shell, ">>");
	if ((find->count_consecutive >= 2 && find->count_consecutive <= 3)
		&& find->count_consecutive_after_redir == 1)
		print_syntax_error(shell, ">");
	if ((find->count_consecutive >= 2 && find->count_consecutive <= 3)
		&& find->count_consecutive_after_redir >= 2)
		print_syntax_error(shell, ">>");
	if (find->count_consecutive == 4
		&& find->count_consecutive_after_redir >= 1)
		print_syntax_error(shell, "<>");
	if (find->count_consecutive == 5
		&& find->count_consecutive_after_redir >= 1)
		print_syntax_error(shell, "<<");
	if (find->count_consecutive == 6
		&& find->count_consecutive_after_redir >= 1)
		print_syntax_error(shell, "<<<");
}
