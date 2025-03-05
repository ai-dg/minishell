/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_readline_quotes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 22:11:14 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/22 13:03:18 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static char	*handle_readline_errors(char *result, char delimiter)
{
	printf("minishell: unexpected EOF while looking for matching `%c'\n",
		delimiter);
	printf("minishell: syntax error: unexpected end of file\n");
	free_variable((void **)&result);
	return (NULL);
}

char	*return_readline(char *str, char delimiter)
{
	char	*read;
	char	*result;

	result = create_initial_result(str);
	if (result == NULL)
		return (NULL);
	while (1)
	{
		read = readline("> ");
		if (read == NULL)
		{
			return (handle_readline_errors(result, delimiter));
		}
		result = append_and_check(result, read, delimiter);
		if (result == NULL || ft_strchr(read, delimiter) != NULL)
			break ;
	}
	return (result);
}

static char	*continue_reading_if_needed(char *str, int total_quotes,
		char quote_char)
{
	char	*new_str;

	if (total_quotes % 2 != 0)
	{
		new_str = return_readline(str, quote_char);
		if (new_str == NULL)
		{
			free_variable((void **)&str);
			return (NULL);
		}
		free_variable((void **)&str);
		return (new_str);
	}
	return (str);
}

char	*if_readline_is_needed(char *str)
{
	int		double_quotes_total;
	int		simple_quotes_total;
	char	*result;

	double_quotes_total = total_quotes_double(str);
	simple_quotes_total = total_quotes_simple(str);
	result = continue_reading_if_needed(str, double_quotes_total, 34);
	if (result != str)
		return (result);
	return (continue_reading_if_needed(str, simple_quotes_total, 39));
}
