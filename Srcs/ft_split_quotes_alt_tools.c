/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes_alt_tools.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:37:58 by ls                #+#    #+#             */
/*   Updated: 2024/06/14 18:54:24 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	encode_char_with(char *words, char replace, char with)
{
	int	i;

	i = 0;
	while (words[i])
	{
		if (words[i] == replace)
			words[i] = with;
		i++;
	}
}

void	*free_on_split_quote_data(t_parser *p, char **words, bool err)
{
	if (err)
		perror("malloc");
	if (words)
		free_array(&words);
	if (p->total_args)
		free_variable((void **)&p->total_args);
	if (p->start)
		free_variable((void **)&p->start);
	if (p->len_words)
		free_variable((void **)&p->len_words);
	return (NULL);
}
