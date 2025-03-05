/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_args_and_system_tools.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:24:52 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/21 18:53:03 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

bool	is_printable_and_no_special(char c)
{
	if ((c > 32 && c < 127) && c != '|' && c != '\\' && c != '&')
		return (true);
	return (false);
}
