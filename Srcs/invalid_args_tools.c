/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_args_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 08:12:58 by ls                #+#    #+#             */
/*   Updated: 2024/06/24 18:47:50 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

bool	is_single_char_in_string(char *str, char *cmp)
{
	int	i;

	i = 0;
	if (ft_strlen(str) == 0)
		return (false);
	while (str[i])
	{
		if (!ft_found_char(cmp, str[i]))
			return (false);
		i++;
	}
	return (true);
}
