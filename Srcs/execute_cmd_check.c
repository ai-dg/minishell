/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:13:16 by dagudelo          #+#    #+#             */
/*   Updated: 2024/06/24 16:40:12 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	check_cmd_args(char **cmd_args, t_shell_data *shell)
{
	int	i;

	i = 0;
	if (cmd_args == NULL || cmd_args[0] == NULL)
	{
		print_error(cmd_args[i], ": command not found\n", shell);
		free_array(&cmd_args);
		if ((shell->i - 1) >= 0 && shell->pid == shell->pid_list[shell->i - 1])
			exit_0(&shell);
		else
			exit_127(&shell);
	}
}
