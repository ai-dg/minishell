/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc_readline_write.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:23:43 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/26 14:52:00 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	write_line_to_pipe(int pipefd[2], const char *line,
		const char *delimiter, t_shell_data *shell)
{
	char	*end;

	(void)*shell;
	end = ft_strstr((char *)line, (char *)delimiter);
	if (end)
	{
		write(pipefd[1], line, end - line);
	}
	else
	{
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
	}
}
