/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 21:03:55 by ls                #+#    #+#             */
/*   Updated: 2024/06/27 17:07:18 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

char	*filter_key(char *key)
{
	if (is_a_sum(key))
	{
		key[ft_strlen(key) - 1] = '\0';
	}
	return (key);
}

static void	if_variable_not_found(t_shell_data *shell, char **keyval,
		char ***inst, int *i)
{
	if (!ft_found_char((*inst)[*i], '=') && is_valid_variable((*inst)[*i]))
	{
		if (!is_duplicate_key(shell->env, (*inst)[*i]))
			push_back_env_node(&shell->env,
				new_env_node(filter_key((*inst)[*i]), NULL, shell));
		else
			change_env_value(shell->env, filter_key((*inst)[*i]), NULL);
	}
	if (shell->session)
		if (is_duplicate_key(shell->session, keyval[0]))
			extract_node_with_key(&shell->session, keyval[0], EXTRACT);
}

static void	change_value_variable(t_shell_data *shell, char **keyval,
		char ***inst, int *i)
{
	if (!is_duplicate_key(shell->env, filter_key(keyval[0])))
		push_back_env_node(&shell->env, new_env_node(filter_key(keyval[0]),
				keyval[1], shell));
	else if (is_a_sum((*inst)[*i]))
	{
		keyval[1] = ft_fstrjoin(get_value_from_key(shell->env, keyval[0]),
				keyval[1], SECOND);
		change_env_value(shell->env, filter_key(keyval[0]), keyval[1]);
	}
	else
		change_env_value(shell->env, keyval[0], keyval[1]);
	free_array(&keyval);
}

static int	fill_env_char_by_variable(t_shell_data *shell, char **keyval,
		char ***inst, int *i)
{
	while ((*inst)[*i])
	{
		(*inst)[*i] = check_and_filter((*inst)[*i], shell);
		if (!is_valid_variable((*inst)[*i]))
		{
			printf("minishell: export: ʻ%s': not a valid identifier\n",
				(*inst)[*i]);
			shell->exit_status = 1;
		}
		keyval = ft_split_key_val((*inst)[*i], '=');
		if (!keyval)
			return (1);
		if (!ft_found_char((*inst)[*i], '=') && is_duplicate_key(shell->session,
				(*inst)[*i]))
			return (session_to_env(shell, (*inst)[1]));
		if_variable_not_found(shell, keyval, inst, i);
		change_value_variable(shell, keyval, inst, i);
		(*i)++;
	}
	return (0);
}

int	export_m(t_shell_data *shell, char **inst)
{
	char	**keyval;
	int		i;
	int		result;

	result = 0;
	keyval = NULL;
	if (ft_strncmp(inst[0], "export", ft_strlen(inst[0])) == 0)
		i = 1;
	else
		i = 0;
	if (!inst[i])
		return (shell->env_char = expand_env_to_char(shell->env,
				shell->env_char, shell), ft_sort_array_cs(shell->env_char),
			print_chars("declare -x", shell->env_char), 0);
	if (handle_export_options(shell, inst))
		return (2);
	result = fill_env_char_by_variable(shell, keyval, &inst, &i);
	return (result);
}
