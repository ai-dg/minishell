/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:21:51 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/27 14:38:43 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	print_tokens(t_token *token, t_shell_data *shell)
{
	int		i;
	t_token	*current;

	(void)i;
	i = 1;
	current = token;
	if (shell->debug_mode == DEV)
	{
		while (current != NULL)
		{
			printf(" token %d - %s: ", i, token->value);
			status(current, shell);
			i++;
			current = current->next;
		}
	}
}

void	print_tokens_stack(t_token *tokens, t_shell_data *shell)
{
	t_token	*current;
	int		i;

	current = tokens;
	i = 0;
	if (shell->debug_mode == DEV)
	{
		printf("\nToken list: \n");
		while (current != NULL)
		{
			printf("Token[%d]: %s\n", i, current->value);
			current = current->next;
			i++;
		}
	}
}

void	print_tokens_status(t_shell_data *shell)
{
	int		i;
	t_cmd	*current;

	(void)i;
	i = 1;
	current = shell->pipe;
	if (shell->debug_mode == DEV)
	{
		while (current)
		{
			printf("cmd : %d\n", i);
			printf("Args: \n");
			print_splitted(current->args);
			print_tokens(current->tokens, shell);
			current = current->next;
			i++;
		}
	}
}

int	print_keyval(t_env *lst, char *key)
{
	char	*value;
	int		res;

	res = 1;
	value = get_value_from_key(lst, key);
	printf("%s=", key);
	if (value)
	{
		res = 0;
		printf("%s\n", value);
	}
	return (res);
}
