/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_args_parentheses.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 08:12:58 by ls                #+#    #+#             */
/*   Updated: 2024/06/22 16:00:20 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

bool	check_found_redir(char *inst, int *i)
{
	int	x;

	x = *i - 1;
	while (x >= 0 && inst[x] && is_special_char(inst[x]) == false)
	{
		if (inst[x] == '>' || inst[x] == '<')
			return (true);
		x--;
	}
	return (false);
}

bool	find_errors_open(char *inst, int *i, t_shell_data *shell)
{
	int		x;
	char	*to_print;
	bool	found_redir;

	x = *i - 1;
	found_redir = false;
	found_redir = check_found_redir(inst, i);
	while (x >= 0 && is_special_char(inst[x]) == false)
	{
		if (is_printable_but_no_special(inst[x], SKIP_PARENTHESIS) == true)
		{
			if (found_redir == false)
			{
				to_print = find_str_to_print(inst, i, shell);
				printf("minishell: syntax error near unexpected token `%s'\n",
					to_print);
				free_variable((void **)&to_print);
			}
			else
				printf("minishell: syntax error near unexpected token `('\n");
			return (true);
		}
		x--;
	}
	return (false);
}

bool	find_errors_close(char *inst, int *i)
{
	int	x;

	x = *i - 1;
	while (x >= 0 && is_special_char(inst[x]) == false)
	{
		if (is_printable_but_no_special(inst[x], SKIP_PARENTHESIS) == true)
		{
			return (false);
		}
		x--;
	}
	printf("minishell: syntax error near unexpected token `)'\n");
	return (true);
}

bool	find_errors_open_close_repeat(char *inst)
{
	int	i;
	int	nbr_open;
	int	nbr_close;

	i = 0;
	nbr_open = 0;
	nbr_close = 0;
	while (inst[i])
	{
		if (inst[i] == '(')
			nbr_open++;
		else if (inst[i] == ')')
			nbr_close++;
		i++;
	}
	if (nbr_open != nbr_close)
	{
		printf("minishell: syntax error near unexpected token `)'\n");
		return (true);
	}
	return (false);
}

bool	check_parenth_system(char *inst, t_shell_data *shell)
{
	int	i;

	if (shell->in_script == true && shell->in_parentheses == false)
		return (false);
	i = 0;
	while (inst[i])
	{
		if (inst[i] == '(')
		{
			if (find_errors_open(inst, &i, shell) == true)
				return (true);
		}
		else if (inst[i] == ')')
		{
			if (find_errors_close(inst, &i) == true)
				return (true);
		}
		i++;
	}
	if (find_errors_open_close_repeat(inst) == true)
		return (true);
	return (false);
}
