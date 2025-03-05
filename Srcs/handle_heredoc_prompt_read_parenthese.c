/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc_prompt_read_parenthese.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 08:12:58 by ls                #+#    #+#             */
/*   Updated: 2024/06/26 11:40:41 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static void	count_len_and_realloc(t_readline_parenth *read)
{
	read->current_length = ft_strlen(read->new_prompt);
	read->new_size = read->current_length + ft_strlen(read->read) + 2;
	read->new_prompt = ft_realloc(read->new_prompt, read->new_size);
}

static void	fill_new_prompt_values(t_readline_parenth *read)
{
	if (ft_strncmp(read->read, ")", 1) != 0)
	{
		if (read->new_prompt[ft_strlen(read->new_prompt) - 1] == '|'
			&& read->new_prompt[ft_strlen(read->new_prompt) - 2] == '|')
		{
			ft_strcat(read->new_prompt + read->current_length, read->read);
		}
		else
		{
			ft_strcat(read->new_prompt + read->current_length, "|");
			ft_strcat(read->new_prompt + read->current_length + 1, read->read);
		}
	}
	else
		ft_strcat(read->new_prompt + read->current_length, read->read);
}

static void	main_loop(char **prompt, t_readline_parenth *read,
		t_shell_data *shell)
{
	while (read->count_close < read->to_find)
	{
		read->read = readline("> ");
		if (read->read == NULL && g_receipt == SIGINT)
		{
			free_variable((void **)&read->new_prompt);
			free_variable((void **)&*prompt);
			read->new_prompt = ft_strdup("");
			g_receipt = 0;
			reopen_stdin_if_needed();
			break ;
		}
		if_read_is_null(&read->new_prompt, &read->read, shell);
		if (read->read)
			read->count_close += count_close_parentheses(read->read);
		if (read->read[0] != '\0' && read->read[0] != '\n')
		{
			count_len_and_realloc(read);
			if (!read->new_prompt)
				exit_1_malloc(&shell);
			fill_new_prompt_values(read);
		}
		free_variable((void **)&read->read);
	}
}

char	*handle_parentheses(char *prompt, t_shell_data *shell)
{
	t_readline_parenth	read;

	init_read(&read);
	init_signals_alt(shell);
	read.to_find = count_to_find_parentheses(prompt);
	read.new_prompt = ft_strdup(prompt);
	if (!read.new_prompt)
		exit_1_malloc(&shell);
	main_loop(&prompt, &read, shell);
	init_signals(shell);
	if (prompt)
		free_variable((void **)&prompt);
	return (read.new_prompt);
}

void	handle_readline_parentheses(char **prompt, t_shell_data *shell)
{
	if (ft_strstr(*prompt, "export"))
		return ;
	else if (*prompt && readline_parentheses_needed(*prompt) == true)
		*prompt = handle_parentheses(*prompt, shell);
}
