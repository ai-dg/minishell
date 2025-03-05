/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc_prompt_readline.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:04:18 by dagudelo          #+#    #+#             */
/*   Updated: 2024/06/26 11:13:30 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static void	fill_result(char **result, char **read, char **temp, int *len)
{
	free_variable((void **)&*result);
	*result = *temp;
	*len = ft_strlen(*read);
}

static int	is_string_only_spaces(const char *str)
{
	while (*str)
	{
		if (!isspace((unsigned char)*str))
			return (0);
		str++;
	}
	return (1);
}

static bool	initial_case_conditions(char **read, char **temp, char **result,
		t_shell_data **shell)
{
	*read = readline("> ");
	if (*read == NULL && g_receipt == SIGINT)
	{
		free_variable((void **)&*result);
		free_variable((void **)&*read);
		(*shell)->error_in_readline = true;
		g_receipt = 0;
		reopen_stdin_if_needed();
		return (true);
	}
	if_read_is_null(result, read, *shell);
	*temp = ft_fstrjoin(*result, *read, NONE);
	if (*temp == NULL)
	{
		free_variable((void **)&*read);
		free_variable((void **)&*result);
		return (true);
	}
	return (false);
}

static void	put_on_readline(char **read, char **temp, char **result,
		t_shell_data **shell)
{
	int		len;
	bool	result_bool;

	len = 0;
	result_bool = false;
	init_signals_alt(*shell);
	while (1)
	{
		result_bool = initial_case_conditions(read, temp, result, shell);
		if (result_bool == true)
			break ;
		fill_result(result, read, temp, &len);
		if (len > 0 && (*read)[len - 1] == '|' && !is_string_only_spaces(*read))
		{
			free_variable((void **)&*read);
			continue ;
		}
		if (*read[0] != 0 && *read[0] != 32)
		{
			free_variable((void **)&*read);
			break ;
		}
		free_variable((void **)&*read);
	}
	init_signals(*shell);
}

char	*prompt_to_here_doc(char *prompt, t_shell_data *shell)
{
	char	delimiter;
	int		i;
	char	*read;
	char	*result;
	char	*temp;

	i = 0;
	read = NULL;
	temp = NULL;
	result = NULL;
	while (prompt[i])
		i++;
	delimiter = prompt[i - 1];
	result = ft_strdup("");
	if (result == NULL)
		return (NULL);
	if (delimiter == 0x7C)
	{
		put_on_readline(&read, &temp, &result, &shell);
		if (temp == NULL)
			return (NULL);
	}
	return (result);
}
