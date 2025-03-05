/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_load_get.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:07:59 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/18 15:22:07 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

char	*get_history_path(void)
{
	char	*path;

	path = ft_fstrjoin(get_home_path(), "/.minishell_history", FIRST);
	return (path);
}

int	load_historic(t_shell_data *shell)
{
	char	*line;
	char	*clean;
	int		fd;
	char	*path;

	(void)shell;
	path = get_history_path();
	fd = open(path, O_CREAT | O_CREAT, 0666);
	if (!fd)
		return (free_variable((void **)&path), -1);
	line = get_next_line(fd);
	while (line)
	{
		clean = ft_strtrim(line, "\n");
		clean = encode_char(clean, 7, '\n');
		if (clean)
		{
			add_history(clean);
			free_variable((void **)&clean);
		}
		free_variable((void **)&line);
		line = get_next_line(fd);
	}
	return (close(fd), free_variable((void **)&path), 0);
}

static void	fill_history(char **line, char **history, int *fd)
{
	char	*new_history;
	int		i;
	int		nbr_lines;
	int		to_copy;

	new_history = NULL;
	i = 0;
	nbr_lines = check_historic_lines();
	if (nbr_lines > 2000)
		to_copy = nbr_lines - 2000;
	else
		to_copy = 0;
	*line = get_next_line(*fd);
	while (*line != NULL)
	{
		if (i >= to_copy)
		{
			new_history = ft_fstrjoin(*history, *line, NONE);
			free_variable((void **)&*history);
			*history = new_history;
		}
		free_variable((void **)&*line);
		*line = get_next_line(*fd);
		i++;
	}
}

char	*get_all_history(void)
{
	int		fd;
	char	*history_path;
	char	*line;
	char	*history;

	history_path = get_history_path();
	history = NULL;
	fd = open(history_path, O_RDONLY);
	if (fd < 0)
	{
		free_variable((void **)&history_path);
		return (NULL);
	}
	fill_history(&line, &history, &fd);
	close(fd);
	free_variable((void **)&history_path);
	return (history);
}
