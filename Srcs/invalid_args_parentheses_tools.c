/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_args_parentheses_tools.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 08:12:58 by ls                #+#    #+#             */
/*   Updated: 2024/06/24 16:40:46 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

bool	is_printable_but_no_special(char c, int mode)
{
	if (mode == SKIP_PARENTHESIS)
	{
		if ((c > 32 && c < 127) && c != '|'
			&& c != '\\' && c != '&' && c != '(' )
			return (true);
	}
	else if (((c > 32 && c < 127) || c == '(' || c == ' ')
		&& c != '|' && c != '\\' && c != '&')
		return (true);
	return (false);
}

bool	is_special_char(char c)
{
	if (c == '|' || c == '\\' || c == '(' || c == '&')
		return (true);
	return (false);
}

static void	bool_condition(bool *is_current_char_word, bool *in_word,
		int *count)
{
	if (*is_current_char_word)
	{
		if (!*in_word)
			*in_word = true;
	}
	else
	{
		if (*in_word)
		{
			(*count)++;
			*in_word = false;
		}
	}
}

int	count_words_before(char *inst, int i)
{
	int		x;
	int		count;
	bool	in_word;
	bool	is_current_char_word;

	x = i - 1;
	count = 0;
	in_word = false;
	while (x >= 0)
	{
		is_current_char_word = (inst[x] > 32 && inst[x] < 127
				&& !is_special_char(inst[x]));
		if (is_special_char(inst[x]) == true)
			break ;
		bool_condition(&is_current_char_word, &in_word, &count);
		x--;
	}
	if (in_word)
		count++;
	return (count);
}

char	*find_str_to_print(char *inst, int *i, t_shell_data *shell)
{
	int		x;
	int		start;
	int		end;
	int		len;
	char	*to_return ;

	if (count_words_before(inst, *i) > 1)
		return (to_return = ((ft_strdup("("))));
	x = *i + 1;
	start = x;
	while (inst[x] && is_printable_but_no_special(inst[x], SKIP_PARENTHESIS))
		x++;
	end = x;
	len = end - start;
	to_return = (((char *)malloc(sizeof(char) * (len + 1))));
	if (to_return == NULL)
		exit_1_malloc(&shell);
	x = 0;
	while (x < len)
	{
		to_return[x] = inst[start + x];
		x++;
	}
	to_return[len] = '\0';
	return (to_return);
}
