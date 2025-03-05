/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:07:59 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/26 17:00:39 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static void	write_in_file_history(int *fd, char *last_entry, char *line)
{
	if (check_historic_lines() >= 2000)
		rewrite_history();
	if (ft_strncmp(line, last_entry, ft_strlen(last_entry)) != 0)
	{
		write(*fd, "\n", 1);
		write(*fd, line, ft_strlen(line));
	}
	close(*fd);
}

int	add_to_history(char *line, t_shell_data *shell)
{
	int		fd;
	char	*last_entry;
	char	*path;
	int		pid;

	last_entry = NULL;
	path = NULL;
	pid = fork();
	if (pid == 0)
	{
		path = get_history_path();
		fd = open(path, O_CREAT | O_RDWR | O_APPEND, 0666);
		last_entry = get_last_line();
		if (fd < 0)
			return (free_variable((void **)&last_entry),
				free_variable((void **)&*path), -1);
		write_in_file_history(&fd, last_entry, line);
		free_variable((void **)&last_entry);
		free_variable((void **)&path);
		free_malloc_exit_system(&shell);
		exit(0);
	}
	else
		waitpid(pid, NULL, 0);
	return (0);
}
