/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 22:12:37 by calbor-p          #+#    #+#             */
/*   Updated: 2024/07/01 12:48:01 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "colors.h"
# include "data.h"
# include "libft/libft.h"
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

# define WILD_START 0
# define WILD_END 1
# define WILD_MIDDLE 2
# define WILD_BOTH 3
# define WILD_MIXED 4
# define WILD_ALL 5
# define ONLY_DIRECTORIES 0
# define ALL_TYPES 1
# define BUFFER_SIZE 1024
# define PROD 1
# define DEV 2
# define EPF "%s\n"
# define IS_A_BRANCH 0
# define IS_A_LEAF 1
# define AND_WAIT 2
# define OR_WAIT 3
# define IS_DONE 4
# define VERBOSE 1
# define SILENT 0
# define REMOVE 0
# define REPLACE 1
# define CHECK_PARENTHESIS 0
# define SKIP_PARENTHESIS 1

/**
 * @file alias_expander.c
 *
 */

char			*expand_alias(t_shell_data *shell, char *key);
char			*expand_aliases(char *prompt, t_shell_data *shell);

/**
 * @file alias.c
 *
 */

int				add_alias(t_shell_data *shell, char **inst);
int				alias_m(t_shell_data *shell, char **inst);

/**
 * @file cd_go_home.c
 *
 */

int				go_home(t_shell_data *shell);

/**
 * @file cd_path_exist_tools.c
 *
 */

int				handle_cd_args_error(t_shell_data *shell, char **inst);
int				handle_cd_file_error(t_shell_data *shell, char *path);
void			update_env(t_env *env, char *key, char *val,
					t_shell_data *shell);
int				back_to_safe_directory(t_shell_data *shell);
bool			safe_check_and_close_dir(DIR *dir);

/**
 * @file cd_path_exist.c
 *
 */

char			*formated_path(t_shell_data *shell, char **inst);
void			set_env_pwd(t_shell_data *shell, char *old_pwd, char *new_pwd);
bool			is_dir(char *ctx, bool silent);
bool			path_exist(char *path, char *old);
bool			check_parent(char *path);

/**
 * @file cd.c
 *
 */
int				backward_cd(t_shell_data *shell, char *path);
char			*get_path(char *inst);
bool			handle_error_cd_messages(char *home, char **inst,
					t_shell_data *shell);
bool			handle_process_cd(char **inst, char *old, t_shell_data *shell,
					int *i);
int				cd_m(t_shell_data *shell, char **inst);

/**
 * @file char_expansion.c
 *
 */

char			*expand_char(char **prompt, char *to_replace, char **by,
					t_shell_data *shell);

/**
 * @file check_args_and_close.c
 *
 */

void			close_pipes_and_files(t_shell_data *shell);

/**
 * @file check_tokens_checker.c
 *
 */

void			basic_token_checker(t_token *token, t_cmd *pipe);

/**
 * @file check_tokens_fill_tokens.c
 *
 */

void			put_cmd_on_pipe(t_cmd *pipe);
int				token_init_pass2(t_cmd *pipe);
int				tokens_to_chars(t_cmd *pipe, t_shell_data *shell);
int				token_init(t_cmd *pipe, t_shell_data *shell);

/**
 * @file check_tokens_get_files.c
 *
 */
char			**get_path_files(t_token *token, t_cmd *pipe, t_token_type type,
					t_shell_data *shell);

/**
 * @file check_tokens_put_types.c
 *
 */
void			is_variable_check(t_token *token, t_cmd *pipe);
bool			found_cmd_in_pipes(t_cmd *pipes);
bool			found_cmd(t_token *token, t_token_type type);
void			is_command_check(t_token *token, t_token *head);
void			is_args_check(t_token *token, t_cmd *pipe);

/**
 * @file check_tokens.c
 *
 */

void			put_index_pipes(t_shell_data *shell);
bool			there_is_a_path(t_token *token, t_token_type type);
int				args_init(t_shell_data *shell);

/**
 * @file cleans_and_expands_tools.c
 *
 */

void			expand_if_dollar_found(char ***words, int *i, char *old_word,
					t_shell_data *shell);
void			expand_if_wildcard_found(char ***words, int *i, char *old_word,
					t_shell_data *shell);

/**
 * @file cleans_and_expands.c
 *
 */

char			**cleans_and_expands(t_shell_data *shell, char **words);

/**
 * @file clear.c
 *
 */
int				ft_alt_putchar(int c);
int				clear_m(t_shell_data *shell, char **inst);

/**
 * @file cmd_list.c
 *

*/

t_cmd			*new_cmd_node(t_token *token, t_shell_data *shell);
int				count_cmd_nodes(t_cmd *cmd);

/**
 * @file cursor.c
 *
 */

int				init_termcaps(void);
int				set_cursor_above(int times);
int				set_cursor_down(int times);
int				set_enter(int times);

