/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc_prompt_tools.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:04:18 by dagudelo          #+#    #+#             */
/*   Updated: 2024/06/26 17:00:37 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	init_write(t_write_prompt *write)
{
	write->i = 0;
	write->found_bars = false;
	write->let_it_pass = true;
	write->nbr_consecutives_bars = 0;
	write->nbr_consecutives_vertical_bars = 0;
	write->count = 0;
	write->here_doc = NULL;
}

void	remove_backslashes(char *str)
{
	int	len;
	int	i;
	int	j;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] != '\\')
		{
			str[j] = str[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
}

void	if_read_is_null(char **result, char **read, t_shell_data *shell)
{
	(void)shell;
	(void)result;
	if (*read == NULL)
	{
		printf("minishell: syntax error: unexpected end of file\n");
		printf("exit\n");
		if (*result)
			free_variable((void **)&*result);
		free_malloc_exit_system(&shell);
		exit(2);
	}
}

bool	is_printable_but_no_bar(char c)
{
	if ((c > 32 && c < 127) && c != '|' && c != '\\')
		return (true);
	return (false);
}

bool	nothing_after_bars(char *prompt)
{
	int	i;

	i = 0;
	while (prompt[i])
		i++;
	while (prompt[i] && i >= 0)
	{
		if (prompt[i] > 32 && prompt[i] < 127)
		{
			if (prompt[i] == '|' || prompt[i] == '\\')
				return (true);
			else
				return (false);
		}
		i--;
	}
	return (true);
}
