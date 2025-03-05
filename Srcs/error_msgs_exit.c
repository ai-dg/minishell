/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msgs_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 11:50:26 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/26 17:00:18 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	exit_errno(char *av, t_shell_data **shell)
{
	ft_fprintf(stderr, "minishell: %s: %s\n", av, strerror(errno));
	free_malloc_exit_system(shell);
	exit(errno);
}

void	exit_is_a_directory(char *av, t_shell_data **shell)
{
	ft_fprintf(stderr, "minishell: %s: Is a directory\n", av);
	free_malloc_exit_system(shell);
	exit(126);
}

void	exit_permission_denied(char *av, t_shell_data **shell)
{
	ft_fprintf(stderr, "minishell: %s: Permission denied\n", av);
	free_malloc_exit_system(shell);
	exit(126);
}

void	exit_binary_file(char *av, t_shell_data **shell)
{
	ft_fprintf(stderr, "%s: %s: cannot execute binary file\n", av, av);
	free_malloc_exit_system(shell);
	exit(126);
}

void	exit_invalid_file(char *av, t_shell_data **shell)
{
	ft_fprintf(stderr, "%s: %s: Is not a valid file\n", av, av);
	free_malloc_exit_system(shell);
	exit(126);
}
