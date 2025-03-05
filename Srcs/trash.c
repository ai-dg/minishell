/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 10:42:48 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/13 12:05:11 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	from_index(char *str, char *skip)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_found_char(skip, str[i]))
			return (i);
		i++;
	}
	return (i);
}

int	to_index(char *str, char *skip)
{
	int	i;

	i = (int)ft_strlen(str) - 1;
	while (str[i])
	{
		if (!ft_found_char(skip, str[i]))
			return (i);
		i--;
	}
	return (i);
}

char	*trim(char *str, bool to_free)
{
	int		from;
	int		to;
	char	*back;

	from = from_index(str, " \t\n");
	to = to_index(str, " \t\n");
	if (from >= to)
	{
		if (to_free)
			free_variable((void **)&str);
		return (back = ft_strdup(""));
	}
	else
	{
		back = ft_substr(str, (unsigned int)from, (size_t)to + 1);
		if (to_free)
			free_variable((void **)&str);
		return (back);
	}
	return (NULL);
}
