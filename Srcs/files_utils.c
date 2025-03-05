/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:56:59 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/26 17:00:34 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	count_lines_in_files(char *path, t_shell_data *shell)
{
	int		fd;
	char	*line;
	int		line_number;

	line_number = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("minishell: %s: %s\n", path, strerror(errno));
		free_malloc_exit_system(&shell);
		exit(errno);
	}
	line = get_next_line(fd);
	while (line)
	{
		line_number++;
		free_variable((void **)&line);
		line = get_next_line(fd);
	}
	close(fd);
	return (line_number);
}
