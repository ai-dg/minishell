/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_args_pipes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:55:44 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/15 12:35:36 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

bool	printable_before_pipe(char *inst, int i)
{
	while (i >= 0 && inst[i] && inst[i] != '|')
	{
		if (inst[i] > 32 && inst[i] < 127 && inst[i] != '|' && inst[i] != '\\'
			&& inst[i] != '<' && inst[i] != '>')
		{
			return (true);
		}
		i--;
	}
	return (false);
}

int	count_pipes_in_inst(char *inst, int i, char c)
{
	int	count;

	count = 0;
	while (inst[i])
	{
		if (inst[i] == c)
		{
			count++;
		}
		if (inst[i] >= 32 && inst[i] != c)
			return (count);
		i++;
	}
	return (count);
}

void	printf_syntax_error_vertical(int cases)
{
	if (cases == 1)
		printf("minishell : syntax error near unexpected token `|'\n");
	if (cases == 2)
		printf("minishell : syntax error near unexpected token `||'\n");
}

int	find_error_case_pipe(char *inst, int i, char c)
{
	int	count;

	count = count_pipes_in_inst(inst, i, c);
	if (printable_before_pipe(inst, i - 1) == false)
	{
		if (count > 1)
			return (printf_syntax_error_vertical(2), true);
		else if (count == 1)
			return (printf_syntax_error_vertical(1), true);
	}
	if (count == 3)
		return (printf_syntax_error_vertical(1), true);
	if (count > 3)
		return (printf_syntax_error_vertical(2), true);
	return (false);
}

int	check_pipe_system(char *inst, t_shell_data *shell)
{
	int	i;

	i = 0;
	(void)shell;
	while (inst && inst[i])
	{
		if (inst[i] == '|')
		{
			if (find_error_case_pipe(inst, i, '|') == true)
				return (1);
			while (inst[i] == '|' && inst[i] != '\0')
			{
				i++;
			}
		}
		if (inst[i] != '\0')
		{
			i++;
		}
	}
	return (0);
}
