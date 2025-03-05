/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_args_and_system_messages.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 07:34:19 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/19 07:39:23 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	print_invalid_args_and_message(int count, int mode)
{
	if (mode == VERBOSE)
	{
		if (count == 1)
			ft_fprintf(stderr,
				"minishell: syntax error near unexpected token `&'\n");
		else if (count >= 2)
			ft_fprintf(stderr,
				"minishell: syntax error near unexpected token `&&'\n");
	}
}
