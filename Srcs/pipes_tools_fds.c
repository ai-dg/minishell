/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_tools_fds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:46:34 by dagudelo          #+#    #+#             */
/*   Updated: 2024/06/24 16:40:46 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static int	*initialize_int_ptr(t_shell_data *shell)
{
	int	*ptr;

	ptr = malloc(sizeof(int));
	if (ptr == NULL)
	{
		exit_1_malloc(&shell);
	}
	*ptr = -1;
	return (ptr);
}

static void	handle_allocation_failure(t_fds **node, t_shell_data *shell)
{
	perror("Failure memory allocation\n");
	if (*node)
	{
		free_variable((void **)&node);
	}
	exit_1_malloc(&shell);
}

t_fds	*new_fds_node(t_shell_data *shell)
{
	t_fds	*node;

	node = malloc(sizeof(t_fds));
	if (node == NULL)
		handle_allocation_failure(&node, shell);
	ft_bzero(node, sizeof(t_fds));
	node->input = initialize_int_ptr(shell);
	if (node->input == NULL)
		handle_allocation_failure(&node, shell);
	node->output = initialize_int_ptr(shell);
	if (node->output == NULL)
		handle_allocation_failure(&node, shell);
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

t_fds	*push_fds(t_fds *stack, t_shell_data *shell)
{
	t_fds	*newnode;
	t_fds	*current;

	newnode = new_fds_node(shell);
	if (stack == NULL)
		return (newnode);
	current = stack;
	while (current->next != NULL)
		current = current->next;
	current->next = newnode;
	newnode->prev = current;
	return (stack);
}
