/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_match.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 10:02:17 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/27 13:03:58 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

char	*wild_both(char *to_expand, char *to_check)
{
	char	**match;

	match = ft_split(to_expand, '*');
	if (ft_strstr(to_check, match[0]))
		return (free_array(&match), ft_strdup(to_check));
	return (free_array(&match), NULL);
}

char	*wild_start(char *to_expand, char *to_check)
{
	char	**match;

	match = ft_split(to_expand, '*');
	if (ft_strncmp_backward(match[0], to_check, ft_strlen(match[0])) == 0)
		return (free_array(&match), ft_strdup(to_check));
	return (free_array(&match), NULL);
}

char	*wild_end(char *to_expand, char *to_check)
{
	char	**match;

	match = ft_split(to_expand, '*');
	if (ft_strncmp(match[0], to_check, ft_strlen(match[0])) == 0)
		return (free_array(&match), ft_strdup(to_check));
	return (free_array(&match), NULL);
}

char	*wild_middle(char *to_expand, char *to_check)
{
	char	**match;

	match = ft_split(to_expand, '*');
	if (ft_strncmp(match[0], to_check, ft_strlen(match[0])) == 0
		&& ft_strncmp_backward(match[1], to_check, ft_strlen(match[1])) == 0)
		return (free_array(&match), ft_strdup(to_check));
	return (free_array(&match), NULL);
}

char	*wild_mixed(char *to_expand, char *to_check)
{
	(void)to_expand;
	(void)to_check;
	return (NULL);
}
