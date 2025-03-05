/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scripts_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:52:29 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/27 12:46:05 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static bool	condition_to_skip_line(char *line)
{
	return (!line || ft_strlen(line) == 0 || line[0] == '#' || line[0] == '\n'
		|| line[0] == '\0' || ft_strstr(line, "./") != NULL);
}

static void	execute_minishell_script(t_shell_data **shell,
		t_shell_data *old_shell)
{
	free_loop_malloc_system(shell);
	free_exec_unit(&(*shell)->exec_units);
	free_variable((void **)&(*shell)->line);
	(*shell)->line = ft_strdup((*shell)->lines_char[(*shell)->number_line]);
	old_shell = (*shell);
	shell_prompt((*shell));
	if (old_shell)
	{
		if (old_shell != (*shell))
			free_malloc_exit_system(&old_shell);
	}
	if ((*shell)->exec_units)
		free_exec_unit(&(*shell)->exec_units);
	(*shell)->exec_units = NULL;
	free_variable((void **)&(*shell)->line);
	free_loop_malloc_system(shell);
}

static void	read_lines_and_execute(t_shell_data **shell,
	t_shell_data *old_shell, int *total_lines)
{
	while ((*shell)->number_line < *total_lines)
	{
		if (condition_to_skip_line((*shell)->lines_char[(*shell)->number_line]))
		{
			(*shell)->number_line++;
			free_variable((void **)&(*shell)->line);
			continue ;
		}
		execute_minishell_script(shell, old_shell);
		(*shell)->number_line++;
	}
}

static void	close_and_free_all_after_script(t_shell_data **shell, int *fd,
		int *status)
{
	(*shell)->in_script = false;
	close(*fd);
	*status = (*shell)->exit_status;
	free_variable((void **)&(*shell)->file_script);
	free_malloc_exit_system(shell);
}

int	execute_file_as_script(char *path, t_shell_data *shell)
{
	int				fd;
	int				total_lines;
	t_shell_data	*old_shell;
	int				status;

	old_shell = NULL;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ft_fprintf(stderr, "minishell: %s: %s\n", path,
				strerror(errno)), 0);
	initialize_variables_for_script(&total_lines, shell, path);
	read_lines_and_execute(&shell, old_shell, &total_lines);
	close_and_free_all_after_script(&shell, &fd, &status);
	return (status);
}
