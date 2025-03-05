/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scripts_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 08:37:45 by ls                #+#    #+#             */
/*   Updated: 2024/06/26 17:01:48 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static void	open_fd_double_string(int *fd, char **lines_char, char *path,
		t_shell_data *shell)
{
	*fd = open(path, O_RDONLY);
	if (*fd < 0)
	{
		free_array(&lines_char);
		ft_printf("minishell: %s: %s\n", path, strerror(errno));
		free_malloc_exit_system(&shell);
		exit(errno);
	}
}

void	init_to_null(char **array, int length)
{
	int	i;

	i = 0;
	while (i < length)
	{
		array[i] = NULL;
		i++;
	}
}

char	**line_to_double_string(char *path, int total_lines,
		t_shell_data *shell)
{
	int		fd;
	char	*line;
	int		line_number;
	char	**lines_char;

	lines_char = NULL;
	lines_char = (char **)malloc(sizeof(char *) * (total_lines + 1));
	if (!lines_char)
		exit_1_malloc(&shell);
	init_to_null(lines_char, total_lines + 1);
	open_fd_double_string(&fd, lines_char, path, shell);
	line_number = 0;
	line = get_next_line(fd);
	while (line && line_number < total_lines)
	{
		if (lines_char[line_number])
			free_variable((void **)lines_char[line_number]);
		lines_char[line_number] = ft_strdup(line);
		free_variable((void **)&line);
		line = get_next_line(fd);
		line_number++;
	}
	lines_char[line_number] = NULL;
	close(fd);
	return (lines_char);
}

void	initialize_variables_for_script(int *total_lines, t_shell_data *shell,
		char *path)
{
	shell->in_script = true;
	*total_lines = count_lines(path, shell);
	if (shell->lines_char)
		free_array(&shell->lines_char);
	shell->lines_char = NULL;
	shell->lines_char = line_to_double_string(path, *total_lines, shell);
	shell->number_line = 0;
	if (shell->file_script)
		free_variable((void **)&shell->file_script);
	shell->file_script = ft_strdup(path);
}

void	argv_execution(char *av, t_shell_data *shell)
{
	struct stat	file_info;
	int			status;

	errno = 0;
	if (stat(av, &file_info) == -1)
		exit_errno(av, &shell);
	if (S_ISDIR(file_info.st_mode))
		exit_is_a_directory(av, &shell);
	if (S_ISREG(file_info.st_mode))
	{
		if (access(av, R_OK) == -1)
			exit_permission_denied(av, &shell);
		if (is_binary_file(av))
			exit_binary_file(av, &shell);
		status = 0;
		status = execute_file_as_script(av, shell);
		exit(status);
	}
	else
		exit_invalid_file(av, &shell);
}