/**
 * @file debug_utils_debug_var.c
 *
 */

void			debug_char(char *str, char *color, t_shell_data *shell);
void			debug_nbr(char *label, long long int i, char *color,
					t_shell_data *shell);
void			set_color(char *color);
void			mark(char *txt, t_shell_data *shell);
void			debug_chars(char **chars_array, char *debug_msg);

/**
 * @file debug_utils_status_print.c
 *
 */

void			print_splitted(char **chars);
void			handle_redirection_types(t_token *token);
void			handle_path_types(t_token *token);
void			handle_other_types(t_token *token);
void			status(t_token *token, t_shell_data *shell);

/**
 * @file debug_utils.c
 *
 */

void			print_tokens(t_token *token, t_shell_data *shell);
void			print_tokens_stack(t_token *tokens, t_shell_data *shell);
void			print_tokens_status(t_shell_data *shell);
int				print_keyval(t_env *lst, char *key);

/**
 * @file echo.c
 *
 */

char			*handle_indicators_and_quotes(char *buffer,
					t_shell_data *shell);
int				echo_m(t_shell_data *shell, char **inst);

/**
 * @file encode_heredoc.c
 *
 */

char			*encode_char(char *here, char find, char replace);

/**
 * @file env_list_extract.c
 *
 */

void			*extract_node_with_key(t_env **lst, char *key,
					t_node_mode mode);
t_env			*free_env_node(t_env *node);
void			free_env_list(t_env **lst);

/**
 * @file env_list_utils.c
 *
 */

int				count_env_nodes(t_env *lst);
char			*merge_node(t_env *lst);
char			**expand_env_to_char(t_env *lst, char **old,
					t_shell_data *shell);
bool			is_duplicate_key(t_env *lst, char *key);

/**
 * @file env_list.c
 *
 */

t_env			*new_env_node(char *key, char *value, t_shell_data *shell);
void			change_env_value(t_env *list, char *key, char *value);
void			push_back_env_node(t_env **list, t_env *node);
t_env			*find_node_with_key(t_env *list, char *key);
char			*get_value_from_key(t_env *list, char *key);

/**
 * @file env_tools.c
 *
 */

int				print_env_list(char *pre, t_env *lst, char **inst,
					bool ingore_void);
int				print_var(t_env *lst, char *key);
int				printenv_m(t_shell_data *shell, char **inst);
void			remove_env_arg(char **inst);
t_env			*set_minimal_env(t_shell_data *shell);

/**
 * @file env.c
 *
 */

int				set_env(t_shell_data *shell);
int				env_m(t_shell_data *shell, char **inst);

/**
 * @file error_mgs.c
 *
 */

void			exit_msg(char *av, char *msg);
void			error_msg(char *err);
void			err_msg(char *msg);
void			unexpected_token_msg(char *msg);

/**
 * @file error_msgs_exit.c
 *
 */

void			exit_errno(char *av, t_shell_data **shell);
void			exit_is_a_directory(char *av, t_shell_data **shell);
void			exit_permission_denied(char *av, t_shell_data **shell);
void			exit_binary_file(char *av, t_shell_data **shell);
void			exit_invalid_file(char *av, t_shell_data **shell);

/**
 * @file exec_cmd_handle_input_output_tools.c
 *
 */

void			remove_nodes_after_i_and_j_and_k(t_cmd *pipe, int i, int j,
					int k);
bool			check_input_filest(t_cmd *pipe, int *i, int *j, int *k);
bool			check_output_files(t_cmd *pipe, int *i, int *j, int *k);
bool			check_append_files(t_cmd *pipe, int *i, int *j, int *k);

/**
 * @file exec_cmd_handle_input_output.c
 *
 */

void			check_path_infile_outfile_error(t_cmd *pipe);

/**
 * @file exe_cmd_tools.c
 */

void			remove_non_printable_chars(char *str);
void			syntax_clean_system(char **to_clean, t_shell_data *shell);
void			syntax_clean_system_str(char **to_clean, t_shell_data *shell);
void			replace_system(char **to_replace, char indicator_dollar);

/**
 * @file exe_cmd.c
 *
 */

void			add_variables_to_char(t_cmd *pipe, t_shell_data *shell);
void			exe_cmd(t_shell_data *shell);

/**
 * @file execute_cmd_check_final_path_env.c
 *
 */

void			env_case(char **cmd_args, t_shell_data *shell);
void			env_i_case(char **cmd_args, t_shell_data *shell);

/**
 * @file execute_cmd_check_final_path.c
 *
 */

void			check_cmd_access_final_path(char **cmd_args, char *path_final,
					t_shell_data *shell);

/**
 * @file execute_cmd_check.c
 *
 */

void			check_cmd_args(char **cmd_args, t_shell_data *shell);

/**
 * @file execute_cmd_tools.c
 *
 */

void			path_final_execution(t_shell_data *shell, char *path_final,
					char **cmd_args);
