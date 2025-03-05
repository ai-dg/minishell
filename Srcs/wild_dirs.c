/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_dirs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 10:40:10 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/20 19:18:02 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static char	*get_expanded(char *expanded, char *dir_path, char **dir, int i)
{
	expanded = ft_fstrjoin(expanded, dir_path, FIRST);
	expanded = ft_fstrjoin(expanded, "/", FIRST);
	expanded = ft_fstrjoin(expanded, dir[i], FIRST);
	expanded = ft_fstrjoin(expanded, " ", FIRST);
	return (expanded);
}

char	*get_sub_dirs(char *dir_path, bool show_hided)
{
	char	*expanded;
	char	**dir;
	int		i;

	dir = get_sorted_dirs(dir_path, 0);
	if (!dir)
		return (NULL);
	expanded = NULL;
	i = 0;
	while (dir[i])
	{
		if (!show_hided && dir[i][0] == '.')
			ft_drop();
		else
		{
			if (find_index(' ', dir[i]) > 0)
			{
				dir[i] = get_formated_files(dir[i]);
				replace_spaces(dir[i], REMOVE);
			}
			expanded = get_expanded(expanded, dir_path, dir, i);
		}
		i++;
	}
	return (free_array(&dir), expanded);
}

char	**get_sorted_dirs(char *dir_path, unsigned char type)
{
	char			**dir;
	DIR				*check;
	struct dirent	*into_dir;

	dir = NULL;
	check = opendir(dir_path);
	if (!check)
		printf("could not find!\n");
	into_dir = readdir(check);
	while (into_dir)
	{
		if (type > 0)
		{
			if (into_dir->d_type == type)
				dir = ft_push_chars_to_array(dir, into_dir->d_name);
		}
		else
			dir = ft_push_chars_to_array(dir, into_dir->d_name);
		into_dir = readdir(check);
	}
	closedir(check);
	if (!dir)
		return (NULL);
	ft_sort_array_ci(dir);
	return (dir);
}
