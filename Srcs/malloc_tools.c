/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:13:24 by dagudelo          #+#    #+#             */
/*   Updated: 2024/07/01 12:09:07 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	free_exec_unit(t_exec_unit **unit)
{
	if (*unit == NULL)
		return ;
	if ((*unit)->l_unit)
	{
		free_exec_unit(&(*unit)->l_unit);
	}
	if ((*unit)->r_unit)
	{
		free_exec_unit(&(*unit)->r_unit);
	}
	if ((*unit)->prompt)
	{
		free_variable((void **)&(*unit)->prompt);
		(*unit)->prompt = NULL;
	}
	free_variable((void **)&(*unit));
	*unit = NULL;
}

void	put_to_zero_all(void **ptr, ...)
{
	va_list	args;
	void	*tmp;

	va_start(args, ptr);
	while (ptr)
	{
		tmp = va_arg(args, void *);
		ft_bzero(*ptr, sizeof(tmp));
		ptr = va_arg(args, void *);
	}
	va_end(args);
}

void	free_loop_malloc_system(t_shell_data **shell)
{
	free_cmd_pipe((*shell));
	free_variable((void **)&(*shell)->pid_list);
	free_array(&(*shell)->parsed);
	free_array(&(*shell)->initial_parsed);
	free_array(&(*shell)->paths);
	free_variable((void **)&(*shell)->prompt);
	free_variable((void **)&(*shell)->pline);
	free_variable((void **)&(*shell)->prompt_in);
	free_variable((void **)&(*shell)->prompt_cmd);
	free_variable((void **)&(*shell)->line);
	free_variable((void **)&(*shell)->home);
	free_variable((void **)&(*shell)->tmp_history);
	free_t_fds(&(*shell)->fds);
	free_t_pipefd(&(*shell)->pipefd1);
	free_variable((void **)&(*shell)->to_expand_in_doc);
}

void	free_malloc_exit_system(t_shell_data **shell)
{
	free_cmd_pipe((*shell));
	free_variable((void **)&(*shell)->pid_list);
	free_t_env(&(*shell)->alias);
	free_t_env(&(*shell)->env);
	free_t_env(&(*shell)->session);
	free_array(&(*shell)->parsed);
	free_array(&(*shell)->initial_parsed);
	free_array(&(*shell)->paths);
	free_array(&(*shell)->env_char);
	free_variable((void **)&(*shell)->prompt);
	free_variable((void **)&(*shell)->pline);
	free_variable((void **)&(*shell)->prompt_in);
	free_variable((void **)&(*shell)->prompt_cmd);
	free_variable((void **)&(*shell)->line);
	free_variable((void **)&(*shell)->file_script);
	free_variable((void **)&(*shell)->home);
	free_variable((void **)&(*shell)->tmp_history);
	close_all_pipefd((*shell));
	close_all_fds((*shell));
	free_t_fds(&(*shell)->fds);
	free_t_pipefd(&(*shell)->pipefd1);
	free_array(&(*shell)->lines_char);
	free_exec_unit(&(*shell)->exec_units);
	free_variable((void **)&(*shell)->to_expand_in_doc);
	free_variable((void **)&(*shell));
}

void	free_malloc_exit_system_ctrl_d(t_shell_data **shell)
{
	free_cmd_pipe((*shell));
	free_variable((void **)&(*shell)->pid_list);
	free_t_env(&(*shell)->alias);
	free_t_env(&(*shell)->env);
	free_t_env(&(*shell)->session);
	free_array(&(*shell)->parsed);
	free_array(&(*shell)->initial_parsed);
	free_array(&(*shell)->paths);
	free_array(&(*shell)->env_char);
	free_variable((void **)&(*shell)->prompt);
	free_variable((void **)&(*shell)->pline);
	free_variable((void **)&(*shell)->prompt_in);
	free_variable((void **)&(*shell)->prompt_cmd);
	free_variable((void **)&(*shell)->line);
	free_variable((void **)&(*shell)->file_script);
	free_variable((void **)&(*shell)->home);
	free_variable((void **)&(*shell)->tmp_history);
	close_all_pipefd((*shell));
	close_all_fds((*shell));
	free_t_fds(&(*shell)->fds);
	free_t_pipefd(&(*shell)->pipefd1);
	free_exec_unit(&(*shell)->exec_units);
	free_array(&(*shell)->lines_char);
	free_variable((void **)&(*shell)->to_expand_in_doc);
}