bool			is_cmd_buildin(char *cmd);
int				get_index_buildin_cmd(char *inst);
void			line_error_command_not_found(t_shell_data *shell,
					char **cmd_args, int *i);
void			line_directory_error(t_shell_data *shell, char **cmd_args,
					int *i);

/**
 * @file execute_cmd_parentheses.c
 *
 */

void			execute_in_parentheses(t_cmd *pipe, t_shell_data *shell);

/**
 * @file execute_cmd.c
 *
 */

void			execute_cmd(t_cmd *pipe, t_shell_data *shell);

/**
 * @file exit_resize.c
 *
 */

int				resize_exit_status(int exit_status);
bool			only_numbers(char *str);

/**
 * @file exit.c
 *
 */

bool			only_numbers(char *str);
bool			check_long_long(int is_negative, int digit,
					long long int result);
bool			is_valid_long_long(const char *str);
int				exit_m(t_shell_data *shell, char **argv);

/**
 * @file export_session.c
 *
 */

int				set_session(t_shell_data *shell);
int				add_session(t_shell_data *shell, char **inst);
int				session_to_env(t_shell_data *shell, char *key);
int				handle_export_options(t_shell_data *shell, char **inst);

/**
 * @file export.c
 *
 */

char			*filter_key(char *key);
int				export_m(t_shell_data *shell, char **inst);

/**
 * @file files_utils.c
 *
 */

int				count_lines_in_files(char *path, t_shell_data *shell);

/**
 * @file fill_shell_data.c
 *
 */

/**
 * @file find_path_cmd.c
 *
 */

char			*search_path(t_shell_data *shell, char **cmd_args);

/**
 * @file ft_get_pid.c
 *
 */

int				end_of_digits(char *str);
int				extract_pid(char *buf);
int				ft_get_pid(t_shell_data *shell);
int				ft_get_ppid(void);

/**
 * @file ft_get_ppid.c
 *
 */

int				ft_get_ppid(void);

/**
 * @file ft_getenv.c
 *
 */

char			*ft_getenv(const char *name, t_shell_data *shell);

/**
 * @file ft_getuid.c
 *
 */

char			*extract_uid(char **line);
char			*ft_getuid(void);

/**
 * @file ft_split_quotes_alt_tools.c
 *
 */

void			encode_char_with(char *words, char replace, char with);
void			*free_on_split_quote_data(t_parser *p, char **words, bool err);

/**
 * @file ft_split_quotes_alt.c
 *
 */

void			set_null_split_quotes_values(t_parser *p, char ***words);
char			**init_split_quotes_values(t_parser *p, char ***words,
					char *str, t_shell_data *shell);
char			*char_copy(char *words, int len, int index, char *str);
char			**fill_chars(t_parser *p, char **words, char *str);
char			**ft_split_quotes_alt(char *str, t_shell_data *shell);

/**
 * @file ft_subsplit.c
 *
 */

int				count_words_in_sub_array(char **array);
char			**fill_array(char **words, char *to_split);
char			**ft_subsplit(char **array);

/**
 * @file git.c
 */

char			*get_git_prompt(void);
char			*check_git(char *line);

/**
 * @file handle_exit_status_code.c
 *
 */

void			handle_exit(int *exit_status1, int *exit_status2,
					t_shell_data *shell);

/**
 * @file handle_heredoc_prompt_printable.c
 *
 */

void			special_bar_non_printable_add(char **prompt,
					t_shell_data *shell);

/**
 * @file handle_heredoc_prompt_read_and.c
 *
 */

char			*handle_and_readline(char *prompt, t_shell_data *shell);

/**
 * @file handle_heredoc_prompt_read_parentheses_tools.c
 *
 */

void			init_read(t_readline_parenth *read);
bool			readline_parentheses_needed(char *prompt);
int				count_to_find_parentheses(char *prompt);
int				count_close_parentheses(char *read);

/**
 * @file handle_heredoc_prompt_read_parentheses.c
 *
 */

void			handle_readline_parentheses(char **prompt, t_shell_data *shell);
bool			readline_parentheses_needed(char *prompt);

/**
 * @file handle_heredoc_prompt_readline.c
 *
 */

char			*prompt_to_here_doc(char *prompt, t_shell_data *shell);

/**
 * @file handle_heredoc_prompt_reduce_bars.c
 *
 */

void			reduce_half_of_bars(char *prompt, t_shell_data *shell);

/**
 * @file handle_heredoc_prompt_tools.c
 *
 */

void			init_write(t_write_prompt *write);
void			remove_backslashes(char *str);
void			if_read_is_null(char **result, char **read,
					t_shell_data *shell);
bool			is_printable_but_no_bar(char c);
bool			nothing_after_bars(char *prompt);

/**
 * @file handle_heredoc_prompt.c
 *
 */

char			*write_in_here_doc_prompt(char *prompt, t_shell_data *shell);

