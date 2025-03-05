/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_count_len_words_1.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 22:11:14 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/14 18:15:29 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static void	fill_first_condition(t_parsing_values *values, int **len_words,
		int **start)
{
	if (values->in_args)
	{
		(*len_words)[values->y] = values->len;
		values->y++;
		values->len = 0;
	}
	(*start)[values->y] = values->i;
	(*len_words)[values->y] = 1;
	values->y++;
	values->in_args = 0;
}

static void	fill_second_condition(t_parsing_values *values, int **len_words)
{
	if (values->in_args)
	{
		values->in_args = 0;
		(*len_words)[values->y] = values->len;
		values->y++;
		values->len = 0;
	}
}

static void	fill_third_condition(t_parsing_values *values, int **start)
{
	values->in_args = 1;
	values->count++;
	(*start)[values->y] = values->i;
	values->len = 1;
}

static void	fill_final_word(t_parsing_values *values, int **len_words)
{
	if (values->in_args)
	{
		(*len_words)[values->y] = values->len;
		values->y++;
	}
}

void	count_len_words(char *str, t_parser *p, t_shell_data *shell)
{
	t_parsing_values	values;

	initialize_values(&values);
	allocation_len_and_start(*p->total_args, &p->len_words, &p->start, shell);
	while (str[values.i] && str[values.i] != '\n')
	{
		if (if_quote(str[values.i]) == true)
			values.quote++;
		if (if_trim(str, values.i) == true && values.quote % 2 == 0)
			fill_first_condition(&values, &p->len_words, &p->start);
		else if ((str[values.i] <= 32 && values.quote % 2 == 0))
			fill_second_condition(&values, &p->len_words);
		else if (!values.in_args)
			fill_third_condition(&values, &p->start);
		else
			values.len++;
		values.i++;
	}
	fill_final_word(&values, &p->len_words);
}
