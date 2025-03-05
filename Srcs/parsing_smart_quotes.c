/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_smart_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 22:11:14 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/24 16:40:46 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static void	initialize_smart_remove_values(t_smart_remove_values *values,
		char *str)
{
	values->i = 0;
	values->j = 0;
	values->in_double_quote = false;
	values->in_single_quote = false;
	values->indicator_double = 0x1F;
	values->indicator_single = 0x1E;
	values->indicator_dollar = 0x1D;
	values->len = ft_strlen(str);
}

static void	first_condition_smart_remove(t_smart_remove_values *values,
		char **result, char **str)
{
	if ((*str)[values->i] == '\\')
	{
		if ((*str)[values->i + 1] == '$')
		{
			(*result)[values->j++] = values->indicator_dollar;
			values->i++;
		}
		else
			(*result)[values->j++] = values->indicator_single;
	}
}

static void	second_sub_condition(t_smart_remove_values *values, char **result)
{
	if (values->in_double_quote)
	{
		values->in_double_quote = false;
		(*result)[values->j++] = values->indicator_double;
	}
	else
		values->in_double_quote = true;
}

static void	second_condition_smart_remove(t_smart_remove_values *values,
		char **result, char **str)
{
	if ((*str)[values->i] == '\'' && (*str)[values->i + 1] == '$'
		&& values->in_double_quote == false)
	{
		(*result)[values->j++] = values->indicator_single;
		values->in_single_quote = true;
	}
	else if (!values->in_single_quote && (*str)[values->i] == '"')
	{
		second_sub_condition(values, result);
	}
	else if (!values->in_double_quote && (*str)[values->i] == '\'')
	{
		if (values->in_single_quote)
		{
			values->in_single_quote = false;
			(*result)[values->j++] = values->indicator_single;
		}
		else
			values->in_single_quote = true;
	}
	else
		(*result)[values->j++] = (*str)[values->i];
}

char	*smart_remove_quotes(char *str, t_shell_data *shell)
{
	t_smart_remove_values	values;
	char					*result;

	initialize_smart_remove_values(&values, str);
	result = (char *)malloc((sizeof(char) * values.len * 2) + 1);
	if (result == NULL)
		exit_1_malloc(&shell);
	reset_buf(result, (sizeof(char) * values.len * 2) + 1);
	while (str[values.i] != '\0')
	{
		first_condition_smart_remove(&values, &result, &str);
		second_condition_smart_remove(&values, &result, &str);
		values.i++;
	}
	result[values.j] = '\0';
	free_variable((void **)&str);
	return (result);
}
