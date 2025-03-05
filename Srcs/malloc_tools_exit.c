/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_tools_exit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:13:24 by dagudelo          #+#    #+#             */
/*   Updated: 2024/06/26 17:00:49 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	exit_127(t_shell_data **shell)
{
	free_malloc_exit_system(shell);
	exit(127);
}

void	exit_0(t_shell_data **shell)
{
	free_malloc_exit_system(shell);
	exit(0);
}

void	exit_126(t_shell_data **shell)
{
	free_malloc_exit_system(shell);
	exit(126);
}

void	exit_1(t_shell_data **shell)
{
	free_malloc_exit_system(shell);
	exit(1);
}

void	exit_1_malloc(t_shell_data **shell)
{
	perror("malloc failed");
	free_malloc_exit_system(shell);
	exit(1);
}
