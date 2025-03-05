/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:35:06 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/24 16:39:20 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static int	fill_replaced(int *start, char *replaced, char *prompt, char *by)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < *start)
	{
		replaced[i] = prompt[i];
		i++;
	}
	while (by[j])
	{
		replaced[i] = by[j];
		i++;
		j++;
	}
	return (i);
}

char	*expand_char(char **prompt, char *to_replace, char **by,
		t_shell_data *shell)
{
	int		start;
	char	*replaced;
	int		new_len;
	int		i;

	i = 0;
	new_len = ft_strlen((*prompt)) + ft_strlen((*by))
		- ft_strlen(to_replace) + 1;
	start = 0;
	replaced = malloc((new_len + 2) * sizeof(char));
	if (!replaced)
		exit_1_malloc(&shell);
	reset_buf(replaced, new_len + 2);
	start = ft_strstr_index((*prompt), to_replace);
	i = fill_replaced(&start, replaced, (*prompt), (*by));
	start += ft_strlen(to_replace);
	while ((*prompt)[start])
	{
		replaced[i] = (*prompt)[start];
		i++;
		start++;
	}
	replaced[i] = '\0';
	return (free_variable((void **)&(*prompt)), replaced);
}
