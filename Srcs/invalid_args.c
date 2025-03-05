/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 08:12:58 by ls                #+#    #+#             */
/*   Updated: 2024/06/27 12:42:28 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	init_find(t_find_error_case_syntax *find)
{
	find->position = 0;
	find->alpha = false;
	find->number_special = 0;
	find->count_consecutive = 0;
	find->opposite_redir = 0;
	find->count_consecutive_after_redir = 0;
	find->j = 0;
	find->count_consecutive_after = 0;
}

void	find_opposite_redir_consecutive(char *inst, int i, char c,
		t_find_error_case_syntax *find)
{
	if (c == '<')
	{
		find->opposite_redir = '>';
	}
	else
		find->opposite_redir = '<';
	find->count_consecutive_after_redir = count_consecutive_redir(inst,
			find->opposite_redir, i + find->count_consecutive);
}

int	redirection_errors(t_shell_data *shell, char **inst)
{
	if (check_pipe_system((*inst), shell) == 1)
		return (1);
	if (check_redir_system((*inst), shell) == 1)
		return (1);
	if (check_and_system(inst, shell, VERBOSE) == true)
		return (1);
	if (check_parenth_system((*inst), shell) == true)
		return (1);
	return (0);
}

static bool	check_access_files(char *inst, t_shell_data *shell)
{
	if (access(inst, F_OK) == 0 && access(inst, X_OK) == -1)
	{
		shell->exit_status = 126;
		print_error(inst, ": Permission denied\n", shell);
		return (1);
	}
	else if (access(inst, F_OK) == -1)
	{
		print_error(inst, ": No such file or directory\n", shell);
		shell->exit_status = 127;
		return (1);
	}
	return (0);
}

int	directory_errors(t_shell_data *shell, char *inst)
{
	if (ft_strlen(inst) == 1)
	{
		if (inst[0] == '/')
		{
			printf("minishell : %s : Is a directory\n", inst);
			shell->exit_status = 126;
			return (1);
		}
	}
	else if (is_single_char_in_string(inst, "./"))
	{
		printf("minishell : %s : Is a directory\n", inst);
		shell->exit_status = 126;
		return (1);
	}
	else if (ft_strncmp(inst, "./", 2) == 0)
	{
		if (check_access_files(inst, shell))
			return (1);
	}
	return (0);
}
