/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_write.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:46:34 by dagudelo          #+#    #+#             */
/*   Updated: 2024/06/30 17:16:20 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	check_pipe_content(t_pipefd *pipefd)
{
	char	read_buffer[4096];
	ssize_t	bytes_read_pipe;

	bytes_read_pipe = read(pipefd->values[0], read_buffer, sizeof(read_buffer));
	if (bytes_read_pipe == -1)
	{
		perror("read from pipe");
		return ;
	}
}

static void	handle_pipe_io(int input, t_pipefd *current_pipefd)
{
	char	buffer[4096];
	ssize_t	bytes_read;

	bytes_read = read(input, buffer, sizeof(buffer));
	while ((bytes_read) > 0)
	{
		if (write(current_pipefd->values[1], buffer, bytes_read) == -1)
		{
			perror("write");
			break ;
		}
		bytes_read = read(input, buffer, sizeof(buffer));
	}
	if (bytes_read == -1)
	{
		perror("read");
	}
}

static void	write_input_to_pipe(t_cmd *current_pipe, t_pipefd *current_pipefd,
		t_shell_data *shell)
{
	int	input;

	input = open_fd_input(current_pipe, shell, 1);
	if (input < 0)
	{
		return ;
	}
	handle_pipe_io(input, current_pipefd);
	close(input);
}

void	write_input_to_pipes(t_cmd *current_pipe, t_pipefd *current_pipefd,
		t_shell_data *shell)
{
	while (current_pipe != NULL && current_pipefd != NULL)
	{
		write_input_to_pipe(current_pipe, current_pipefd, shell);
		current_pipe = current_pipe->next;
		current_pipefd = current_pipefd->next;
	}
}
