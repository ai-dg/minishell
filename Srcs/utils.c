/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 11:23:24 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/24 16:40:46 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

char	*cpy(char *src, char *dest)
{
	while (*src)
		*dest++ = *src++;
	return (dest);
}

char	*pass_str(char *to_pass, char *str)
{
	char	*res;
	int		i;

	i = 0;
	while (to_pass[i] && str[i] && to_pass[i] == str[i])
		i++;
	res = ft_strdup(&str[i]);
	free_variable((void **)&str);
	return (res);
}

char	*ft_strjoin_with_space_and_free(char *s1, char *s2, t_shell_data *shell)
{
	char	*res;
	int		t_len;

	if (!s1 || !s2)
		return (NULL);
	t_len = (int)ft_strlen(s1) + (int)ft_strlen(s2);
	if (t_len < 1)
	{
		res = malloc(sizeof(char) * 1);
		if (!res)
			exit_1_malloc(&shell);
		res[0] = '\0';
		return (res);
	}
	else
		res = malloc(sizeof(char) * (t_len + 2));
	if (!res)
		exit_1_malloc(&shell);
	res = cpy(s1, res);
	*res++ = ' ';
	res = cpy(s2, res);
	return (*res = 0, free_variable((void **)&s1), res - t_len - 1);
}

char	*ft_strjoin_and_free(char *s1, char *s2, t_shell_data *shell)
{
	char	*res;
	int		t_len;

	if (!s1 || !s2)
		return (NULL);
	t_len = (int)ft_strlen(s1) + (int)ft_strlen(s2);
	if (t_len < 1)
	{
		res = malloc(sizeof(char) * 1);
		if (!res)
			exit_1_malloc(&shell);
		res[0] = '\0';
		return (res);
	}
	else
		res = malloc(sizeof(char) * (t_len + 2));
	if (!res)
		exit_1_malloc(&shell);
	res = cpy(s1, res);
	res = cpy(s2, res);
	return (*res = 0, free_variable((void **)&s1), res - t_len);
}
