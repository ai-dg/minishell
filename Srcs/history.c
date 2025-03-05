/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:07:59 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/14 20:57:57 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	check_historic_lines(void)
{
	int		historic_lines;
	char	*line;
	int		fd;
	char	*path;

	path = get_history_path();
	historic_lines = 0;
	fd = open(path, O_CREAT | O_RDONLY, 0666);
	if (fd < 0)
		return (free_variable((void **)&path), -1);
	line = get_next_line(fd);
	while (line)
	{
		if (line)
			historic_lines++;
		free_variable((void **)&line);
		line = get_next_line(fd);
	}
	close(fd);
	return (free_variable((void **)&path), historic_lines);
}

char	*get_last_line(void)
{
	int		fd;
	char	*path;
	char	*last;
	char	*beforelast;

	path = get_history_path();
	fd = open(path, O_CREAT | O_RDONLY, 0666);
	if (fd < 0)
		return (free_variable((void **)&path), NULL);
	beforelast = get_next_line(fd);
	last = get_next_line(fd);
	while (last)
	{
		free_variable((void **)&beforelast);
		beforelast = last;
		last = get_next_line(fd);
	}
	close(fd);
	if (!beforelast)
		beforelast = ft_strdup("void");
	free_variable((void **)&path);
	return (beforelast);
}

void	init_history(t_shell_data *shell)
{
	if (check_historic_lines() > 2000)
		rewrite_history();
	load_historic(shell);
}
