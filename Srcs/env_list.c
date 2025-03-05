/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 09:53:47 by calbor-p          #+#    #+#             */
/*   Updated: 2024/07/01 14:25:04 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

t_env	*new_env_node(char *key, char *value, t_shell_data *shell)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		exit_1_malloc(&shell);
	node->key = ft_strdup(key);
	if (value)
		node->value = ft_strdup(value);
	else
		node->value = NULL;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	change_env_value(t_env *list, char *key, char *value)
{
	while (list)
	{
		if (ft_strncmp(list->key, key, ft_strlen(key)) == 0
			&& ft_strlen(key) == ft_strlen(list->key))
		{
			if (list->value)
				free_variable((void **)&list->value);
			list->value = NULL;
			if (value)
				list->value = ft_strdup(value);
			return ;
		}
		list = list->next;
	}
}

void	push_back_env_node(t_env **list, t_env *node)
{
	t_env	*lst;

	lst = *list;
	if (lst && node)
	{
		while (lst->next)
		{
			lst = lst->next;
		}
		lst->next = node;
		node->prev = lst;
		node->next = NULL;
	}
}

t_env	*find_node_with_key(t_env *list, char *key)
{
	while (list)
	{
		if (ft_strncmp(key, list->key, ft_strlen(list->key)) == 0
			&& ft_strlen(key) == ft_strlen(list->key))
			return (list);
		list = list->next;
	}
	return (NULL);
}

char	*get_value_from_key(t_env *list, char *key)
{
	if (!list || !key)
		return (NULL);
	while (list)
	{
		if (ft_strncmp(key, list->key, ft_strlen(list->key)) == 0
			&& ft_strlen(key) == ft_strlen(list->key))
			return (list->value);
		list = list->next;
	}
	return (NULL);
}
