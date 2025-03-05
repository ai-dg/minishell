/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:19:00 by ls                #+#    #+#             */
/*   Updated: 2024/06/24 16:40:46 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

t_token	*new_token_node(char *value, t_shell_data *shell)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (node == NULL)
		exit_1_malloc(&shell);
	if (node)
	{
		node->value = ft_strdup(value);
		node->type = NO_TYPE;
		node->prev = NULL;
		node->next = NULL;
	}
	return (node);
}

void	free_env_node_token(t_token *node)
{
	t_token	*prev;
	t_token	*next;

	if (node == NULL)
		return ;
	prev = node->prev;
	next = node->next;
	if (prev != NULL)
		prev->next = next;
	if (next != NULL)
		next->prev = prev;
	free_variable((void **)&node->value);
	free_variable((void **)&node);
}

int	count_token_nodes(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens)
	{
		count++;
		tokens = tokens->next;
	}
	return (count);
}

t_token	*push_token(t_token *stack, char *value, t_shell_data *shell)
{
	t_token	*newnode;
	t_token	*current;
	t_token	*temp;

	newnode = new_token_node(value, shell);
	if (stack == NULL)
		return (newnode);
	current = stack;
	while (current->next != NULL)
		current = current->next;
	current->next = newnode;
	current = stack;
	temp = stack;
	while (temp->next != NULL)
	{
		current = current->next;
		current->prev = temp;
		temp = temp->next;
	}
	return (stack);
}

void	free_token_stack(t_token **stack)
{
	t_token	*temp;

	if (stack == NULL || *stack == NULL)
		return ;
	while (*stack != NULL)
	{
		temp = *stack;
		*stack = (*stack)->next;
		free_variable((void **)&temp);
	}
}
