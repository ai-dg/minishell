/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lang_expansion_lang_occurences.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:48:09 by ls                #+#    #+#             */
/*   Updated: 2024/06/14 18:53:56 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static void	count_occurences(char *str, int *i, char c, int *occ)
{
	while (str[*i] && str[*i] != c)
		(*i)++;
	if (str[*i] == c && swap_back(str, *i))
		(*occ)++;
}

int	find_lang_occurences(char *str, char c)
{
	int	i;
	int	occ;

	occ = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] != '$' && str[i])
			i++;
		if (!str[i])
			break ;
		i++;
		if (str[i] && str[i] == c)
		{
			i++;
			if (!str[i])
				break ;
			count_occurences(str, &i, c, &occ);
		}
		else
			continue ;
	}
	return (occ);
}
