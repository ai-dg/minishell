/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleans_and_expands_tools.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 20:52:54 by ls                #+#    #+#             */
/*   Updated: 2024/07/01 11:48:24 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static void	expand_word_and_free_old_word(char ***words, int *i, char *old_word,
		t_shell_data *shell)
{
	old_word = (*words)[*i];
	(*words)[*i] = expand_variable((*words)[*i], shell);
	if (old_word)
	{
		if (old_word != (*words)[*i])
			free_variable((void **)&old_word);
	}
}

static bool	if_variable_or_redir(char ***words, int *i, t_shell_data *shell)
{
	bool	result;

	result = false;
	if (shell->mode == FIRST)
	{
		if (ft_strstr((*words)[*i], "=") != NULL)
			result = true;
		if (*i > 0)
			if (ft_strncmp((*words)[*i - 1], ">", 1) == 0
				|| ft_strncmp((*words)[*i - 1], "<", 1) == 0)
				if (ft_strlen((*words)[*i - 1]) == 1)
					result = true;
	}
	else if (shell->mode == SECOND)
	{
		if (ft_strstr((*words)[*i], "=") != NULL)
			return (false);
		else if (*i > 0)
			if (ft_strncmp((*words)[*i - 1], ">", 1) == 0
				|| ft_strncmp((*words)[*i - 1], "<", 1) == 0)
				if (ft_strlen((*words)[*i - 1]) == 1)
					return (false);
		result = true;
	}
	return (result);
}

void	expand_if_dollar_found(char ***words, int *i, char *old_word,
		t_shell_data *shell)
{
	if (find_index('$', (*words)[*i]) > -1
		&& if_variable_or_redir(words, i, shell) == false)
	{
		if (*i < 2)
		{
			expand_word_and_free_old_word(words, i, old_word, shell);
		}
		else if (*i >= 2)
		{
			if (ft_strncmp((*words)[*i - 1], "<", 1) != 0
				&& ft_strncmp((*words)[*i - 2], "<", 1) != 0)
				expand_word_and_free_old_word(words, i, old_word, shell);
		}
	}
}

void	expand_if_wildcard_found(char ***words, int *i, char *old_word,
		t_shell_data *shell)
{
	(void)old_word;
	if (find_index('*', (*words)[*i]) > -1)
	{
		if (*i < 2)
			(*words)[*i] = expand_wildcard((*words)[*i], shell);
		else if (*i >= 2)
		{
			if (ft_strncmp((*words)[*i - 1], "<", 1) != 0
				&& ft_strncmp((*words)[*i - 2], "<", 1) != 0)
				(*words)[*i] = expand_wildcard((*words)[*i], shell);
		}
	}
}
