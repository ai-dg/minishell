/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc_prompt_read_and.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 08:12:58 by ls                #+#    #+#             */
/*   Updated: 2024/06/26 07:57:05 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

/*static void	init_read_and(t_readline_parenth *read)
{
	read->i = 0;
	read->j = 0;
	read->read = NULL;
	read->to_find = 0;
	read->count_close = 0;
	read->current_length = 0;
	read->new_size = 0;
	read->new_prompt = NULL;
}*/

static void	count_len_and_realloc(t_readline_parenth *read)
{
	read->current_length = ft_strlen(read->new_prompt);
	read->new_size = read->current_length + ft_strlen(read->read) + 2;
	read->new_prompt = ft_realloc(read->new_prompt, read->new_size);
}

static void	fill_new_prompt_values(t_readline_parenth *read)
{
	if (ft_strncmp(read->read, "&", 1) != 0)
	{
		ft_strcat(read->new_prompt + read->current_length, read->read);
	}
	else
	{
		ft_strcat(read->new_prompt + read->current_length, " ");
		ft_strcat(read->new_prompt + read->current_length + 1, read->read);
	}
}

static void	exit_signal_case(t_readline_parenth *read, t_shell_data *shell)
{
	free_variable((void **)&read->new_prompt);
	free_variable((void **)&shell->prompt);
	shell->prompt = ft_strdup("");
	read->new_prompt = ft_strdup("");
	g_receipt = 0;
	reopen_stdin_if_needed();
}

static void	main_loop(char **prompt, t_readline_parenth *read,
		t_shell_data *shell)
{
	(void)prompt;
	while (1)
	{
		read->read = readline("> ");
		if (read->read == NULL && g_receipt == SIGINT)
		{
			exit_signal_case(read, shell);
			break ;
		}
		if_read_is_null(&read->new_prompt, &read->read, shell);
		if (read->read[0] != '\0' && read->read[0] != '\n')
		{
			count_len_and_realloc(read);
			if (!read->new_prompt)
				exit_1_malloc(&shell);
			fill_new_prompt_values(read);
		}
		if (read->read[ft_strlen(read->read) - 2] != '&'
			&& read->read[ft_strlen(read->read) - 3] != '&')
			break ;
		free_variable((void **)&read->read);
	}
}

char	*handle_and_readline(char *prompt, t_shell_data *shell)
{
	t_readline_parenth	read;

	read.i = 0;
	read.j = 0;
	read.read = NULL;
	read.to_find = 0;
	read.count_close = 0;
	read.current_length = 0;
	read.new_size = 0;
	read.new_prompt = NULL;
	init_signals_alt(shell);
	read.new_prompt = ft_strdup(prompt);
	if (!read.new_prompt)
		exit_1_malloc(&shell);
	main_loop(&prompt, &read, shell);
	init_signals(shell);
	return (read.new_prompt);
}
