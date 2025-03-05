/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_matcher.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 10:04:22 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/27 13:03:36 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	debug_context(int context)
{
	if (context == WILD_ALL)
		printf("wild_all\n");
	if (context == WILD_START)
		printf("wild_start\n");
	if (context == WILD_END)
		printf("wild_end\n");
	if (context == WILD_MIDDLE)
		printf("wild_middle\n");
	if (context == WILD_BOTH)
		printf("wild_both\n");
	if (context == WILD_MIXED)
		printf("wild_mixed\n");
}

int	get_comp_context(char *to_find)
{
	int	context;
	int	length;
	int	occurences;

	if (!to_find)
		return (-1);
	occurences = ft_count_char(to_find, '*');
	length = ft_strlen(to_find) - 1;
	context = 0;
	if (to_find[0] == '*' && length + 1 == 1)
		context = WILD_ALL;
	else if (to_find[0] == '*' && to_find[length] != '*')
		context = WILD_START;
	else if (to_find[0] != '*' && to_find[length] == '*')
		context = WILD_END;
	else if (to_find[0] != '*' && to_find[length] != '*' && find_index('*',
			to_find) > 0)
		context = WILD_MIDDLE;
	else if (to_find[0] == '*' && to_find[length] == '*')
		context = WILD_BOTH;
	if (occurences > 1 && context != WILD_BOTH)
		context = WILD_MIXED;
	return (context);
}

char	*wild_all(char *to_expand, char *to_check)
{
	(void)to_expand;
	return (ft_strdup(to_check));
}

char	*ft_wild_matcher(char *to_expand, char *to_check, int ctx)
{
	static char	*(*match[])(char *to_expand, char *to_check) = {wild_start,
		wild_end, wild_middle, wild_both, wild_mixed, wild_all};

	return (match[ctx](to_expand, to_check));
}
