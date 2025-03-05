/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_args_specials_chars.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:53:23 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/15 12:27:35 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	special_chars_errors(char *inst)
{
	static const char	singles[] = {'|', '&', ';', '\0'};
	char				err[3];
	int					i;

	i = 0;
	while (singles[i] != '\0')
	{
		err[0] = singles[i];
		err[1] = ' ';
		err[2] = '\0';
		if (is_single_char_in_string(inst, err))
		{
			err[1] = singles[i];
			if (ft_strlen(inst) == 1 || (inst[0] == singles[i]
					&& inst[1] == ' '))
			{
				unexpected_token_msg(&err[1]);
				return (1);
			}
			if (ft_strncmp(inst, err, 2) == 0)
				return (unexpected_token_msg(err), 1);
		}
		i++;
	}
	return (0);
}
