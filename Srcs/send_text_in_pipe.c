/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_text_in_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 00:21:49 by ls                #+#    #+#             */
/*   Updated: 2024/06/13 12:57:14 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static void	write_into_pipes(t_shell_data *shell, int *pipefd, int *pipefd_tmp,
		char *line)
{
	if (shell->in_exe_cmd == true)
	{
		write(pipefd[1], line, ft_strlen(line));
		close(pipefd[1]);
	}
	else
	{
		write(pipefd_tmp[1], line, ft_strlen(line));
		close(pipefd_tmp[1]);
		close(pipefd_tmp[0]);
	}
}

char	*send_text_through_pipe(int *pipefd, char *line, t_cmd *pipes,
		t_shell_data *shell)
{
	int	input;
	int	pipefd_tmp[2];

	(void)pipes;
	(void)input;
	input = 0;
	if (shell->in_exe_cmd == true)
		input = pipefd[1];
	else
	{
		if (pipe(pipefd_tmp) == -1)
		{
			perror("pipe");
			close_pipes_and_files(shell);
		}
		input = pipefd_tmp[1];
	}
	write_into_pipes(shell, pipefd, pipefd_tmp, line);
	return (line);
}
