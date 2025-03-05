/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fflush.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls <ls@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 07:34:31 by ls                #+#    #+#             */
/*   Updated: 2024/06/14 07:39:12 by ls               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_fflush(FILE *stream)
{
	int		fd;
	char	*buffer;
	size_t	buffer_size;
	ssize_t	written;

	if (stream == NULL)
		return (EOF);
	if (stream != stdout && stream != stderr)
		return (0);
	fd = ft_fileno(stream);
	if (fd == -1)
		return (EOF);
	buffer = stream->_IO_write_base;
	buffer_size = stream->_IO_write_ptr - buffer;
	if (buffer_size > 0)
	{
		written = write(fd, buffer, buffer_size);
		if (written != (ssize_t)buffer_size)
			return (EOF);
	}
	stream->_IO_write_ptr = stream->_IO_write_base;
	return (0);
}
