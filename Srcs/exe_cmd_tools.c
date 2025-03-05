/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:42:45 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/19 10:07:49 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	remove_non_printable_chars(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (isprint((unsigned char)str[i]))
		{
			str[j] = str[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
}

void	syntax_clean_system(char **to_clean, t_shell_data *shell)
{
	int		i;
	char	*processed_arg;

	i = 0;
	processed_arg = NULL;
	while (to_clean && to_clean[i])
	{
		if (to_clean[i])
		{
			processed_arg = handle_indicators_and_quotes(to_clean[i], shell);
			free_variable((void **)&to_clean[i]);
			to_clean[i] = ft_strdup(processed_arg);
			free_variable((void **)&processed_arg);
			shell->dollar_expansion_trim = false;
		}
		i++;
	}
}

void	syntax_clean_system_str(char **to_clean, t_shell_data *shell)
{
	char	*processed_cmd;
	char	*new_memory;

	processed_cmd = handle_indicators_and_quotes(*to_clean, shell);
	new_memory = ft_strdup(processed_cmd);
	if (new_memory)
	{
		free_variable((void **)to_clean);
		*to_clean = new_memory;
	}
	free_variable((void **)&processed_cmd);
	shell->dollar_expansion_trim = false;
}

void	replace_system(char **to_replace, char indicator_dollar)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (to_replace != NULL && to_replace[i] != NULL)
	{
		while (to_replace != NULL && to_replace[i] != NULL
			&& to_replace[i][j] != '\0')
		{
			if (to_replace[i][j] == indicator_dollar)
				to_replace[i][j] = '$';
			j++;
		}
		j = 0;
		i++;
	}
}
