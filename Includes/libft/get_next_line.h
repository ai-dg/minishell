/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 06:15:23 by calbor-p          #+#    #+#             */
/*   Updated: 2024/05/27 19:25:06 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# ifndef FD_MAX
#  define FD_MAX 4096
# endif

# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_buffer
{
	char	buf[FD_MAX][BUFFER_SIZE + 1];
	int		read[FD_MAX];
}			t_buffer;

char		*get_next_line(int fd);
int			line_break_position(char const *text);
void		*reset_buffer(char buf[BUFFER_SIZE]);
int			bufferlength(char *buf);
void		handle_buf(char *buf, size_t start, size_t length);

#endif
