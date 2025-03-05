/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:46:34 by dagudelo          #+#    #+#             */
/*   Updated: 2024/06/26 17:01:24 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static void	init_values(t_print_error_values *values, const char *var,
		const char *msg, t_shell_data *shell)
{
	values->prefix = "minishell: ";
	values->prefix_len = ft_strlen(values->prefix);
	values->var_len = ft_strlen(var);
	values->msg_len = ft_strlen(msg);
	values->total_len = values->prefix_len + values->var_len + values->msg_len;
	values->error_msg = (char *)malloc(sizeof(char) * (values->total_len + 1));
	if (!values->error_msg)
		exit_1_malloc(&shell);
}

void	print_error(const char *var, const char *msg, t_shell_data *shell)
{
	t_print_error_values	values;

	init_values(&values, var, msg, shell);
	ft_memcpy(values.error_msg, values.prefix, values.prefix_len);
	ft_memcpy(values.error_msg + values.prefix_len, var, values.var_len);
	ft_memcpy(values.error_msg + values.prefix_len + values.var_len, msg,
		values.msg_len);
	values.error_msg[values.total_len] = '\0';
	write(STDERR_FILENO, values.error_msg, values.total_len);
	free_variable((void **)&values.error_msg);
}

bool	can_execute(const char *filepath)
{
	return (access(filepath, X_OK) == 0);
}

void	error_execve_check(char **cmd_args, t_shell_data *shell)
{
	if (shell->in_path_null == true)
	{
		shell->in_path_null = false;
		print_error(cmd_args[0], ": No such file or directory\n", shell);
		exit_127(&shell);
	}
	if (ft_strstr(cmd_args[0], "home") != NULL || (ft_strstr(cmd_args[0],
				"/") != NULL))
	{
		print_error(cmd_args[0], ": Is a directory\n", shell);
		exit_126(&shell);
	}
	if (shell->in_script == true)
		ft_fprintf(stderr, "%s: line %d: %s: command not found\n",
			shell->file_script, shell->number_line + 1, shell->pipe->cmd);
	else
		print_error(cmd_args[0], ": command not found\n", shell);
	if (errno == EACCES)
		exit_127(&shell);
	else
		exit_127(&shell);
	free_malloc_exit_system(&shell);
	exit(127);
}

void	remove_line_break(t_cmd *pipe, t_pipefd *pipefd1, t_shell_data *shell)
{
	t_cmd		*current_pipe;
	t_pipefd	*current_pipefd1;

	current_pipe = pipe;
	current_pipefd1 = pipefd1;
	while (current_pipe != NULL)
	{
		if (current_pipe->cmd)
		{
			if (ft_strncmp(current_pipe->cmd, "echo", 4) == 0
				&& current_pipe->next != NULL)
			{
				if (current_pipefd1->next)
					shell->echo_in_pipe = true;
			}
		}
		current_pipe = current_pipe->next;
		current_pipefd1 = current_pipefd1->next;
	}
}
