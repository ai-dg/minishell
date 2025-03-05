/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_rewrite.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:07:59 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/18 15:22:41 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static void	init_rewrite_history(t_rewrite_history *rewrite)
{
	rewrite->path = get_history_path();
	rewrite->history = get_all_history();
	rewrite->history_size = check_historic_lines();
	rewrite->to_pass = 0;
	rewrite->i = 0;
	rewrite->fd = open(rewrite->path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
}

int	rewrite_history(void)
{
	t_rewrite_history	rewrite;

	init_rewrite_history(&rewrite);
	if (rewrite.fd < 0)
	{
		free_variable((void **)&rewrite.history);
		return (free_variable((void **)&rewrite.path), -1);
	}
	write(rewrite.fd, rewrite.history, ft_strlen(rewrite.history));
	free_variable((void **)&rewrite.history);
	return (close(rewrite.fd), free_variable((void **)&rewrite.path), 0);
}
