/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:31:31 by dagudelo          #+#    #+#             */
/*   Updated: 2024/06/14 19:02:05 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	pipex(t_cmd *pipe, t_shell_data *shell)
{
	shell->exit_status1 = 0;
	shell->exit_status2 = 0;
	create_pid_process(pipe, shell);
	if (shell->exit_status > 0)
		return (shell->exit_status);
	if (shell->exit_status1 != 0)
		return (shell->exit_status1);
	if (shell->exit_status2 != 0)
		return (shell->exit_status2);
	return (0);
}
