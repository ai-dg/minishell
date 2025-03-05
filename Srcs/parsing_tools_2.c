/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 22:11:14 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/25 18:11:58 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

bool	if_only_espaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

bool	if_only_tabs(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '\t')
			return (false);
		i++;
	}
	return (true);
}

int	handle_basic_invalid_args(char **inst, t_shell_data *shell)
{
	if (directory_errors(shell, (*inst)))
		return (0);
	if (redirection_errors(shell, inst) == 1)
		return (shell->exit_status = 2, 0);
	if (ft_strlen((*inst)) == 1 && (*inst)[0] == ':')
		return (shell->exit_status = 0, 0);
	if (ft_strcmp((*inst), "!") == 0)
		return (shell->exit_status = 1, 0);
	if (if_only_espaces((*inst)))
		return (shell->exit_status = 0, 0);
	if (if_only_tabs((*inst)))
		return (shell->exit_status = 0, 0);
	return (1);
}
