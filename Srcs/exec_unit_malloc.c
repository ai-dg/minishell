/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unit_malloc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 10:56:46 by ls                #+#    #+#             */
/*   Updated: 2024/06/18 15:34:22 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

t_exec_unit	*create_exec_unit(char *prompt, int type, t_exec_unit *parent)
{
	t_exec_unit	*new;

	(void)parent;
	new = malloc(sizeof(t_exec_unit));
	if (!new)
		return (NULL);
	ft_bzero(new, sizeof(t_exec_unit));
	new->p_unit = parent;
	new->l_unit = NULL;
	new->r_unit = NULL;
	if (prompt)
	{
		new->prompt = ft_strdup(prompt);
		ft_unallocated_trim(new->prompt);
	}
	new->type = type;
	return (new);
}

t_exec_unit	*get_exec_root(t_exec_unit *unit)
{
	t_exec_unit	*root;

	root = unit;
	if (root)
		while (root->p_unit != NULL)
			root = root->p_unit;
	return (root);
}

void	clear_exec_unit(t_exec_unit *exec_unit)
{
	if (!exec_unit)
		return ;
	if (exec_unit->prompt)
		free_variable((void **)&exec_unit->prompt);
	if (exec_unit->l_unit)
		clear_exec_unit(exec_unit->l_unit);
	if (exec_unit->r_unit)
		clear_exec_unit(exec_unit->r_unit);
	free_variable((void **)&exec_unit);
}

void	join_exec_unit(t_exec_unit *left, t_exec_unit *right,
		t_exec_unit **node)
{
	if (*node)
	{
		(*node)->l_unit = left;
		(*node)->r_unit = right;
		if (left)
			left->p_unit = *node;
		if (right)
			right->p_unit = *node;
	}
}
