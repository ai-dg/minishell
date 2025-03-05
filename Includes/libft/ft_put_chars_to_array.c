/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_chars_to_array.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 05:45:27 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/15 05:48:54 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_push_chars_to_array(char **array, char *to_add)
{
	char	**new;
	int		length;

	if (!array)
	{
		new = (char **)malloc(sizeof(char *) * 2);
		if (!new)
			return (NULL);
		new[0] = ft_strdup(to_add);
		new[1] = NULL;
		free_array(&array);
		return (new);
	}
	length = ft_count_args(array);
	new = malloc((length + 2) * sizeof(char *));
	if (!new)
		return (free_array(&array), NULL);
	new = ft_dup_chars(array, new);
	length = ft_count_args(new) - 1;
	new[length + 1] = ft_strdup(to_add);
	new[length + 2] = NULL;
	return (free_array(&array), new);
}
