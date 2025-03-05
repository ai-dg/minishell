/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 09:50:10 by calbor-p          #+#    #+#             */
/*   Updated: 2024/07/01 12:04:44 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include "colors.h"
# include "libft/libft.h"
# include "minishell.h"
# include <ctype.h>
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <unistd.h>

extern volatile sig_atomic_t	g_receipt;

typedef struct t_to_exec
{
	char						*command;
	char						*redirection;
	char						*equal;
	char						*question;
	char						*dollar;
	char						*args;
}								t_to_exec;

typedef enum s_res
{
	RES_INIT,
	RES_OK,
	RES_KO
}								t_res;

typedef enum s_node_mode
{
	DELETE,
	EXTRACT
}								t_node_mode;

typedef struct s_parser
{
	int							*total_args;
	int							*len_words;
	char						**words;
	int							*start;
}								t_parser;

typedef struct s_env
{
	char						*key;
	char						*value;
	bool						aff;
	struct s_env				*next;
	struct s_env				*prev;
}								t_env;

typedef enum s_quote_status
{
	QUOTE_CLOSED,
	QUOTE_OPEN
}								t_quote_status;

typedef struct s_qchecker
{
	t_quote_status				s_status;
	t_quote_status				d_status;
	char						to_close;
	bool						pending;
}								t_qchecker;

typedef struct s_var_expander
{
	char						*final;
	char						*cpy;
	int							occurences;
	char						*to_expand;
	char						*replaced;
	int							length;
	int							index;
	int							next;
	int							trim_space;
}								t_var_ex;

typedef enum s_token_type
{
	REDIR_IN,
	REDIR_OUT,
	DBLE_REDIR_IN,
	DBLE_REDIR_OUT,
	DOLLAR_IN,
	PATH_INFILE,
	PATH_OUTFILE,
	VARIABLE,
	CMD,
	ARG,
	DELIMITER,
	NO_TYPE,
	APPEND_REDIR_OUT,
}								t_token_type;

typedef struct s_parsing_values
{
	int							i;
	int							y;
	int							in_args;
	int							count;
	int							len;
	int							quote;
}								t_parsing_values;

typedef struct s_smart_remove_values
{
	int							i;
	int							j;
	bool						in_double_quote;
	bool						in_single_quote;
	char						indicator_double;
	char						indicator_single;
	char						indicator_dollar;
	int							len;
}								t_smart_remove_values;

typedef struct s_echo_values
{
	int							i;
	bool						skip;
	bool						ignore;
	bool						write_in_fd;
	int							fd_output;
	int							fd_input;
}								t_echo_values;

typedef struct s_special_bar
{
	char						*tmp;
	int							j;
	char						single_quote;
	bool						close_it;
	int							position_of_str;
	size_t						prompt_len;
	size_t						i;
	int							k;
}								t_special_bar;

typedef struct s_reduce_half_of_bars
{
	int							i;
	int							j;
	int							k;
	int							len;
	bool						odd;
	char						*tmp;
	int							count;
	int							to_copy;
}								t_reduce_half_of_bars;

typedef struct s_write_prompt
{
	int							i;
	bool						found_bars;
	bool						let_it_pass;
	int							nbr_consecutives_bars;
	int							nbr_consecutives_vertical_bars;
	int							count;
	char						*here_doc;
}								t_write_prompt;

typedef struct s_write_in_here_doc
{
	char						*line;
	char						*tester;
	int							i;
	bool						error;
	bool						in_signals;
	int							position;
	char						*line_to_history;
	char						*delimiter;
	size_t						lenght;
	size_t						current_length;
	size_t						new_size;
	char						*msg;
	char						*line_to_print;
}								t_write_in_here_doc;

typedef struct s_find_error_case_syntax
{
	int							position;
	bool						alpha;
	int							number_special;
	int							count_consecutive;
	char						opposite_redir;
	int							count_consecutive_after_redir;
	int							j;
	int							i;
	int							count_consecutive_after;
}								t_find_error_case_syntax;

typedef struct s_print_error_values
{
	const char					*prefix;
	size_t						prefix_len;
	size_t						var_len;
	size_t						msg_len;
	size_t						total_len;
	char						*error_msg;
}								t_print_error_values;

typedef struct s_history_values
{
	int							fd;
	char						*history;
	char						buffer[BUFFER_SIZE + 1];
	int							reads;
	char						*path;
	char						*new_history;
}								t_history_values;

typedef struct s_rewrite_history
{
	int							fd;
	char						*path;
	char						*history;
	int							history_size;
	int							to_pass;
	int							i;
}								t_rewrite_history;

typedef struct s_wild
{
	char						*path;
	char						*expanded;
	char						**expands;
	char						*temp;
	DIR							*check;
	struct dirent				*into_dir;
	int							i;
	int							context;
}								t_wild;

typedef struct s_smart_decode
{
	char						replace_dble;
	char						replace_sple;
	unsigned char				space_rple;
	unsigned char				sple_quote;
	unsigned char				dollar;
}								t_smart_decode;

typedef struct s_readline_parenth
{
	int							i;
	int							j;
	char						*read;
	int							to_find;
	int							count_close;
	int							current_length;
	int							new_size;
	char						*new_prompt;
}								t_readline_parenth;

typedef struct s_token
{
	char						*value;
	t_token_type				type;
	struct s_token				*next;
	struct s_token				*prev;
}								t_token;

typedef struct s_cmd
{
	pid_t						pid;
	int							index;
	char						*cmd;
	int							len_args;
	char						**args;
	char						*delimiter;
	char						**path_infiles;
	char						**path_outfiles;
	char						**path_append_outfiles;
	char						**variables;
	char						**delimiter_var;
	t_token						*tokens;
	int							output_result;
	int							input_result;
	int							exit_status;
	bool						in_parentheses;
	char						*p_execute;
	struct s_cmd				*next;
	struct s_cmd				*prev;
}								t_cmd;

typedef struct s_file_descriptors
{
	int							*input;
	int							*output;
	struct s_file_descriptors	*next;
	struct s_file_descriptors	*prev;
}								t_fds;

typedef struct s_pipefd
{
	int							*values;
	struct s_pipefd				*next;
	struct s_pipefd				*prev;
}								t_pipefd;

typedef struct s_exec_unit
{
	int							type;
	char						*prompt;
	struct s_exec_unit			*l_unit;
	struct s_exec_unit			*r_unit;
	struct s_exec_unit			*p_unit;
}								t_exec_unit;

typedef struct s_smart_token
{
	int							index;
	int							index_and;
	int							index_or;
	char						*extract;
	char						*remain_str;
}								t_smart_token;

typedef struct s_remove_input_output
{
	t_token						*current_token;
	int							i;
	int							j;
	int							k;
}								t_remove_input_output;

typedef struct s_shell_data
{
	int							cd_error;
	t_cmd						*pipe;
	int							total_pipes;
	pid_t						*pid_list;
	int							i;
	bool						exist_cmd;
	int							input;
	int							output;
	int							exit_status;
	int							exit_status1;
	int							exit_status2;
	int							output_result;
	bool						in_exe_cmd;
	t_env						*alias;
	t_env						*env;
	t_env						*session;
	char						**parsed;
	struct termios				old;
	struct termios				terminal;
	int							argc;
	char						**initial_parsed;
	int							pipefd[2];
	int							pipefd_2[2];
	pid_t						pid;
	pid_t						pid_current;
	int							status;
	char						**paths;
	int							first_message;
	int							ac;
	char						**av;
	char						**env_char;
	char						**sys_env;
	char						*prompt;
	char						*pline;
	char						*prompt_in;
	char						*prompt_cmd;
	t_pipefd					*pipefd1;
	t_fds						*fds;
	bool						dollar_expansion;
	bool						dollar_expansion_trim;
	bool						echo_in_pipe;
	bool						echo_in_variable;
	bool						in_env_cmd;
	bool						in_env_cmd_error;
	bool						just_one_pipe;
	bool						in_child_process;
	int							input_result;
	bool						in_script;
	char						*file_script;
	int							number_line;
	int							number_line_here_docs;
	char						*line;
	char						**lines_char;
	int							x;
	int							y;
	int							z;
	int							fd;
	int							g_receipt;
	int							debug_count;
	int							debug_mode;
	int							last_status;
	bool						in_parentheses;
	int							fds_parenthese[2];
	t_exec_unit					*exec_units;
	t_exec_unit					*exec_units2;
	char						*home;
	int							*to_expand_in_doc;
	int							count_in_doc;
	bool						in_path_null;
	int							shell_level;
	bool						error_in_readline;
	int							output_to_change;
	int							exit_signals;
	int							exit_signals2;
	int							fd_in_child;
	int							fd_out_child;
	int							i_pipes;
	bool						in_here_doc;
	bool						write_in_here_doc;
	char						*tmp_history;
	int							mode;
	// char						*here_doc_once;
	int							fd_null[2];
}								t_shell_data;

typedef struct s_prompt
{
	char						*line;
	char						*cwd;
	char						*pwd;
	char						*path;
	char						*log;
	bool						filter;
	char						**hst;
	char						host[255];
}								t_prompt;

typedef struct s_tree
{
	t_token						*token;
	struct s_tree				*ltree;
	struct s_tree				*rtree;
	struct s_tree				*ptree;
}								t_tree;

typedef struct s_shell_level
{
	int							fd;
	int							number;
	char						buffer[16];
	ssize_t						bytes_read;
	char						number_str[16];
	int							length;
	int							temp_number;
	char						temp;
}								t_shell_level;

#endif