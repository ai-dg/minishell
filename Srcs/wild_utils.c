/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 10:06:10 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/19 21:28:36 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

char	*get_sorted_wildcards(char **to_sort)
{
	char	*sorted;

	sorted = NULL;
	ft_sort_array_ci(to_sort);
	format_files_array(to_sort);
	sorted = ft_join_splitted(to_sort, " ");
	return (free_array(&to_sort), free_variable((void **)&to_sort), sorted);
}

char	*extract_path_from_glob(char *to_expand)
{
	char	*path;
	int		index;

	index = 0;
	path = NULL;
	while (to_expand[index] != '*' && (to_expand[index] == '.'
			|| to_expand[index] == '/'))
		index++;
	if (index == 0)
	{
		path = ft_strdup(".");
		return (path);
	}
	path = ft_substr(to_expand, 0, index);
	return (path);
}

void	set_wild_struct(t_wild *wild, char *to_expand, bool open_dir)
{
	wild->expanded = NULL;
	wild->expands = NULL;
	wild->path = NULL;
	wild->temp = NULL;
	wild->i = 0;
	wild->context = get_comp_context(to_expand);
	wild->path = extract_path_from_glob(to_expand);
	if (open_dir)
	{
		wild->check = opendir(wild->path);
		if (!wild->check)
			printf("could not find!\n");
		wild->into_dir = readdir(wild->check);
	}
}
