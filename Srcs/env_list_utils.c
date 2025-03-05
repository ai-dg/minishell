/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:48:22 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/24 16:40:46 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	count_env_nodes(t_env *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

char	*merge_node(t_env *lst)
{
	char	*tmp;
	char	*merged;

	if (!lst->value)
		return (ft_strdup(lst->key));
	tmp = ft_fstrjoin(lst->key, "=", NONE);
	merged = ft_fstrjoin(tmp, lst->value, FIRST);
	return (merged);
}

char	**expand_env_to_char(t_env *lst, char **old, t_shell_data *shell)
{
	char	**expanded;
	int		i;

	i = 0;
	if (old)
		free_array(&old);
	if (lst)
	{
		expanded = malloc(sizeof(char *) * (count_env_nodes(lst) + 1));
		if (!expanded)
			exit_1_malloc(&shell);
		while (lst)
		{
			expanded[i] = merge_node(lst);
			lst = lst->next;
			i++;
		}
		expanded[i] = NULL;
		return (expanded);
	}
	return (NULL);
}

bool	is_duplicate_key(t_env *lst, char *key)
{
	int	cmp;

	if (lst)
	{
		while (lst)
		{
			if (ft_strlen(key) > ft_strlen(lst->key))
				cmp = (int)ft_strlen(key);
			else
				cmp = (int)ft_strlen(lst->key);
			if (lst->key && ft_strncmp(key, lst->key, cmp) == 0)
			{
				return (true);
			}
			lst = lst->next;
		}
	}
	return (false);
}
