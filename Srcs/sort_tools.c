/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:40:55 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/15 12:27:01 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	print_chars(char *prefix, char **chars)
{
	int	i;

	i = -1;
	while (chars[++i])
	{
		if (prefix)
			printf("%s ", prefix);
		printf("%s\n", chars[i]);
	}
}