/**
 * @file handle_heredoc_readline_tools.c
 *
 */

void			error_here_doc(t_write_in_here_doc *write, t_cmd *cmd);
void			init_write_in_here_doc(t_write_in_here_doc *write,
					char *delimiter, t_shell_data *shell);
void			save_position(t_write_in_here_doc **write, t_shell_data *shell);
void			fill_line_history(t_write_in_here_doc **write);

/**
 * @file handle_heredoc_readline_write.c
 *
 */

void			write_line_to_pipe(int pipefd[2], const char *line,
					const char *delimiter, t_shell_data *shell);
/**
 * @file handle_heredoc_stdout.c
 *
 */

void			stdout_checks(int *saved_stdout, t_shell_data *shell);
void			process_here_doc_writing(int *saved_stdout,
					t_write_in_here_doc *write, t_shell_data *shell);

/**
 * @file handle_heredoc_tools.c
 *
 */

void			free_before_return(t_write_in_here_doc **write);
bool			condition_to_go_out_here(t_write_in_here_doc **write);
void			print_to_pipe(int pipefd[2], t_write_in_here_doc **write,
					t_shell_data *shell);

/**
 * @file handle_heredoc.c
 *
 */

void			write_in_here_doc(int pipefd[2], t_cmd *cmd, char *delimiter,
					t_shell_data *shell);

/**
 * @file history_add.c
 *
 */

int				add_to_history(char *line, t_shell_data *shell);

/**
 * @file history_load_get.c
 *
 */

char			*get_history_path(void);
int				load_historic(t_shell_data *shell);
char			*get_all_history(void);

/**
 * @file history_rewrite.c
 *
 */

int				rewrite_history(void);

/**
 * @file history.c
 *
 */

int				check_historic_lines(void);
char			*get_last_line(void);
void			init_history(t_shell_data *shell);

/**
 * @file home_path.c
 *
 */

char			*get_home_path_alt(void);
char			*get_home_path(void);
char			*get_login(void);

/**
 * @file init_shell.c
 *
 */

t_shell_data	*init_shell(void);

/**
 * @file invalid_args_and_system_tools.c
 *
 */

bool			is_printable_and_no_special(char c);

/**
 * @file invalid_args_and_system.c
 *
 */

bool			readline_needed(char *inst);
bool			check_and_system(char **inst, t_shell_data *shell, int mode);

/**
 * @file invalid_args_and_system_messages.c
 *
 */

void			print_invalid_args_and_message(int count, int mode);

/**
 * @file invalid_args_parentheses_tools.c
 *
 */

bool			is_printable_but_no_special(char c, int mode);
bool			is_special_char(char c);
char			*find_str_to_print(char *inst, int *i, t_shell_data *shell);

/**
 * @file invalid_args_parentheses.c
 *
 */

bool			check_parenth_system(char *inst, t_shell_data *shell);

/**
 * @file invalid_args_pipes.c
 *
 */

bool			printable_before_pipe(char *inst, int i);
int				count_pipes_in_inst(char *inst, int i, char c);
void			printf_syntax_error_vertical(int cases);
int				find_error_case_pipe(char *inst, int i, char c);
int				check_pipe_system(char *inst, t_shell_data *shell);

/**
 * @file invalid_args_redir_printers_tools.c
 *
 */

bool			printable_after_redir(char *inst, int i, int *position);
void			print_syntax_error(t_shell_data *shell, const char *token);
void			print_number_special_case(t_shell_data *shell,
					t_find_error_case_syntax *find);

/**
 * @file invalid_args_redir_printers.c
 *
 */

bool			find_error_case_special_number(t_find_error_case_syntax *find,
					char c, t_shell_data *shell);
void			print_first_case_next_redir(t_find_error_case_syntax *find,
					t_shell_data *shell, char *inst);
void			print_second_case_next_redir(t_find_error_case_syntax *find,
					t_shell_data *shell, char *inst);
void			print_third_case_next_redir(t_find_error_case_syntax *find,
					t_shell_data *shell, char c);
bool			check_next_redir_final(t_find_error_case_syntax *find,
					t_shell_data *shell, char *inst, char c);

/**
 * @file invalid_args_redir_tools.c
 *
 */

bool			find_error_case_syntax(char *inst, int i, char c,
					t_shell_data *shell);
bool			check_special_number_case(t_find_error_case_syntax *find,
					t_shell_data *shell);
int				count_consecutive_redir(char *inst, char c, int i);
int				count_special_order_redir(char *inst, int i, bool *alpha,
					int *number_special);

/**
 * @file invalid_args_redir.c
 *
 */

bool			find_new_line_case(char *inst, int i, char c);
bool			find_single_redir_in_case(char *inst, int i, char c);
bool			find_double_redir_in_case(char *inst, int i, char c);
bool			find_triple_redir_in_case(char *inst, int i, char c);
int				check_redir_system(char *inst, t_shell_data *shell);

