/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_debug.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 22:11:14 by calbor-p          #+#    #+#             */
/*   Updated: 2024/07/01 11:26:25 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	check_start_mode(t_shell_data *shell)
{
	int	i;

	i = 0;
	while (shell->av[i])
	{
		if (ft_strncmp(shell->av[i], "--dev", ft_strlen(shell->av[i])) == 0
			|| ft_strncmp(shell->av[i], "-d", ft_strlen(shell->av[i])) == 0)
		{
			shell->debug_mode = DEV;
			printf("%sRUNNING IN DEV MODE ---- DEV DEBUG MESSAGES ON%s\n", RED,
				RESET);
		}
		i++;
	}
	return (0);
}

int	sandbox(t_shell_data *shell)
{
	if (shell->debug_mode == DEV)
	{
		mark("---------SANDBOX---------\n", shell);
		printf("pid : %d\n", ft_get_pid(shell));
		mark("-------SANDBOX END-------\n", shell);
	}
	return (0);
}

void	script_exe(t_shell_data *shell)
{
	if (shell && shell->av && shell->av[1] && !(ft_strncmp(shell->av[1],
				"--dev", 5) == 0 || ft_strncmp(shell->av[1], "-d", 2) == 0))
		argv_execution(shell->av[1], shell);
}
