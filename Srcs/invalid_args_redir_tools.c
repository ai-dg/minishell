/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_args_redir_tools.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:32:54 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/15 12:32:51 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

bool	find_error_case_syntax(char *inst, int i, char c, t_shell_data *shell)
{
	t_find_error_case_syntax	find;
	bool						result;

	result = false;
	init_find(&find);
	count_special_order_redir(inst, i, &find.alpha, &find.number_special);
	if (find.number_special == 1 && find.alpha == true)
		return (false);
	find.count_consecutive = count_consecutive_redir(inst, c, i);
	find_opposite_redir_consecutive(inst, i, c, &find);
	result = check_special_number_case(&find, shell);
	if (result == true)
		return (true);
	result = find_error_case_special_number(&find, c, shell);
	if (result == true)
		return (true);
	find.j = i + find.count_consecutive;
	result = check_next_redir_final(&find, shell, inst, c);
	if (result == true)
		return (true);
	return (false);
}

bool	check_special_number_case(t_find_error_case_syntax *find,
		t_shell_data *shell)
{
	if (find->number_special >= 1)
	{
		if (find->number_special == 1)
			return (print_number_special_case(shell, find), true);
		return (print_syntax_error(shell, "<>"), true);
	}
	return (false);
}

int	count_consecutive_redir(char *inst, char c, int i)
{
	int	count;

	count = 0;
	while (inst[i] == c)
	{
		count++;
		i++;
	}
	return (count);
}

int	count_special_order_redir(char *inst, int i, bool *alpha,
		int *number_special)
{
	int	count;

	count = 0;
	while (inst[i])
	{
		if (inst[i] == '<' && inst[i + 1] == '>')
		{
			count++;
			if (count > (*number_special))
				(*number_special) = count;
		}
		if (inst[i] > 32 && inst[i] < 127 && inst[i] != '<' && inst[i] != '>')
		{
			(*alpha) = true;
			count = 0;
		}
		i++;
	}
	return (count);
}
