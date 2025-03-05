/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:55:59 by ls                #+#    #+#             */
/*   Updated: 2024/06/14 15:52:42 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

char	*encode_char(char *here, char find, char replace)
{
	int	i;

	i = 0;
	if (!here)
		return (ft_strdup(""));
	while (here[i])
	{
		if (here[i] == find)
			here[i] = replace;
		i++;
	}
	return (here);
}
