/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_args_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:24:52 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/15 12:39:15 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

bool	find_new_line_case(char *inst, int i, char c)
{
	int	consecutive_redir;

	consecutive_redir = 0;
	if (inst[i] == '<')
		consecutive_redir = count_consecutive_redir(inst, '<', i);
	else if (inst[i] == '>')
		consecutive_redir = count_consecutive_redir(inst, '>', i);
	printf("consecutive_redir = %d\n", consecutive_redir);
	if (consecutive_redir > 3 && c == '<')
		return (false);
	if (consecutive_redir > 2 && c == '>')
		return (false);
	return (false);
}

bool	find_single_redir_in_case(char *inst, int i, char c)
{
	int	consecutive_redir;

	consecutive_redir = 0;
	if (inst[i] == '<')
		consecutive_redir = count_consecutive_redir(inst, '<', i);
	else if (inst[i] == '>')
		consecutive_redir = count_consecutive_redir(inst, '>', i);
	if (consecutive_redir != 4 && c == '<')
		return (false);
	if (consecutive_redir != 3 && c == '>')
		return (false);
	return (false);
}

bool	find_double_redir_in_case(char *inst, int i, char c)
{
	int	consecutive_redir;

	consecutive_redir = 0;
	if (inst[i] == '<')
		consecutive_redir = count_consecutive_redir(inst, '<', i);
	else if (inst[i] == '>')
		consecutive_redir = count_consecutive_redir(inst, '>', i);
	if (consecutive_redir != 5 && c == '<')
		return (false);
	if (consecutive_redir < 4 && c == '>')
		return (false);
	return (false);
}

bool	find_triple_redir_in_case(char *inst, int i, char c)
{
	int	consecutive_redir;

	if (c == '>')
		return (false);
	consecutive_redir = 0;
	if (inst[i] == '<')
		consecutive_redir = count_consecutive_redir(inst, '<', i);
	if (consecutive_redir < 6 && c == '<')
		return (false);
	return (false);
}

int	check_redir_system(char *inst, t_shell_data *shell)
{
	int	i;
	int	error_case;

	i = 0;
	error_case = 0;
	while (inst[i])
	{
		if (inst[i] == '<')
		{
			error_case = find_error_case_syntax(inst, i, '<', shell);
			if (error_case == true)
				return (1);
		}
		else if (inst[i] == '>')
		{
			error_case = find_error_case_syntax(inst, i, '>', shell);
			if (error_case == true)
				return (1);
		}
		while (inst[i] && (inst[i] == '<' || inst[i] == '>'))
			i++;
		i++;
	}
	return (0);
}
