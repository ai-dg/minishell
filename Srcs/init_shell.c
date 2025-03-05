/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 18:23:34 by calbor-p          #+#    #+#             */
/*   Updated: 2024/07/01 12:05:58 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

t_shell_data	*init_shell(void)
{
	t_shell_data	*shell;

	shell = malloc(sizeof(t_shell_data));
	if (!shell)
		exit_1_malloc(&shell);
	ft_bzero(shell, sizeof(t_shell_data));
	shell->fd_null[1] = -1;
	shell->fd_null[0] = -1;
	if (tcgetattr(STDIN_FILENO, &shell->old) == -1)
		return (free_variable((void **)&shell), NULL);
	if (tcgetattr(STDIN_FILENO, &shell->terminal) == -1)
		return (free_variable((void **)&shell), NULL);
	return (shell);
}
