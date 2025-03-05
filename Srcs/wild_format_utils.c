/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_format_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 21:26:55 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/20 18:08:16 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	replace_all_spaces(char **chars, int mode)
{
	int	i;

	i = 0;
	while (chars[i])
	{
		replace_spaces(chars[i], mode);
		i++;
	}
}

void	replace_spaces(char *temp, int mode)
{
	int	i;

	i = 0;
	while (temp[i])
	{
		if (mode == REMOVE)
		{
			if (temp[i] == ' ')
				temp[i] = 0x11;
		}
		else
		{
			if (temp[i] == 0x11)
				temp[i] = ' ';
		}
		i++;
	}
}

void	format_files_array(char **to_format)
{
	int	i;

	i = 0;
	while (to_format[i])
	{
		if (ft_found_char(to_format[i], ' ') || ft_found_char(to_format[i],
				'$'))
		{
			to_format[i] = get_formated_files(to_format[i]);
		}
		i++;
	}
}

char	*get_formated_files(char *temp)
{
	char	*replaced;

	replaced = ft_fstrjoin("'", temp, SECOND);
	replaced = ft_fstrjoin(replaced, "'", FIRST);
	return (replaced);
}
