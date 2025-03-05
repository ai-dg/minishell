/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_args_redir_printers.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:33:48 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/15 12:34:36 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

bool	find_error_case_special_number(t_find_error_case_syntax *find,
		char c, t_shell_data *shell)
{
	if (c == '<')
	{
		if (find->count_consecutive == 4)
			return (print_syntax_error(shell, "<"), true);
		else if (find->count_consecutive == 5)
			return (print_syntax_error(shell, "<<"), true);
		else if (find->count_consecutive > 5)
			return (print_syntax_error(shell, "<<<"), true);
	}
	else if (c == '>')
	{
		if (find->count_consecutive == 3)
			return (print_syntax_error(shell, ">"), true);
		else if (find->count_consecutive >= 4)
			return (print_syntax_error(shell, ">>"), true);
	}
	return (false);
}

void	print_first_case_next_redir(t_find_error_case_syntax *find,
		t_shell_data *shell, char *inst)
{
	find->count_consecutive_after = count_consecutive_redir(inst, '>',
			find->position);
	if (find->count_consecutive_after == 1)
		print_syntax_error(shell, ">");
	else if (find->count_consecutive_after >= 2)
		print_syntax_error(shell, ">>");
}

void	print_second_case_next_redir(t_find_error_case_syntax *find,
		t_shell_data *shell, char *inst)
{
	find->count_consecutive_after = count_consecutive_redir(inst, '<',
			find->position);
	if (find->count_consecutive_after == 1)
		print_syntax_error(shell, "<");
	else if (find->count_consecutive_after == 2)
		print_syntax_error(shell, "<<");
	else if (find->count_consecutive_after >= 3)
		print_syntax_error(shell, "<<<");
}

void	print_third_case_next_redir(t_find_error_case_syntax *find,
		t_shell_data *shell, char c)
{
	if (c == '<' && find->count_consecutive <= 3)
		print_syntax_error(shell, "newline");
	else if (c == '<' && find->count_consecutive == 4)
		print_syntax_error(shell, "<");
	else if (c == '<' && find->count_consecutive == 5)
		print_syntax_error(shell, "<<");
	else if (c == '<' && find->count_consecutive > 5)
		print_syntax_error(shell, "<<<");
	else if (c == '>' && find->count_consecutive <= 2)
		print_syntax_error(shell, "newline");
	else if (c == '>' && find->count_consecutive == 3)
		print_syntax_error(shell, ">");
	else if (c == '>' && find->count_consecutive >= 3)
		print_syntax_error(shell, ">>");
}

bool	check_next_redir_final(t_find_error_case_syntax *find,
		t_shell_data *shell, char *inst, char c)
{
	if (printable_after_redir(inst, find->j, &find->position) == false)
	{
		if (inst[find->position] == '>')
			print_first_case_next_redir(find, shell, inst);
		else if (inst[find->position] == '<')
			print_second_case_next_redir(find, shell, inst);
		else
			print_third_case_next_redir(find, shell, c);
		return (true);
	}
	return (false);
}