/**
 * @file invalid_args_specials_chars.c
 *
 */

int				special_chars_errors(char *inst);

/**
 * @file invalid_args_tools.c
 *
 */

bool			is_single_char_in_string(char *str, char *cmp);

/**
 * @file invalid_args.c
 *
 */

bool			is_single_char_in_string(char *str, char *cmp);
void			init_find(t_find_error_case_syntax *find);
void			find_opposite_redir_consecutive(char *inst, int i, char c,
					t_find_error_case_syntax *find);
int				redirection_errors(t_shell_data *shell, char **inst);
int				directory_errors(t_shell_data *shell, char *inst);

/**
 * @file lang_expansion_lang_occurences.c
 *
 */

int				find_lang_occurences(char *str, char c);

/**
 * @file lang_expansion.c
 *
 */

int				end_index(char *to_expand, char *sequence, int start);
int				ft_strstr_index(char *to_expand, char *sequence);
char			*filter_occurences(char *to_expand, char *to_filter,
					char *end_char, t_shell_data *shell);
char			*expand_lang(char *to_expand, t_shell_data *shell);

/**
 * @file live_code_chris.c
 *
 */

/**
 * @file malloc_tools_exit.c
 *
 */

void			exit_127(t_shell_data **shell);
void			exit_0(t_shell_data **shell);
void			exit_126(t_shell_data **shell);
void			exit_1(t_shell_data **shell);
void			exit_1_malloc(t_shell_data **shell);

/**
 * @file malloc_tools_struct.c
 *
 */

void			free_t_env(t_env **head);
void			free_t_fds(t_fds **head);
void			free_t_pipefd(t_pipefd **head);
void			free_tokens(t_cmd *pipe);
void			free_cmd_pipe(t_shell_data *shell);

/**
 * @file malloc_tools.c
 *
 */

void			free_exec_unit(t_exec_unit **unit);
void			put_to_zero_all(void **ptr, ...);
void			free_loop_malloc_system(t_shell_data **shell);
void			free_malloc_exit_system(t_shell_data **shell);
void			free_malloc_exit_system_ctrl_d(t_shell_data **shell);

/**
 * @file memory.c
 */

void			clear_memory(t_shell_data *shell);

/**
 * @file minishell_buildin_tools.c
 *
 */

bool			is_builtin(char *func);
int				get_index(char *inst);
int				exe_builtin_cmd(char *inst, char **argv, t_shell_data *shell);
int				reopen_stdin_if_needed(void);

/**
 * @file minishell_debug.c
 *
 */

int				check_start_mode(t_shell_data *shell);
int				sandbox(t_shell_data *shell);
void			init_rc_file(t_shell_data *shell);
void			script_exe(t_shell_data *shell);

/**
 * @file minishell_shell_prompt_init.c
 *
 */

void			parsing_and_stack_malloc(t_shell_data *shell);
void			case_bar_vertical_command(t_shell_data *shell);

/**
 * @file minishell_shell_prompt_tools.c
 *
 */

void			initialize_prompt_value(t_shell_data *shell);
void			handle_history_add_readline(char **prompt, t_shell_data *shell);

/**
 * @file minishell_shell_prompt.c
 *
 */

int				shell_prompt(t_shell_data *shell);
void			execute_shell(char *prompt, t_shell_data *shell, int *count,
					bool have_to_free);

/**
 * @file minishell_signals.c
 *
 */

void			welcome_message(void);
void			restore_terminal(t_shell_data *shell);
void			handle_sigtstp(int sig);

/**
 * @file minishell.c
 *
 */

int				main(int ac, char **av, char **env);

/**
 * @file open_input.c
 *
 */

int				open_fd_input(t_cmd *pipes, t_shell_data *shell, int print);

/**
 * @file open_output.c
 *
 */

int				open_fd_output(t_cmd *pipe, t_shell_data *shell);

/**
 * @file parsing_chars.c
 *
 */

void			cat_char_to_one(t_token *token, t_shell_data *shell);
void			double_to_char(t_cmd *pipe, t_shell_data *shell);

/**
 * @file parsing_clean_system.c
 *
 */

void			remove_word(char ***words, int index, t_shell_data *shell);
void			check_and_remove_nonexistent_vars(char ***words,
					t_shell_data *shell);
void			remove_dollar_and_quotes(char **words);
void			print_string(const char *str);
char			*remove_spaces_before_after_word(char *str);

/**
 * @file parsing_count_args.c
 *
 */

int				is_space(char c);
bool			if_quote(char c);
bool			if_trim(char *str, int i);
int				count_total_args(char *str);

/**
 * @file parsing_count_len_words_1.c
 *
 */

void			count_len_words(char *str, t_parser *p, t_shell_data *shell);

/**
 * @file parsing_count_len_words_2.c
 *
 */

void			allocation_len_and_start(int total_args, int **len_words,
					int **start, t_shell_data *shell);
void			initialize_values(t_parsing_values *values);

