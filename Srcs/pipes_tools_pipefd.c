/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_tools_pipefd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:46:34 by dagudelo          #+#    #+#             */
/*   Updated: 2024/06/25 14:45:07 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

t_pipefd	*new_pipefd_node(t_shell_data *shell)
{
	t_pipefd	*node;

	node = malloc(sizeof(t_pipefd));
	if (node == NULL)
		exit_1_malloc(&shell);
	ft_bzero(node, sizeof(t_pipefd));
	node->values = malloc(sizeof(int) * 2);
	if (node->values == NULL)
		exit_1_malloc(&shell);
	node->values[1] = -1;
	node->values[0] = -1;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

t_pipefd	*push_pipefd(t_pipefd *stack, t_shell_data *shell)
{
	t_pipefd	*newnode;
	t_pipefd	*current;

	newnode = new_pipefd_node(shell);
	if (stack == NULL)
		return (newnode);
	current = stack;
	while (current->next != NULL)
		current = current->next;
	current->next = newnode;
	newnode->prev = current;
	return (stack);
}
