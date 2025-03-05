/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 22:05:41 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/30 17:10:51 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	add_alias(t_shell_data *shell, char **inst)
{
	char	**keyval;
	char	*arg;

	keyval = NULL;
	arg = inst[1];
	keyval = ft_split_key_val(arg, '=');
	if (!keyval)
		return (shell->exit_status = 1, -1);
	if (!is_valid_variable(keyval[0]))
		return (free_array(&keyval), shell->exit_status = 127, 127);
	if (shell->alias)
	{
		if (!is_duplicate_key(shell->alias, keyval[0]))
			push_back_env_node(&shell->alias, new_env_node(keyval[0], keyval[1],
					shell));
		else
			change_env_value(shell->alias, keyval[0], keyval[1]);
	}
	else
		shell->alias = new_env_node(keyval[0], keyval[1], shell);
	return (free_array(&keyval), 0);
}

int	alias_m(t_shell_data *shell, char **inst)
{
	if (shell->debug_mode == DEV)
		print_splitted(inst);
	if (!inst[1])
	{
		print_env_list(NULL, shell->alias, inst, true);
		return (0);
	}
	return (add_alias(shell, inst));
}