/**
 * @file parsing_count_tools.c
 *
 */

int				total_quotes(char *str);
int				total_quotes_double(char *str);
int				total_quotes_simple(char *str);

/**
 * @file parsing_readline_quotes.c
 *
 */

int				*add_logic_expand_in_doc(char *inst, t_shell_data *shell);

/**
 * @file parsing_readline_quotes.c
 *
 */

char			*return_readline(char *str, char delimiter);
char			*if_readline_is_needed(char *str);

/**
 * @file parsing_smart_quotes.c
 *
 */

char			*smart_remove_quotes(char *str, t_shell_data *shell);

/**
 * @file parsing_stack_parentheses.c
 *
 */

void			remove_parentheses_string(char *str, t_shell_data *shell);
void			fill_p_execute_shell(t_cmd *cmd, char ***parsed, int *i,
					int *j);
void			remove_string_in_parentheses(char ***parsed, int *i, int *j);
void			remove_empty_strings(char ***parsed);
void			parentheses_traitement(char **parsed, t_cmd *cmd, int *i,
					t_shell_data *shell);

/**
 * @file parsing_stack.c
 *
 */

size_t			ft_strlen_alt(const char *s);
int				args_parsed_to_stack(t_shell_data *shell);

/**
 * @file parsing_tools_1.c
 *
 */

int				count_words(char *str);
char			*hard_remove_quotes(char *word, t_shell_data *shell);
void			remove_quotes(char *word);
void			free_malloc_split(char **dest);

/**
 * @file parsing_tools_2.c
 *
 */

bool			if_only_espaces(char *str);
bool			if_only_tabs(char *str);
int				handle_basic_invalid_args(char **inst, t_shell_data *shell);

/**
 * @file parsing_variable_exist.c
 */

char			*create_initial_result(char *str);
char			*append_and_check(char *result, char *read, char delimiter);
int				variable_exists(char *var, t_shell_data *shell);

/**
 * @file parsing.c
 *
 */

void			fill_initial_parsed(char **words, t_shell_data *shell);
void			add_espace_if_need(char **inst, char c, t_shell_data *shell);
void			fill_args_to_parsed(char *inst, t_shell_data *shell);

/**
 * @file pipes_fds_child_setup.c
 *
 */

pid_t			create_child_process(t_fds *fds, t_cmd *pipe,
					t_shell_data *shell);

/**
 * @file pipes_tools_fds.c
 *
 */

t_fds			*new_fds_node(t_shell_data *shell);
t_fds			*push_fds(t_fds *stack, t_shell_data *shell);

/**
 * @file pipes_tools_pipefd.c
 *
 */

t_pipefd		*new_pipefd_node(t_shell_data *shell);
t_pipefd		*push_pipefd(t_pipefd *stack, t_shell_data *shell);

/**
 * @file pipes_tools.c
 *
 */

void			print_error(const char *var, const char *msg,
					t_shell_data *shell);
bool			can_execute(const char *filepath);
void			error_execve_check(char **cmd_args, t_shell_data *shell);
void			remove_line_break(t_cmd *pipe, t_pipefd *pipefd1,
					t_shell_data *shell);

/**
 * @file pipex_close_and_open.c
 *
 */

void			close_all_pipefd(t_shell_data *shell);
void			close_all_fds(t_shell_data *shell);
void			open_all_pipes(t_shell_data *shell);
void			open_all_fds(t_shell_data *shell);
int				*clear_pipe(int *pipefd, t_shell_data *shell);

/**
 * @file pipex_create_process_tools.c
 *
 */

void			config_children_process(t_shell_data *shell);
void			start_children_process(t_fds *current_fds, t_cmd *current_pipe,
					t_shell_data *shell);
void			handle_exit_status_children(t_cmd *current_pipe,
					t_shell_data *shell);

/**
 * @file pipex_create_process.c
 *
 */

void			create_pid_process(t_cmd *pipes, t_shell_data *shell);

/**
 * @file pipex_exist.c
 *
 */

bool			if_double_redir_input_exist(t_cmd *pipes);
bool			if_double_redir_input_is_last(t_cmd *pipes);
bool			if_double_redir_output_exist(t_cmd *pipes);

/**
 * @file pipex_fill_all_fds_doc.c
 *
 */

void			fill_all_fds_doc(t_cmd *current_pipe, t_pipefd *current_pipefd1,
					t_fds *current_fds, t_shell_data *shell);

/**
 * @file pipex_fill_all_fds.c
 *
 */

void			fill_all_fds(t_cmd *current_pipe, t_pipefd *current_pipefd1,
					t_fds *current_fds, t_shell_data *shell);

/**
 * @file pipex_write.c
 *
 */

void			write_input_to_pipes(t_cmd *current_pipe,
					t_pipefd *current_pipefd, t_shell_data *shell);

/**
 * @file pipex.c
 *
 */

