/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls <ls@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:33:04 by calbor-p          #+#    #+#             */
/*   Updated: 2024/04/29 22:14:50 by ls               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

/*
[4;XXm : souligné
[7;XXm : fond
[9;XXm : barré
*/
# define GREY "\001\033[30m\002"
# define BOLD_GREY "\001\033[1;30m\002"
# define UNDER_GREY "\001\033[4;30m\002"
# define BG_GREY "\001\033[40m\002"

# define RED "\001\033[31m\002"
# define BOLD_RED "\001\033[1;31m\002"
# define UNDER_RED "\001\033[4;31m\002"
# define BG_RED "\001\033[41m\002"

# define GREEN "\001\033[32m\002"
# define BOLD_GREEN "\001\033[1;32m\002"
# define UNDER_GREEN "\001\033[4;32m\002"
# define BG_GREEN "\001\033[42m\002"

# define YELLOW "\001\033[33m\002"
# define BOLD_YELLOW "\001\033[1;33m\002"
# define UNDER_YELLOW "\001\033[4;33m\002"
# define BG_YELLOW "\001\033[43m\002"

# define BLUE "\001\033[34m\002"
# define BOLD_BLUE "\001\033[1;34m\002"
# define UNDER_BLUE "\001\033[4;1;34m\002"
# define BG_BLUE "\001\033[44m\002"

# define VIOLET "\001\033[35m\002"
# define BOLD_VIOLET "\001\033[1;35m\002"
# define UNDER_VIOLET "\001\033[4;35m\002"
# define BG_VIOLET "\001\033[45m\002"

# define TURQUOISE "\001\033[36m\002"
# define BOLD_TURQUOISE "\001\033[1;36m\002"
# define UNDER_TURQUOISE "\001\033[4;36m\002"
# define BG_TURQUOISE "\001\033[46m\002"

# define WHITE "\001\033[37m\002"
# define BOLD_WHITE "\001\033[1;37m\002"
# define UNDER_WHITE "\001\033[4;37m\002"
# define BG_WHITE "\001\033[47m\002"

# define RESET "\001\033[0m\002"
# define RESET_FINAL "\001\033[0m\002\0"

# define BLINK "\001\033[5;35m\002"
#endif