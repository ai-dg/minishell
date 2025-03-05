/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:13:16 by dagudelo          #+#    #+#             */
/*   Updated: 2024/06/20 14:25:04 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

char	*ft_getenv(const char *name, t_shell_data *shell)
{
	t_env	*tmp;
	char	*env_name;
	char	*env_value;

	tmp = shell->env;
	while (tmp)
	{
		env_name = tmp->key;
		env_value = tmp->value;
		if (ft_strcmp(env_name, (char *)name) == 0)
			return (env_value);
		tmp = tmp->next;
	}
	return (NULL);
}
