/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 22:11:14 by calbor-p          #+#    #+#             */
/*   Updated: 2024/07/01 11:07:45 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	fill_initial_parsed(char **words, t_shell_data *shell)
{
	int	i;

	i = 0;
	while (words[i])
	{
		shell->initial_parsed[i] = ft_strdup(words[i]);
		if (shell->initial_parsed[i] == NULL)
		{
			perror("strdup");
			free_array(&shell->initial_parsed);
			free_array(&words);
			return ;
		}
		i++;
	}
	shell->initial_parsed[i] = NULL;
}

static void	clean_words_system(t_shell_data *shell, char **words)
{
	int	i;

	i = 0;
	syntax_clean_system(words, shell);
	replace_system(words, 0x1D);
	while (words[i])
	{
		remove_non_printable_chars(words[i]);
		i++;
	}
	shell->exit_status = 0;
}

static bool	is_double_quote_only(char *inst, char c)
{
	if (inst == NULL)
		return (false);
	return (inst[0] == c && inst[1] == c && inst[2] == '\0');
}

void	add_espace_if_need(char **inst, char c, t_shell_data *shell)
{
	char	*new_inst;

	if (is_double_quote_only(*inst, c) == false)
		return ;
	new_inst = (char *)malloc(sizeof(char) * (ft_strlen(*inst) + 2));
	if (new_inst == NULL)
		exit_1_malloc(&shell);
	new_inst[0] = c;
	new_inst[1] = ' ';
	new_inst[2] = c;
	new_inst[3] = '\0';
	free_variable((void **)&*inst);
	*inst = new_inst;
}

void	fill_args_to_parsed(char *inst, t_shell_data *shell)
{
	char	**words;

	words = NULL;
	shell->to_expand_in_doc = add_logic_expand_in_doc(inst, shell);
	words = ft_split_quotes_alt(inst, shell);
	words = cleans_and_expands(shell, words);
	if (words == NULL)
	{
		free_variable((void **)&words);
		shell->initial_parsed = NULL;
		return ;
	}
	shell->argc = ft_count_args(words);
	shell->initial_parsed = (char **)malloc(sizeof(char *)
			* (ft_count_args(words) + 1));
	if (shell->initial_parsed == NULL)
		exit_1_malloc(&shell);
	clean_words_system(shell, words);
	fill_initial_parsed(words, shell);
	free_array(&words);
}
