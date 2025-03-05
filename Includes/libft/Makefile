# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/16 19:03:33 by calbor-p          #+#    #+#              #
#    Updated: 2024/06/25 12:26:45 by dagudelo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES = arrays.c ft_atoi.c ft_atoll.c ft_bzero.c ft_calloc.c ft_clear_splitted.c ft_convert_base.c ft_convert_base2.c \
          ft_count_char.c ft_drop.c ft_dup_chars.c ft_fflush.c ft_fileno.c ft_filter.c ft_fprintf.c ft_found_char.c \
          ft_fstrjoin.c ft_get_hostname.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_is_binary_file.c ft_isdigit.c \
          ft_is_same_letter.c ft_isprint.c ft_itoa.c ft_join_splitted.c ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c \
          ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c ft_lstmap_bonus.c ft_lstnew_bonus.c \
          ft_lstsize_bonus.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_printf.c ft_putchar.c \
          ft_putchar_fd.c ft_put_chars_to_array.c ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c \
          ft_realloc.c ft_reset_buffer.c ft_sort_array_ci.c ft_sort_array_cs.c ft_split.c ft_split_key_val.c \
          ft_strcat.c ft_strchr.c ft_strcmp.c ft_strcpy.c ft_strcspn.c ft_strdup.c ft_striteri.c ft_strjoin.c \
          ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strsstr.c \
          ft_strstr.c ft_strtrim.c ft_substr.c ft_swap_chars.c ft_tolower.c ft_toogle.c ft_toupper.c get_next_line.c \
          get_next_line_utils.c handler_hex.c handler_numb.c handler_params.c handler_txt.c handler_write.c malloc_tools.c \
          params.c reset_buf.c rules_hex.c rules_int.c rules_str.c rules_u.c string_lengths.c string_utils.c utils.c

OBJECTS = $(SOURCES:.c=.o)

BONUSSRC = ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c \
           ft_lstiter_bonus.c ft_lstlast_bonus.c ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c

BONUSOBJ = $(BONUSSRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror 
NAME = libft.a

all : $(NAME)

$(NAME) : $(OBJECTS)
	ar -crs $(NAME) $(OBJECTS)

$(OBJECTS) : $(SOURCES) 
	$(CC) $(CFLAGS) -c $(SOURCES)

bonus : $(BONUSSRC) $(NAME)
	$(CC) $(CFLAGS) -c $(BONUSSRC)
	ar -rs $(NAME) $(BONUSOBJ)

.PHONY : clean fclean re bonus

clean : 
	rm -rf $(OBJECTS) $(BONUSOBJ)

fclean : clean
	rm -rf $(NAME)

re :  fclean all
