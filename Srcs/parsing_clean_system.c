/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_clean_system.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 22:11:14 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/19 13:29:35 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	remove_word(char ***words, int index, t_shell_data *shell)
{
	(void)shell;
	if (!words || !(*words) || index < 0)
		return ;
	free_variable((void **)&(*words)[index]);
	while ((*words)[index + 1] != NULL)
	{
		(*words)[index] = (*words)[index + 1];
		index++;
	}
	(*words)[index] = NULL;
}

void	check_and_remove_nonexistent_vars(char ***words, t_shell_data *shell)
{
	int	i;

	(void)shell;
	i = 0;
	while ((*words)[i])
	{
		if ((*words)[i] && (*words)[i][0] == '$')
		{
			if (i < 2 && !variable_exists((*words)[i], shell))
			{
				remove_word(words, i, shell);
				i--;
			}
			if (i >= 2 && !variable_exists((*words)[i], shell)
				&& ft_strncmp((*words)[i - 1], "<", 1) != 0
				&& ft_strncmp((*words)[i - 2], "<", 1) != 0)
			{
				remove_word(words, i, shell);
				i--;
			}
		}
		i++;
	}
}

void	remove_dollar_and_quotes(char **words)
{
	char	quote;
	int		len;
	int		i;

	i = 0;
	while (words[i] != NULL)
	{
		if (words[i][0] == '$' && (words[i][1] == '\'' || words[i][1] == '"'))
		{
			quote = words[i][1];
			len = ft_strlen(words[i]);
			if (words[i][len - 1] == quote)
			{
				ft_memmove(words[i], words[i] + 2, len - 2);
				words[i][len - 3] = '\0';
			}
		}
		i++;
	}
}

void	print_string(const char *str)
{
	while (*str)
	{
		if (isprint((unsigned char)*str))
			printf("%c", *str);
		else
			printf("|0x%02X|", (unsigned char)*str);
		str++;
	}
	printf("\n");
}

char	*remove_spaces_before_after_word(char *str)
{
	char	*start;
	char	*end;

	if (!str)
		return (NULL);
	start = str;
	while (*start && isspace((unsigned char)*start))
	{
		start++;
	}
	end = start + ft_strlen(start);
	while (end > start && isspace((unsigned char)*(end - 1)))
	{
		end--;
	}
	*end = '\0';
	if (start > str)
	{
		ft_memmove(str, start, end - start + 1);
	}
	return (str);
}
