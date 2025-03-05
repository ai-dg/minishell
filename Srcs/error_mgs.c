/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mgs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 11:50:26 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/14 17:38:35 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	exit_msg(char *av, char *msg)
{
	write(STDERR_FILENO, "minishell: ", ft_strlen("minishell: "));
	write(STDERR_FILENO, "exit: ", ft_strlen("exit: "));
	write(STDERR_FILENO, av, ft_strlen(av));
	write(STDERR_FILENO, ": ", ft_strlen(": "));
	write(STDERR_FILENO, msg, ft_strlen(msg));
}

void	error_msg(char *err)
{
	write(STDERR_FILENO, err, ft_strlen(err));
}

void	err_msg(char *msg)
{
	write(STDERR_FILENO, "minishell: ", ft_strlen("minishell: "));
	write(STDERR_FILENO, msg, ft_strlen(msg));
}

void	unexpected_token_msg(char *msg)
{
	err_msg("syntax error near unexpected token `");
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "'\n", 2);
}
