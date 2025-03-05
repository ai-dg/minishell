/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc_prompt.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:04:18 by dagudelo          #+#    #+#             */
/*   Updated: 2024/06/28 07:19:00 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static void	found_vertical_bars(t_write_prompt *write, char *prompt)
{
	while (prompt[write->i])
	{
		if (prompt[write->i] == '|' || prompt[write->i] == '\\')
		{
			write->found_bars = true;
			break ;
		}
		write->i++;
	}
	if (nothing_after_bars(prompt) == false)
		write->found_bars = false;
	write->i = ft_strlen(prompt) - 1;
}

static void	count_vertical_and_backslash(t_write_prompt *write, char *prompt)
{
	if (prompt[write->i] == '|')
	{
		write->count = 0;
		while (write->i >= 0 && prompt[write->i] == '|')
		{
			write->count++;
			if (write->count > write->nbr_consecutives_vertical_bars)
				write->nbr_consecutives_vertical_bars = write->count;
			write->i--;
		}
	}
	while (write->i >= 0 && prompt[write->i] == '\\')
	{
		write->count = 0;
		while (write->i >= 0 && prompt[write->i] == '\\')
		{
			write->count++;
			if (write->count > write->nbr_consecutives_bars)
				write->nbr_consecutives_bars = write->count;
			write->i--;
		}
		write->i--;
	}
}

static void	find_and_handle_vertical_bars_and_backslash(t_write_prompt *write,
		char *prompt)
{
	while (write->i >= 0)
	{
		if (prompt[write->i] == '|' || prompt[write->i] == '\\')
		{
			count_vertical_and_backslash(write, prompt);
			if (write->nbr_consecutives_vertical_bars > 1)
			{
				write->let_it_pass = false;
				break ;
			}
			if ((write->nbr_consecutives_bars
					+ write->nbr_consecutives_vertical_bars) % 2 != 0)
			{
				write->let_it_pass = false;
				break ;
			}
		}
		write->i--;
	}
}

static void	handle_final_definition(char **prompt, t_write_prompt *write,
		t_shell_data *shell)
{
	if (write->found_bars == true)
	{
		write->here_doc = prompt_to_here_doc(*prompt, shell);
		if (shell->error_in_readline == false && write->here_doc
			&& ft_strlen(write->here_doc) > 0)
			*prompt = ft_fstrjoin(*prompt, write->here_doc, BOTH);
		else
		{
			free_variable((void **)&write->here_doc);
			shell->error_in_readline = false;
		}
		handle_history_add_readline(prompt, shell);
		shell->write_in_here_doc = true;
		reduce_half_of_bars(*prompt, shell);
	}
	if (write->let_it_pass == false && write->found_bars == false)
		reduce_half_of_bars(*prompt, shell);
}

char	*write_in_here_doc_prompt(char *prompt, t_shell_data *shell)
{
	t_write_prompt	write;

	init_write(&write);
	found_vertical_bars(&write, prompt);
	if (find_index('|', prompt) < 0 && find_index('\\', prompt) < 0)
		return (prompt);
	if (is_single_char_in_string(prompt, "|")
		|| is_single_char_in_string(prompt, "| "))
		return (prompt);
	find_and_handle_vertical_bars_and_backslash(&write, prompt);
	if (write.let_it_pass == true)
		return (reduce_half_of_bars(prompt, shell), prompt);
	handle_final_definition(&prompt, &write, shell);
	return (prompt);
}
