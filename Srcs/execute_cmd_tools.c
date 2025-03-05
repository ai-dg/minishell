/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:13:16 by dagudelo          #+#    #+#             */
/*   Updated: 2024/06/24 16:40:46 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	path_final_execution(t_shell_data *shell, char *path_final,
		char **cmd_args)
{
	shell->env_char = expand_env_to_char(shell->env, shell->env_char, shell);
	path_final = search_path(shell, cmd_args);
	if (path_final != NULL && access(path_final, X_OK) == 0)
	{
		if (execve(path_final, cmd_args, shell->env_char) == -1)
			error_execve_check(cmd_args, shell);
	}
}

bool	is_cmd_buildin(char *cmd)
{
	int					i;
	static const char	*cmds[] = {"exit", "clear", "pwd", "echo", "cd",
		"export", "unset", "env", "set", "printenv", "alias", "unalias",
		NULL};

	i = 0;
	if (cmd == NULL)
	{
		return (false);
	}
	while (cmds[i] != NULL)
	{
		if (ft_strcmp(cmd, (char *)cmds[i]) == 0)
		{
			return (true);
		}
		i++;
	}
	return (false);
}

int	get_index_buildin_cmd(char *inst)
{
	int					i;
	static const char	*keys[] = {"exit", "clear", "pwd", "echo", "cd",
		"export", "unset", "env", "set", "printenv", "alias", "unalias",
		NULL};

	i = 0;
	if (ft_found_char(inst, '='))
		return (10);
	while (keys[i])
	{
		if (ft_strncmp(keys[i], inst, ft_strlen(keys[i])) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	line_error_command_not_found(t_shell_data *shell, char **cmd_args,
		int *i)
{
	char	*line_number_str;

	line_number_str = ft_itoa(shell->number_line + 1);
	if (!line_number_str)
		exit_1_malloc(&shell);
	write(STDERR_FILENO, shell->file_script, ft_strlen(shell->file_script));
	write(STDERR_FILENO, ": line ", 7);
	write(STDERR_FILENO, line_number_str, ft_strlen(line_number_str));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, cmd_args[*i], ft_strlen(cmd_args[*i]));
	write(STDERR_FILENO, ": command not found\n", 20);
	free_variable((void **)&line_number_str);
	exit_127(&shell);
}

void	line_directory_error(t_shell_data *shell, char **cmd_args, int *i)
{
	char	*line_number_str;

	line_number_str = ft_itoa(shell->number_line + 1);
	if (!line_number_str)
		exit_1_malloc(&shell);
	write(STDERR_FILENO, shell->file_script, ft_strlen(shell->file_script));
	write(STDERR_FILENO, ": line ", 7);
	write(STDERR_FILENO, line_number_str, ft_strlen(line_number_str));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, cmd_args[*i], ft_strlen(cmd_args[*i]));
	write(STDERR_FILENO, ": No such file or directory\n", 29);
	free_variable((void **)&line_number_str);
	exit_127(&shell);
}
