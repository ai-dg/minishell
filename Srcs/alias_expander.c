/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 20:57:23 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/19 16:25:12 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

char	*expand_alias(t_shell_data *shell, char *key)
{
	return (get_value_from_key(shell->alias, key));
}

static int	is_alias_match(char *prompt, int i, char *alias_key)
{
	size_t	key_len;

	key_len = ft_strlen(alias_key);
	if (i == 0 && ft_strncmp(&prompt[i], alias_key, key_len) == 0 && prompt[i
			+ key_len] && prompt[i + key_len] == ' ')
		return (1);
	if (ft_strncmp(&prompt[i], alias_key, key_len) == 0
		&& ft_strlen(prompt) == key_len)
		return (1);
	return (0);
}

static void	expand_alias_at_index(char **prompt, t_env *alias,
		t_shell_data *shell)
{
	char	*temp;

	temp = NULL;
	if (alias->value)
	{
		*prompt = expand_char(prompt, alias->key, &alias->value, shell);
		temp = ft_strtrim(*prompt, "\"'");
		free_variable((void **)prompt);
		*prompt = temp;
	}
}

static void	process_alias(char **prompt, t_env *alias, t_shell_data *shell)
{
	int	i;

	i = 0;
	while ((*prompt)[i])
	{
		if (is_alias_match(*prompt, i, alias->key))
		{
			expand_alias_at_index(prompt, alias, shell);
			break ;
		}
		i++;
	}
}

char	*expand_aliases(char *prompt, t_shell_data *shell)
{
	t_env	*alias;

	alias = shell->alias;
	while (alias)
	{
		process_alias(&prompt, alias, shell);
		alias = alias->next;
	}
	return (prompt);
}
