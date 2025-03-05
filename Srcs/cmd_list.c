/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 00:00:26 by ls                #+#    #+#             */
/*   Updated: 2024/06/24 16:40:46 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

t_cmd	*new_cmd_node(t_token *token, t_shell_data *shell)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	ft_bzero(node, sizeof(t_cmd));
	if (!node)
		exit_1_malloc(&shell);
	node->tokens = token;
	return (node);
}

int	count_cmd_nodes(t_cmd *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}