int				pipex(t_cmd *pipe, t_shell_data *shell);

/**
 * @file prompt.c
 *
 */

void			debug_prompt(t_prompt prompt);
char			*get_prompt(t_prompt prompt, char *line, t_shell_data *shell);
char			*prompt_line(t_shell_data *shell);

/**
 * @file pwd.c
 *
 */

bool			bad_pwd_options(t_shell_data *shell, char **inst);
int				pwd_m(t_shell_data *shell, char **inst);

/**
 * @file quotes_handling_mask.c
 *
 */

bool			has_dollar_indicator(char *str);
bool			has_quotes(char *str);

/**
 * @file quotes_handling.c
 *
 */

bool			swap_foreward_in_lang(char *str, int index);
bool			swap_foreward(char *str, int index);
bool			swap_back(char *str, int index);

/**
 * @file rc_file.c
 *
 */

void			init_rc_file(t_shell_data *shell);

/**
 * @file scripts_count_lines.c
 *
 */

bool			has_binary_data(char *buff, int reads);
void			reset_buffer_alt(char *buffer, int size);
bool			is_binary_file(char *path);
bool			if_some_thing_to_execute(t_cmd *pipes);
int				count_lines(char *path, t_shell_data *shell);

/**
 * @file scripts_exec.c
 *
 */

int				execute_file_as_script(char *path, t_shell_data *shell);

/**
 * @file scripts_utils.c
 *
 */

bool			if_some_thing_to_execute(t_cmd *pipes);
char			**line_to_double_string(char *path, int total_lines,
					t_shell_data *shell);
void			initialize_variables_for_script(int *total_lines,
					t_shell_data *shell, char *path);
void			argv_execution(char *av, t_shell_data *shell);

/**
 * @file send_text_in_pipe.c
 *
 */

char			*send_text_through_pipe(int *pipefd, char *line, t_cmd *pipes,
					t_shell_data *shell);

/**
 * @file set.c
 *
 */

int				set_m(t_shell_data *shell, char **inst);

/**
 * @file shell_level.c
 *
 */

void			add_number_shell_level(void);
void			reduce_number_shell_level(void);

/**
 * @file signals_readline.c
 *
 */

int				init_signals_alt(t_shell_data *shell);

/**
 * @file signals_shell.c
 *
 */

int				init_signals_new_shell(void);

/**
 * @file signals.c
 *
 */

void			handle_sigint_parent(int sig);
void			handle_sigquit_parent(int sig);
void			handle_signals_parent(int sig);
void			handle_sigs_in_child(int sig);
int				init_signals(t_shell_data *shell);

/**
 * @file sort_tools.c
 *
 */

void			print_chars(char *prefix, char **chars);

/**
 * @file tokens.c
 *
 */

t_token			*new_token_node(char *value, t_shell_data *shell);
void			free_env_node_token(t_token *node);
int				count_token_nodes(t_token *tokens);
t_token			*push_token(t_token *stack, char *value, t_shell_data *shell);
void			free_token_stack(t_token **stack);

/**
 * @file trash.c
 *
 */

int				from_index(char *str, char *skip);
int				to_index(char *str, char *skip);
char			*trim(char *str, bool to_free);

/**
 * @file unalias.c
 *
 */

int				unalias_m(t_shell_data *shell, char **inst);

/**
 * @file unset.c
 *
 */

bool			unset_errors(char *inst, t_shell_data *shell);
void			change_value_in_env(t_env **env, char *key, char *value);
int				unset_m(t_shell_data *shell, char **inst);

/**
 * @file utils.c
 *
 */

char			*cpy(char *src, char *dest);
char			*pass_str(char *to_pass, char *str);
char			*ft_strjoin_with_space_and_free(char *s1, char *s2,
					t_shell_data *shell);
char			*ft_strjoin_and_free(char *s1, char *s2, t_shell_data *shell);

/**
 * @file var_affectation.c
 */

bool			only_affectation(t_cmd *pipe);
char			**get_chars_from_single(char *aff, t_shell_data *shell);
int				exec_affectations(t_shell_data *shell);
int				var_affectations(t_shell_data *shell);

/**
 * @file var_check.c
 */

bool			has_forbidden_sign(char *key);
bool			is_a_sum(char *key);
bool			has_forbidden_char(char *key);
bool			is_valid_variable(char *key);

/**
 * @file var_expansion_expander.c
 */

char			*replace_in_str(char *str, t_shell_data *shell);

/**
 * @file var_expansion_quotes.c
 */

void			encode_quotes(char *replace);
void			decode_quotes_before_smart(char *replace);
void			decode_quotes_after_smart_quotes(char *replace);
bool			has_to_expand(char *str, char *to_expand, int pos);

/**
 * @file var_expansion_tools.c
 */

int				ft_count_occurences(char c, char *str);
int				var_length(char *str, int index);
int				count_bar_before_dollar(char *str, int index);
int				is_authorized_char(char c);
bool			has_to_ignore(char c);

