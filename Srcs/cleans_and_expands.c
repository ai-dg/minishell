/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleans_and_expands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 20:52:54 by ls                #+#    #+#             */
/*   Updated: 2024/07/01 15:53:11 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

// static bool	if_echo_in_args(char ***words, int *i)
// {
// 	int	x;

// 	x = *i;
// 	while (x >= 0)
// 	{
// 		if (ft_strstr((*words)[x], "echo") != NULL)
// 			return (true);
// 		x--;
// 	}
// 	return (false);
// }

static void	final_split_words(char ***words, t_shell_data *shell)
{
	int		i;
	char	*old_word;

	i = 0;
	old_word = NULL;
	(*words) = ft_subsplit((*words));
	shell->mode = SECOND;
	while ((*words)[i])
	{
		expand_if_dollar_found(words, &i, old_word, shell);
		i++;
	}
	shell->mode = 0;
	i = 0;
	if ((*words))
	{
		while ((*words)[i])
		{
			decode_quotes_before_smart((*words)[i]);
			(*words)[i] = remove_spaces_before_after_word((*words)[i]);
			(*words)[i] = smart_remove_quotes((*words)[i], shell);
			decode_quotes_after_smart_quotes((*words)[i]);
			i++;
		}
	}
}

char	**cleans_and_expands(t_shell_data *shell, char **words)
{
	int		i;
	char	*old_word;

	old_word = NULL;
	i = -1;
	while (words[++i])
		words[i] = expand_lang(words[i], shell);
	check_and_remove_nonexistent_vars(&words, shell);
	shell->mode = FIRST;
	i = 0;
	while (words[i])
	{
		expand_if_dollar_found(&words, &i, old_word, shell);
		expand_if_wildcard_found(&words, &i, old_word, shell);
		i++;
	}
	shell->mode = 0;
	i = -1;
	while (words[++i])
	{
		add_espace_if_need(&words[i], '"', shell);
		add_espace_if_need(&words[i], '\'', shell);
	}
	final_split_words(&words, shell);
	return (words);
}
