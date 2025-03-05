/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:13:16 by dagudelo          #+#    #+#             */
/*   Updated: 2024/06/26 17:00:30 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static void	directory_error(t_shell_data *shell, char **cmd_args, int *i)
{
	if (shell->in_script == true && shell->in_parentheses == false)
		line_directory_error(shell, cmd_args, i);
	else
	{
		print_error(cmd_args[0], ": No such file or directory\n", shell);
		exit_127(&shell);
	}
}

static void	cmd_no_existing_error(t_shell_data *shell, char **cmd_args,
		char *path)
{
	path = search_path(shell, cmd_args);
	if (path == NULL)
	{
		if (ft_strstr(cmd_args[0], "/") != NULL)
			print_error(cmd_args[0], ": No such file or directory\n", shell);
		else
			print_error(cmd_args[0], ": command not found\n", shell);
		exit_127(&shell);
	}
	print_error(cmd_args[0], ": command not found\n", shell);
	exit_127(&shell);
}

static void	print_messages_error(char **cmd_args, t_shell_data *shell)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	if (ft_strchr(cmd_args[0], '/') != NULL && access(cmd_args[0], F_OK) == -1
		&& shell->first_message != 1)
		directory_error(shell, cmd_args, &i);
	else if (ft_strchr(cmd_args[0], '/') == NULL && access(cmd_args[0], F_OK)
		== -1 && shell->first_message != 1)
	{
		if (shell->in_script == true && shell->in_parentheses == false)
			line_error_command_not_found(shell, cmd_args, &i);
		else
			cmd_no_existing_error(shell, cmd_args, path);
		shell->exit_status = 127;
	}
}

static void	final_check_error(t_shell_data *shell, char **cmd_args)
{
	if ((shell->i - 1) >= 0 && shell->pid == shell->pid_list[shell->i - 1])
		exit_0(&shell);
	else
	{
		if (ft_strstr(cmd_args[0], "/") != NULL)
		{
			print_error(cmd_args[0], ": Permission denied\n", shell);
			exit_126(&shell);
		}
		else
			print_error(cmd_args[0], ": command not found\n", shell);
		exit_127(&shell);
	}
}

void	execute_cmd(t_cmd *pipe, t_shell_data *shell)
{
	char	**cmd_args;
	char	*path_final;

	path_final = NULL;
	if (pipe->in_parentheses == true)
		execute_in_parentheses(pipe, shell);
	if (ft_strcmp(pipe->cmd, ".\0") == 0)
	{
		print_error(pipe->cmd, ": filename argument required\n", shell);
		print_error(pipe->cmd, ": usage: . filename [arguments]\n", shell);
		free_malloc_exit_system(&shell);
		exit(2);
	}
	if (pipe->cmd != NULL && ft_strncmp(pipe->cmd, "", 1) != 0)
	{
		cmd_args = pipe->args;
		check_cmd_args(cmd_args, shell);
		check_cmd_access_final_path(cmd_args, path_final, shell);
		print_messages_error(cmd_args, shell);
		shell->first_message = 0;
		if (path_final != NULL)
			free_variable((void **)&path_final);
		final_check_error(shell, cmd_args);
	}
	exit_0(&shell);
}
