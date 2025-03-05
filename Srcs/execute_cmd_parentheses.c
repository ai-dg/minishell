/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_parentheses.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:13:16 by dagudelo          #+#    #+#             */
/*   Updated: 2024/06/24 16:40:34 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	execute_in_parentheses(t_cmd *pipe, t_shell_data *shell)
{
	int	fd;

	fd = open(".tmp", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
	{
		perror("open");
		exit_1(&shell);
	}
	write(fd, pipe->p_execute, ft_strlen(pipe->p_execute));
	shell->in_parentheses = true;
	argv_execution(".tmp", shell);
	exit_0(&shell);
}
