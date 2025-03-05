/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_dirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:43:05 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/20 19:04:14 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	set_wild_struct_i(t_wild *w, char *to_expand, bool *show_hided)
{
	while (to_expand[w->i] == w->path[w->i])
	{
		if (ft_strlen(to_expand) == 2 && to_expand[0] == '.'
			&& to_expand[1] == '*')
		{
			*show_hided = true;
			break ;
		}
		w->i++;
	}
}

static void	run_expansion(t_wild *w, char *to_expand, bool *show_hided)
{
	while (w->into_dir)
	{
		w->temp = ft_wild_matcher(&to_expand[w->i], w->into_dir->d_name,
				w->context);
		if (w->temp)
		{
			if (!*show_hided && w->temp[0] == '.')
				ft_drop();
			else if (*show_hided && ((ft_strlen(w->temp) == 1
						&& w->temp[0] == '.') || (ft_strlen(w->temp) == 2
						&& ft_strncmp(w->temp, "..", 2) == 0)))
				ft_drop();
			else
				w->expands = ft_push_chars_to_array(w->expands, w->temp);
			free_variable((void **)&w->temp);
		}
		w->into_dir = readdir(w->check);
	}
	closedir(w->check);
}

char	*expand_wildcard_from_dir(char **tx, bool *show_hided)
{
	t_wild	w;
	char	*to_expand;

	to_expand = *tx;
	set_wild_struct(&w, to_expand, true);
	set_wild_struct_i(&w, to_expand, show_hided);
	run_expansion(&w, to_expand, show_hided);
	if (w.expands)
		w.expanded = get_sorted_wildcards(w.expands);
	free_variable((void **)&w.path);
	return (w.expanded);
}
