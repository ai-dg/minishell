/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scripts_count_lines.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:52:29 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/26 17:01:31 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

bool	has_binary_data(char *buff, int reads)
{
	int	i;

	i = 0;
	while (i < reads)
	{
		if ((buff[i] < 9 || buff[i] > 13) && (buff[i] < 32 || buff[i] > 126)
			&& buff[i] != '\0')
			return (true);
		i++;
	}
	return (false);
}

void	reset_buffer_alt(char *buffer, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		buffer[i] = '\0';
		i++;
	}
}

bool	is_binary_file(char *path)
{
	int		reads;
	int		fd;
	char	buff[1024];

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (false);
	reads = read(fd, buff, sizeof(buff));
	while ((reads) > 0)
	{
		if (has_binary_data(buff, reads))
		{
			close(fd);
			return (true);
		}
		reset_buffer_alt(buff, reads);
		reads = read(fd, buff, sizeof(buff));
	}
	close(fd);
	return (false);
}

bool	if_some_thing_to_execute(t_cmd *pipes)
{
	while (pipes)
	{
		if (found_cmd(pipes->tokens, VARIABLE))
			return (true);
		pipes = pipes->next;
	}
	return (false);
}

int	count_lines(char *path, t_shell_data *shell)
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
