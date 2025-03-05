/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens_get_files.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:01:51 by dagudelo          #+#    #+#             */
/*   Updated: 2024/06/24 16:40:46 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static void	copy_path_files(t_token *current, char **files, int *i,
		t_token_type type)
{
	while (current)
	{
		if (current->type == type)
		{
			files[*i] = ft_strdup(current->value);
			(*i)++;
		}
		current = current->next;
	}
	files[*i] = NULL;
}

char	**get_path_files(t_token *token, t_cmd *pipe, t_token_type type,
		t_shell_data *shell)
{
	t_token	*current;
	char	**files;
	int		i;

	(void)pipe;
	current = token;
	i = 0;
	while (current)
	{
		if (current->type == type)
			i++;
		current = current->next;
	}
	files = (char **)malloc(sizeof(char *) * (i + 1));
	if (!files)
		exit_1_malloc(&shell);
	if (i == 0)
	{
		files[0] = NULL;
		return (files);
	}
	current = token;
	i = 0;
	copy_path_files(current, files, &i, type);
	return (files);
}
