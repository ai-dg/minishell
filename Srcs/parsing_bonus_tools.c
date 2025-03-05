/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:24:09 by ls                #+#    #+#             */
/*   Updated: 2024/06/18 12:38:05 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args != NULL && args[i])
		i++;
	return (i);
}

int	index_from_pointer(char *prompt, char *p)
{
	char	*end;
	int		i;

	i = 0;
	end = &prompt[ft_strlen(prompt) - 1];
	if (p >= prompt && p <= end)
	{
		while (prompt < p)
		{
			i++;
			prompt++;
		}
		return (i);
	}
	else
		return (-1);
}

void	reset_buffers_array(char **buffs, int length, int sublength)
{
	int	i;

	i = 0;
	while (i < length)
	{
		reset_buf(buffs[i], sublength);
		i++;
	}
}

char	*get_next_prompt(char **splitted)
{
	static char	**local = NULL;
	static int	i = 0;

	if (splitted)
	{
		local = splitted;
		i = count_args(splitted) - 1;
	}
	else
		i--;
	if (i < 0)
	{
		local = NULL;
		i = 0;
		return (NULL);
	}
	return (local[i]);
}
