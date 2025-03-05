/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 08:53:02 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/24 16:40:46 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

char	*check_and_filter(char *str, t_shell_data *shell)
{
	char	**key_val;
	char	*new_str;

	new_str = NULL;
	if (!str)
		return (NULL);
	if (!ft_strchr(str, '"') && !ft_strchr(str, '\''))
		return (str);
	key_val = ft_split_key_val(str, '=');
	if (!key_val)
		exit_1_malloc(&shell);
	if ((key_val[0][0] == '"' && key_val[0][ft_strlen(key_val[0]) - 1] == '"')
		|| (key_val[0][0] == '\'' && key_val[0][ft_strlen(key_val[0])
			- 1] == '\''))
	{
		key_val[0][0] = ' ';
		key_val[0][ft_strlen(key_val[0]) - 1] = ' ';
		ft_unallocated_trim(key_val[0]);
		new_str = ft_fstrjoin(key_val[0], "=", NONE);
		new_str = ft_fstrjoin(new_str, key_val[1], FIRST);
		return (free_array(&key_val), free_variable((void **)&str), new_str);
	}
	return (free_array(&key_val), str);
}
