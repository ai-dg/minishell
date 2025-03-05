/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls <ls@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 06:15:48 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/21 10:03:03 by ls               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	line_break_position(char const *text)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (text[i] != '\0')
		i++;
	while (text[j] && text[j] != '\n')
		j++;
	if ((i == j && i != 0) || (i == 0 && text[i] != '\n' && text[i] != '\0'))
		return (-1);
	if (text[0] == '\0')
		return (-2);
	if (i == 0)
		return (0);
	return (j);
}

char	*get_line(char *buf)
{
	char	*line;
	int		offset;
	int		buflen;

	buflen = ft_strlen(buf);
	offset = 0;
	line = NULL;
	if (line_break_position(buf) > -1)
		offset = line_break_position(buf);
	line = ft_substr(buf, 0, (size_t)offset + 1);
	if (line_break_position(buf) == bufferlength(buf) - 1)
		reset_buffer(buf);
	else
		handle_buf(buf, offset + 1, bufferlength(buf) - (size_t)offset - 1);
	if (!buflen)
		line[0] = '\0';
	return (line);
}

char	*get_left(char *line, char *buf)
{
	int	i;

	i = 0;
	if (!line)
		line = malloc(ft_strlen(buf) + 1);
	if (!line)
		return (NULL);
	while (buf[i])
	{
		line[i] = buf[i];
		i++;
	}
	line[i] = '\0';
	i = 0;
	return (line);
}

char	*get_tmp_line(char *tmp, char *buf, bool is_alloc)
{
	char	*new;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!tmp || !buf)
		return (NULL);
	new = malloc(ft_strlen(tmp) + bufferlength(buf) + 1);
	if (!new)
	{
		if (is_alloc)
			free(buf);
		free(tmp);
		return (NULL);
	}
	while (tmp[++i])
		new[i] = tmp[i];
	while (buf[++j])
		new[i++] = buf[j];
	if (is_alloc)
		free(buf);
	free(tmp);
	new[i] = '\0';
	return (new);
}

char	*get_next_line(int fd)
{
	char			*tmp;
	static t_buffer	bufs = {.read = {-2}};

	tmp = NULL;
	if (bufs.read[fd] == -2 || !bufferlength(bufs.buf[fd]))
		bufs.read[fd] = read(fd, bufs.buf[fd], BUFFER_SIZE);
	if (bufs.read[fd] <= 0 || fd < 0)
		return (NULL);
	if (line_break_position(bufs.buf[fd]) == -1 && bufs.read[fd] != 0)
	{
		tmp = get_left(tmp, bufs.buf[fd]);
		while (line_break_position(bufs.buf[fd]) == -1 && bufs.read[fd] != 0)
		{
			bufs.read[fd] = read(fd, reset_buffer(bufs.buf[fd]), BUFFER_SIZE);
			if (line_break_position(bufs.buf[fd]) == -1 && bufs.read[fd] != 0)
				tmp = get_tmp_line(tmp, bufs.buf[fd], false);
		}
		if (line_break_position(bufs.buf[fd]) > -1 || bufs.read[fd] == 0)
			return (get_tmp_line(tmp, get_line(bufs.buf[fd]), true));
	}
	if (bufferlength(bufs.buf[fd]) && bufs.read[fd] != 0)
		return (get_line(bufs.buf[fd]));
	return (NULL);
}
