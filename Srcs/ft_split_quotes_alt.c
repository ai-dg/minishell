/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes_alt.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:37:58 by ls                #+#    #+#             */
/*   Updated: 2024/06/24 16:40:46 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	set_null_split_quotes_values(t_parser *p, char ***words)
{
	*words = NULL;
	p->total_args = NULL;
	p->start = NULL;
	p->len_words = NULL;
}

char	**init_split_quotes_values(t_parser *p, char ***words, char *str,
		t_shell_data *shell)
{
	p->total_args = malloc(sizeof(int));
	if (p->total_args == NULL)
		exit_1_malloc(&shell);
	*p->total_args = count_total_args(str);
	count_len_words(str, p, shell);
	*words = (char **)malloc(sizeof(char *) * (*p->total_args + 1));
	if (!*words)
		exit_1_malloc(&shell);
	return (*words);
}

char	*char_copy(char *words, int len, int index, char *str)
{
	int	j;

	j = 0;
	while (str[index] && j < len)
	{
		words[j] = str[index];
		index++;
		j++;
	}
	if (len != 0)
		words[j] = '\0';
	return (words);
}

char	**fill_chars(t_parser *p, char **words, char *str)
{
	int	i;

	i = 0;
	while (i < *p->total_args)
	{
		words[i] = (char *)malloc(sizeof(char) * (p->len_words[i] + 1));
		if (words[i] == NULL)
			return (free_on_split_quote_data(p, words, true), NULL);
		reset_buf(words[i], p->len_words[i] + 1);
		words[i] = char_copy(words[i], p->len_words[i], p->start[i], str);
		i++;
	}
	words[i] = NULL;
	return (words);
}

char	**ft_split_quotes_alt(char *str, t_shell_data *shell)
{
	t_parser	p;
	char		**words;

	(void)shell;
	set_null_split_quotes_values(&p, &words);
	if (!str)
		return (NULL);
	init_split_quotes_values(&p, &words, str, shell);
	words = fill_chars(&p, words, str);
	if (!words)
	{
		return (free_on_split_quote_data(&p, words, true), NULL);
	}
	return (free_on_split_quote_data(&p, NULL, false), words);
}
