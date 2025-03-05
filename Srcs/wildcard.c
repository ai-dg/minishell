/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:16:46 by ls                #+#    #+#             */
/*   Updated: 2024/06/24 08:01:14 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static char	**run_expansion(t_wild *w, char **dir, bool *show_hided)
{
	char	**new_dir;

	new_dir = NULL;
	while (dir[w->i])
	{
		if (!*show_hided && dir[w->i][0] == '.')
			ft_drop();
		else
		{
			w->temp = get_sub_dirs(dir[w->i], *show_hided);
			if (w->temp)
			{
				w->expanded = ft_fstrjoin(w->expanded, w->temp, BOTH);
				new_dir = ft_push_chars_to_array(new_dir, w->expanded);
				free_variable((void **)&w->expanded);
			}
		}
		w->i++;
	}
	return (new_dir);
}

char	*expand_wildcard_from_directories(char **to_expand, bool *show_hided)
{
	char	**dir;
	t_wild	w;
	char	**new_dir;

	new_dir = NULL;
	set_wild_struct(&w, (*to_expand), false);
	dir = get_sorted_dirs(w.path, DT_DIR);
	if (!dir)
		return (free_variable((void **)&w.path), NULL);
	new_dir = run_expansion(&w, dir, show_hided);
	if (!new_dir)
		new_dir = ft_push_chars_to_array(new_dir, "*/*");
	new_dir = ft_subsplit(new_dir);
	replace_all_spaces(new_dir, REPLACE);
	ft_sort_array_ci(new_dir);
	w.expanded = ft_join_splitted(new_dir, " ");
	return (free_array(&dir), free_array(&new_dir),
		free_variable((void **)&w.path), w.expanded);
}

char	*get_wildcard_to_expand(char **prompt)
{
	int		i;
	char	*to_expand;

	to_expand = NULL;
	i = 0;
	while ((*prompt)[i] && (*prompt)[i] != '*')
		i++;
	while (i > 0 && (*prompt)[i - 1] && (*prompt)[i - 1] != ' ')
		i--;
	if (!(*prompt)[i])
		return (NULL);
	to_expand = ft_substr(&(*prompt)[i], 0, find_index(' ', &(*prompt)[i]));
	return (to_expand);
}

bool	set_show_hided(char **prompt)
{
	return (ft_strstr((*prompt), "-a") || ft_strstr((*prompt), "-la"));
}

char	*expand_wildcard(char *prompt, t_shell_data *shell)
{
	char	*to_expand;
	char	*expanded;
	bool	show_hided;

	expanded = NULL;
	to_expand = NULL;
	show_hided = false;
	show_hided = set_show_hided(&prompt);
	to_expand = get_wildcard_to_expand(&prompt);
	if (ft_strncmp(to_expand, "*/*", 3) == 0 && ft_strlen(to_expand) == 3)
		expanded = expand_wildcard_from_directories(&to_expand, &show_hided);
	else if (find_index('*', to_expand) != -1)
		expanded = expand_wildcard_from_dir(&to_expand, &show_hided);
	if (!expanded)
		return (free_variable((void **)&to_expand), prompt);
	prompt = expand_char(&prompt, to_expand, &expanded, shell);
	return (free_variable((void **)&to_expand),
		free_variable((void **)&expanded), prompt);
}
