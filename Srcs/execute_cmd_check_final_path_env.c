/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_check_final_path_env.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls <ls@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:13:16 by dagudelo          #+#    #+#             */
/*   Updated: 2024/06/21 07:30:32 by ls               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	env_case(char **cmd_args, t_shell_data *shell)
{
	if (!ft_getenv("PATH", shell))
	{
		shell->in_path_null = true;
		if (access(cmd_args[0], X_OK) == 0)
		{
			if (execve(cmd_args[0], cmd_args, shell->env_char) == -1)
				error_execve_check(cmd_args, shell);
		}
		else if (ft_strncmp(cmd_args[0], "/", 1) == 0)
		{
			if (execve(cmd_args[0], cmd_args, shell->env_char) == -1)
				error_execve_check(cmd_args, shell);
		}
		else
		{
			if (execve(cmd_args[0], cmd_args, shell->env_char) == -1)
				error_execve_check(cmd_args, shell);
		}
	}
}

void	access_test(char **cmd_args, t_shell_data *shell)
{
	if (execve(cmd_args[0], cmd_args, shell->env_char) == -1)
		error_execve_check(cmd_args, shell);
}

void	env_i_case(char **cmd_args, t_shell_data *shell)
{
	char	*old_char;

	if (shell->sys_env[0] == NULL && ft_strcmp(ft_getenv("_", shell),
			"/usr/bin/env") == 0)
	{
		if (access(cmd_args[0], X_OK) == 0)
			access_test(cmd_args, shell);
		else if (ft_strncmp(cmd_args[0], "/", 1) == 0)
		{
			if (execve(cmd_args[0], cmd_args, shell->env_char) == -1)
				error_execve_check(cmd_args, shell);
		}
		else
		{
			old_char = ft_strdup(cmd_args[0]);
			cmd_args[0] = ft_fstrjoin("/usr/bin/", cmd_args[0], NONE);
			if (execve(cmd_args[0], cmd_args, shell->env_char) == -1)
			{
				cmd_args[0] = ft_strdup(old_char);
				free_variable((void **)&old_char);
				error_execve_check(cmd_args, shell);
			}
		}
	}
}
