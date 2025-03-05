/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_variable_exist.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 22:11:14 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/24 13:07:07 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

char	*create_initial_result(char *str)
{
	char	*result;

	result = ft_strdup(str);
	if (result == NULL)
	{
		printf("minishell: error: failed to allocate memory\n");
		return (NULL);
	}
	return (result);
}

char	*append_and_check(char *result, char *read, char delimiter)
{
	char	*temp;

	temp = ft_fstrjoin(result, read, NONE);
	if (temp == NULL)
	{
		printf("minishell: error: failed to join strings\n");
		free_variable((void **)&read);
		free_variable((void **)&result);
		return (NULL);
	}
	free_variable((void **)&result);
	if (ft_strchr(read, delimiter) != NULL)
	{
		free_variable((void **)&read);
		return (temp);
	}
	free_variable((void **)&read);
	return (temp);
}

int	variable_exists(char *var, t_shell_data *shell)
{
	char	*expanded;
	int		exists;

	expanded = expand_variable(var, shell);
	exists = (expanded != NULL && ft_strlen(expanded) > 0);
	if (expanded)
	{
		free_variable((void **)&expanded);
	}
	return (exists);
}
