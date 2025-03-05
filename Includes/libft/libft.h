/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:47:16 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/19 19:57:02 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include "get_next_line.h"
# include "stdio.h"
# include <limits.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# ifndef FREEMODES
#  define FREEMODES

#  define NONE 0
#  define FIRST 1
#  define SECOND 2
#  define BOTH 3
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_offsets
{
	int				b_space;
	int				a_space;
	int				precision;
	int				length;
	int				s_length;
	int				blank;
	int				nbr;
	long long		llnbr;
	char			c;
}					t_offsets;

t_offsets			extract_params(char *params);

int					handle_char(va_list args, char *params);
int					handle_string(va_list args, char *params);
int					handle_int(va_list args, char *params);
int					handle_pointer(va_list args, char *params);
int					handle_unsigned(va_list args, char *params);
int					handle_hexlower(va_list args, char *params);
int					handle_hexupper(va_list args, char *params);
int					handle_percent(va_list args, char *params);
int					ft_printf(const char *str, ...);
void				ft_putchar(char c);
void				ft_putnbr(int nb);
int					count_digits_from_nb(long long int nb, bool count_sign);
int					ft_printhex(long long int lnbr, int start, char *base);
int					print_char(int nb, char c);
int					extract_number(char *params);
int					count_digits(char *params);
int					is_in_array(char c, char *params);
int					check_zero_rule_i(t_offsets off, int reads, int nbr,
						char *params);
int					find_index(char c, char *params);
int					count_digits_from_hex(long long int lnbr, int start);
int					write_number(long nb, bool print_sign);
int					write_char(char c);
int					write_str(char *str);
int					sharp_rule(t_offsets off, int reads, char *params);
int					check_space_rule_i(t_offsets off, int reads, int nbr,
						char *params);
int					check_plus_rule_i(int nbr, char *params);
int					check_minus_rule_hex(t_offsets off, int reads, char *params,
						char *base);
int					check_zero_rule_hex(t_offsets off, int reads, char *params);
int					check_dot_rule_hex(t_offsets off, int reads, char *params);
int					write_nstr(char *str, int len);
int					get_argslength(const char *str, char tests[9]);
int					handle_params_int(char *params, int i, int reads,
						t_offsets off);
int					handle_params_uint(char *params, unsigned int i, int reads,
						t_offsets off);
int					count_digits_from_uint(unsigned int nb);
int					check_zero_rule_u(t_offsets off, int reads, int nbr,
						char *params);
int					check_space_rule_u(t_offsets off, int reads, int nbr,
						char *params);
int					check_zero_rule_str(t_offsets off, int reads, char *params);
int					check_minus_rule_str(t_offsets off, int reads,
						char *params);
int					check_space_rule_str(t_offsets off, int reads,
						char *params);
int					check_dot_rule_str(t_offsets off, int reads, char *str,
						char *params);

/* Fonctions de la libc*/

char				*ft_strcpy(char *dest, char *src);
char				*ft_strrstr(char *str, char *to_find);
char				*ft_fstrjoin(char *s1, char *s2, int freemode);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(char c);
char				*ft_filter(char *tofilter, char toskip);
size_t				count_word(char const *s, char c);
size_t				ft_strlen(const char *s);
void				ft_putstr(char *str);
void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
int					ft_strcmp(char *s1, char *s2);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_ftoa(float n, int precision);
char				*ft_to_lower_case(char *str);
char				*ft_to_upper_case(char *str);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strncmp_backward(const char *s1, const char *s2,
						size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t n);
int					ft_atoi(const char *nptr);
void				*ft_calloc(size_t nmemb, size_t size);
void				*ft_realloc(void *ptr, size_t size);
char				*ft_strdup(const char *s);
/* Fonctions supplementaires*/
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
char				*ft_convert_base(char *nbr, char *base_from, char *base_to);
char				*check_base(char *base, char *check);
int					check_error(char *base);
int					in_base(char *base, char c, int *getindex);
long				get_number(char *str, char *base);
long				ft_atoi_base(char *str, char *base);
char				**ft_split_key_val(char const *s, char c);
char				*ft_strcpy(char *dest, char *src);
/* Fonctions bonus*/
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

char				*ft_strstr(char *str, char *to_find);
bool				ft_found_char(char *str, int c);

//	strings utils
char				*reset_buf(char *buf, int length);
bool				is_strlen_within_range(char *str, int min, int max);
bool				is_strlen_greater_than(char *str, int max);
bool				is_strlen_at_least(char *str, int min);
bool				is_strlen_within(char *str, int max);
bool				is_strlen_equal_to(char *str, int nb);
bool				is_strictly_alternating(char *str, char c1, char c2);
bool				is_strictly_alternating_within(char *str, char c1, char c2,
						int max);
int					ft_strcspn(const char *str1, const char *str2);
char				*ft_join_splitted(char **splitted, char *separator);
int					ft_count_args(char **args);
void				ft_clear_splitted(char **splitted);
int					find_isolated(char c, char *params);
long long int		ft_atoll(const char *nptr);
char				*ft_join_nsplitted(char **splitted, char *c, int n);
char				*ft_strcat(char *dest, const char *src);
void				free_array(char ***array);
void				free_variable(void **ptr);
int					ft_fprintf(FILE *stream, const char *format, ...);
int					ft_fflush(FILE *stream);
int					ft_fileno(FILE *stream);
void				ft_drop(void);
char				**ft_dup_chars(char **from, char **to);
char				**ft_push_chars_to_array(char **array, char *to_add);
int					ft_count_char(char *str, char c);
bool				ft_is_same_letter(char a, char b);
int					ft_gethostname(char *buff, int buffer_size);
void				ft_reset_buffer(char *buff, int buffer_size);
void				ft_sort_array_cs(char **array);
void				ft_sort_array_ci(char **array);
void				ft_swap_chars(char **str1, char **str2);
bool				ft_is_binary_file(char *path);
bool				ft_toogle(bool value);
int					find_dollar_index(char c, char *params);
bool				ft_strsstr(char *str, char **strs);
int					compare_ci(char *str1, char *str2);

#endif
