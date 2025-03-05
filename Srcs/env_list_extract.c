/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_extract.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:13:11 by calbor-p          #+#    #+#             */
/*   Updated: 2024/07/01 14:23:55 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static void	update_links(t_env *node)
{
	if (!node->prev && node->next)
	{
		node->next->prev = NULL;
	}
	else if (!node->next && node->prev)
	{
		node->prev->next = NULL;
	}
	else if (node->next && node->prev)
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
}

static void	*extract_or_delete_node(t_env **lst, t_env *node, t_node_mode mode,
		int size)
{
	if (mode == DELETE)
	{
		if (ft_strncmp(node->value, (*lst)->value, ft_strlen(node->value)) == 0
			&& ft_strlen(node->value) == ft_strlen((*lst)->value) && size > 1)
			*lst = (*lst)->next;
		update_links(node);
		if (size == 1)
			*lst = NULL;
		free_env_node(node);
		return (NULL);
	}
	else if (mode == EXTRACT)
	{
		if (ft_strncmp(node->value, (*lst)->value, ft_strlen(node->value)) == 0
			&& ft_strlen(node->value) == ft_strlen((*lst)->value) && size > 1)
			*lst = (*lst)->next;
		update_links(node);
		if (size == 1)
			*lst = NULL;
		return (node);
	}
	return (NULL);
}

void	*extract_node_with_key(t_env **lst, char *key, t_node_mode mode)
{
	int		size;
	t_env	*node;

	size = count_env_nodes(*lst);
	if (size > 0 && is_duplicate_key(*lst, key))
	{
		node = find_node_with_key(*lst, key);
		if (node)
		{
			return (extract_or_delete_node(lst, node, mode, size));
		}
	}
	return (NULL);
}

t_env	*free_env_node(t_env *node)
{
	if (node)
	{
		if (node->key)
			free_variable((void **)&node->key);
		if (node->value)
			free_variable((void **)&node->value);
		free_variable((void **)&node);
	}
	return (NULL);
}

void	free_env_list(t_env **lst)
{
	t_env	*tmp;
	t_env	*list;

	list = *lst;
	while (list)
	{
		tmp = list;
		list = list->next;
		free_env_node(tmp);
	}
	*lst = NULL;
}
