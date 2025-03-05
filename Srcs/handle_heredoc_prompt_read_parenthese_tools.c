/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc_prompt_read_parenthese_tools        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 08:12:58 by ls                #+#    #+#             */
/*   Updated: 2024/06/22 16:00:23 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	init_read(t_readline_parenth *read)
{
	read->i = 0;
	read->j = 0;
	read->read = NULL;
	read->to_find = 0;
	read->count_close = 0;
	read->current_length = 0;
	read->new_size = 0;
	read->new_prompt = NULL;
}

bool	readline_parentheses_needed(char *prompt)
{
	int	i;
	int	count_open;
	int	count_close;

	i = 0;
	count_open = 0;
	count_close = 0;
	while (prompt[i])
	{
		if (prompt[i] == '(')
			count_open++;
		if (prompt[i] == ')')
			count_close++;
		i++;
	}
	if (count_open != count_close)
		return (true);
	return (false);
}

int	count_to_find_parentheses(char *prompt)
{
	int	i;
	int	count_open;
	int	count_close;
	int	to_find;

	i = 0;
	count_open = 0;
	count_close = 0;
	while (prompt[i])
	{
		if (prompt[i] == '(')
			count_open++;
		if (prompt[i] == ')')
			count_close++;
		i++;
	}
	to_find = count_open - count_close;
	return (to_find);
}

int	count_close_parentheses(char *read)
{
	int	i;
	int	count_close;

	i = 0;
	count_close = 0;
	while (read[i])
	{
		if (read[i] == ')')
			count_close++;
		i++;
	}
	return (count_close);
}
