/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lang_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:48:09 by ls                #+#    #+#             */
/*   Updated: 2024/06/19 16:25:35 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	end_index(char *to_expand, char *sequence, int start)
{
	while (to_expand[start])
	{
		if (ft_strncmp(&to_expand[start], sequence, ft_strlen(sequence)) == 0)
		{
			return (start + 1);
		}
		start++;
	}
	return (-1);
}

int	ft_strstr_index(char *to_expand, char *sequence)
{
	int	i;

	i = 0;
	while (to_expand[i])
	{
		if (ft_strncmp(&to_expand[i], sequence, ft_strlen(sequence)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	*filter_occurences(char *to_expand, char *to_filter, char *end_char,
		t_shell_data *shell)
{
	int		start;
	int		end;
	char	*to_replace;
	char	*by;

	start = 0;
	end = 0;
	start = ft_strstr_index(to_expand, to_filter);
	end = end_index(to_expand, end_char, start + ft_strlen(to_filter));
	if (start > -1)
	{
		to_replace = ft_substr(to_expand, start, end - start);
		by = ft_substr(&to_replace[2], 0, ft_strlen(&to_replace[2]) - 1);
		if (swap_foreward_in_lang(to_expand, start))
		{
			to_expand = expand_char(&to_expand, to_replace, &by, shell);
			to_expand = ft_fstrjoin(to_expand, "\n", FIRST);
		}
		free_variable((void **)&by);
		free_variable((void **)&to_replace);
	}
	return (to_expand);
}

char	*expand_lang(char *to_expand, t_shell_data *shell)
{
	int	occ;

	(void)shell;
	occ = find_lang_occurences(to_expand, '\'');
	while (occ--)
		to_expand = filter_occurences(to_expand, "$'", "'", shell);
	occ = find_lang_occurences(to_expand, '"');
	while (occ--)
		to_expand = filter_occurences(to_expand, "$\"", "\"", shell);
	return (to_expand);
}
