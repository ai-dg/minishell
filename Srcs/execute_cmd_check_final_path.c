/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_check_final_path.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:13:16 by dagudelo          #+#    #+#             */
/*   Updated: 2024/06/29 13:10:12 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static void	arg_execution_case(char **cmd_args, t_shell_data *shell)
{
	if (ft_strncmp(cmd_args[0], "./", 2) == 0 && shell->in_script == false)
	{
		errno = 0;
		if (is_binary_file(cmd_args[0]) == true)
		{
			if (execve(cmd_args[0], cmd_args, shell->env_char) == -1)
				error_execve_check(cmd_args, shell);
		}
		else if (ft_strncmp(cmd_args[0], "./", 2) == 0)
		{
			shell->in_env_cmd = false;
			ft_unallocated_trim_once(cmd_args[0], ' ');
			argv_execution(cmd_args[0], shell);
			exit_0(&shell);
		}
	}
	if (access(cmd_args[0], X_OK) == 0 && shell->in_env_cmd == false
		&& shell->in_script == false)
	{
		errno = 0;
		if (execve(cmd_args[0], cmd_args, shell->env_char) == -1)
			error_execve_check(cmd_args, shell);
	}
}

static void	buildtin_case_execution(t_shell_data *shell, char **cmd_args,
		int *index)
{
	static int	(*exe[])(t_shell_data *, char **) = {exit_m, clear_m, pwd_m,
		echo_m, cd_m, export_m, unset_m, env_m, 0, printenv_m, add_session};

	*index = get_index_buildin_cmd(cmd_args[0]);
	if (*index != -1)
		exe[*index](shell, cmd_args);
	if (shell->exit_status == 1)
		exit_1(&shell);
	else
		exit_0(&shell);
}

static void	final_path_case(t_shell_data *shell, char **cmd_args,
		char *path_final)
{
	path_final = search_path(shell, cmd_args);
	if (path_final == NULL)
	{
		if (ft_strncmp(cmd_args[0], "./", 2) == 0)
			argv_execution(cmd_args[0], shell);
		else
		{
			if (shell->dollar_expansion == true && ft_strncmp(cmd_args[0],
					"/home", 5) == 0)
				print_error(cmd_args[0], ": Is a directory\n", shell);
			else
				print_error(cmd_args[0], ": command not found\n", shell);
		}
	}
}

void	check_cmd_access_final_path(char **cmd_args, char *path_final,
		t_shell_data *shell)
{
	int	index;

	arg_execution_case(cmd_args, shell);
	env_i_case(cmd_args, shell);
	env_case(cmd_args, shell);
	if (is_cmd_buildin(cmd_args[0]) == true)
		buildtin_case_execution(shell, cmd_args, &index);
	else if (access(cmd_args[0], X_OK) == 0)
		final_path_case(shell, cmd_args, path_final);
	else
		path_final_execution(shell, path_final, cmd_args);
	if (shell->in_env_cmd == true)
	{
		shell->in_env_cmd_error = true;
		write(STDERR_FILENO, "env: ", 5);
		write(STDERR_FILENO, "\'", 1);
		write(STDERR_FILENO, cmd_args[0], ft_strlen(cmd_args[0]));
		write(STDERR_FILENO, "\'", 1);
		write(STDERR_FILENO, ": No such file or directory\n", 29);
		if (shell->in_child_process == true)
			exit_127(&shell);
	}
}
