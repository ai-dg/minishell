/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 22:11:14 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/24 16:40:46 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	count_words(char *str)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	if (str == NULL || str[0] == '\0')
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && (i == 0 || str[i - 1] == ' '))
			words++;
		i++;
	}
	return (words);
}

char	*hard_remove_quotes(char *word, t_shell_data *shell)
{
	char	*replaced;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!word)
		return (word);
	replaced = malloc((ft_strlen(word) + 1) * sizeof(char));
	if (!replaced)
		exit_1_malloc(&shell);
	reset_buf(replaced, ft_strlen(word) + 1);
	while (word[i])
	{
		if ((word[i] != '\'' || word[i] != '"') && ft_isprint(word[i]))
		{
			replaced[j] = word[i];
			j++;
		}
		i++;
	}
	replaced[j] = '\0';
	return (replaced);
}

void	remove_quotes(char *word)
{
	size_t	len;
	size_t	i;
	size_t	j;

	if (word == NULL)
		return ;
	len = ft_strlen(word);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (word[i] != '\'' && word[i] != '\"')
		{
			word[j++] = word[i];
		}
		i++;
	}
	word[j] = '\0';
}

void	free_malloc_split(char **dest)
{
	int	i;

	if (dest == NULL)
		return ;
	i = 0;
	while (dest[i])
	{
		free_variable((void **)&dest[i]);
		i++;
	}
	free_variable((void **)&dest[i]);
	free_variable((void **)&dest);
	dest = NULL;
}