/**
 * @file var_expansion.c
 */

int				get_status_from_sig(t_shell_data *shell);
char			*expand_exit_status(t_shell_data *shell);
char			*find_value(char *to_expand, t_shell_data *shell,
					int trim_space);
bool			do_nothing_in_vars(char *str);
char			*expand_variable(char *str, t_shell_data *shell);

/**
 * @file wild_dirs.c
 *
 */
char			*get_sub_dirs(char *dir_path, bool show_hided);
char			**get_sorted_dirs(char *dir_path, unsigned char type);

/**
 * @file wild_match.c
 *
 */

char			*wild_both(char *to_expand, char *to_check);
char			*wild_start(char *to_expand, char *to_check);
char			*wild_end(char *to_expand, char *to_check);
char			*wild_middle(char *to_expand, char *to_check);
char			*wild_mixed(char *to_expand, char *to_check);

/**
 * @file wild_matcher.c
 *
 */

int				get_comp_context(char *to_find);
char			*wild_all(char *to_expand, char *to_check);
char			*ft_wild_matcher(char *to_expand, char *to_check, int ctx);

/**
 * @file wild_utils.c
 *
 */

char			*get_sorted_wildcards(char **to_sort);
char			*extract_path_from_glob(char *to_expand);
void			set_wild_struct(t_wild *wild, char *to_expand, bool open_dir);

/**
 * @file wild_format_utils.c
 *
 */

char			*get_formated_files(char *temp);
void			format_files_array(char **to_format);
void			replace_all_spaces(char **chars, int mode);
void			replace_spaces(char *temp, int mode);

/**
 * @file wildcard.c
 *
 */

char			*expand_wildcard_from_directories(char **to_expand,
					bool *show_hided);
char			*expand_wildcard_from_dir(char **to_expand, bool *show_hided);
char			*get_wildcard_to_expand(char **prompt);
bool			set_show_hided(char **prompt);
char			*expand_wildcard(char *prompt, t_shell_data *shell);

/**
 * @file parsing_bonus_create_subs.c
 *
 */

t_exec_unit		*create_subs(t_exec_unit *parent, char *left_prompt,
					char *right_prompt);

/**
 * @file parsing_bonus_sanithize_tools.c
 *
 */

bool			can_trim_parenthesis(char *prompt);
bool			has_white_space(char *prompt);
bool			ft_is_whitespace(char c);

/**
 * @file parsing_bonus_sanithize.c
 *
 */

void			ft_unallocated_trim(char *str);
void			ft_symetric_trim_parenthesis(char *str);
void			sanithize_prompt(char *prompt);
void			sanithize_prompts(char **prompts);
void			ft_unallocated_trim_once(char *str, char c);

/**
 * @file parsing_bonus_split_in_exec.c
 *
 */

t_exec_unit		*split_in_exec_units(char *prompt, t_exec_unit *exec_unit);

/**
 * @file parsing_bonus_split_tools.c
 *
 */

bool			has_ops(char *str);

/**
 * @file parsing_bonus_split.c
 *
 */

int				get_root_split_index(char *prompt);
int				get_root_split_index_rev(char *prompt);
char			**ft_split_at_law_index(char *prompt);
char			**ft_split_at_index(char *prompt, int index);

/**
 * @file parsing_bonus_tokens.c
 *
 */

int				count_tokens(char **args);
char			*move_pointer(char *ptr, int moves);
char			*ft_smart_tokeniser(char *str, int *toki);

/**
 * @file parsing_bonus_tools.c
 *
 */

int				count_args(char **args);
int				index_from_pointer(char *prompt, char *p);
void			reset_buffers_array(char **buffs, int length, int sublength);

char			*get_next_prompt(char **splitted);

/**
 * @file parsing_bonus.c
 *
 */

int				exec_cmd_tree(t_exec_unit *exec_unit, t_shell_data *shell,
					int *count);
void			breakdown_parenthesis(char *prompt, t_shell_data *shell,
					int *count);

/**
 * @file exec_unit_malloc.c
 *
 */

t_exec_unit		*create_exec_unit(char *prompt, int type, t_exec_unit *parent);
t_exec_unit		*get_exec_root(t_exec_unit *unit);
void			clear_exec_unit(t_exec_unit *exec_unit);
void			join_exec_unit(t_exec_unit *left, t_exec_unit *right,
					t_exec_unit **node);

/**
 * @file exec_unit_print.c
 *
 */

void			print_exec_unit_prefix(t_exec_unit *exec_unit);
void			print_exec_unit_postfix(t_exec_unit *exec_unit);

/**
 * @file exec_unit.c
 *
 */

int				count_exec_unit_nodes(t_exec_unit *exec_unit);
int				execute_commands(t_shell_data *shell);

/**
 * @file export_tools.c
 */

char			*check_and_filter(char *str, t_shell_data *shell);

#endif
