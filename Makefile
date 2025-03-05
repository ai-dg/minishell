# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/25 12:07:46 by dagudelo          #+#    #+#              #
#    Updated: 2024/06/30 18:18:16 by calbor-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ./Srcs/alias.c ./Srcs/alias_expander.c \
      ./Srcs/cd.c \
      ./Srcs/cd_go_home.c \
      ./Srcs/cd_path_exist.c \
      ./Srcs/cd_path_exist_tools.c \
      ./Srcs/char_expansion.c \
      ./Srcs/check_args_and_close.c \
      ./Srcs/check_tokens.c \
      ./Srcs/check_tokens_checker.c \
      ./Srcs/check_tokens_fill_tokens.c \
      ./Srcs/check_tokens_get_files.c \
      ./Srcs/check_tokens_put_types.c \
      ./Srcs/cleans_and_expands_tools.c \
      ./Srcs/cleans_and_expands.c \
      ./Srcs/clear.c \
      ./Srcs/cmd_list.c \
      ./Srcs/cursor.c \
      ./Srcs/debug_utils.c \
      ./Srcs/debug_utils_debug_var.c \
      ./Srcs/debug_utils_status_print.c \
      ./Srcs/echo.c \
      ./Srcs/encode_heredoc.c \
      ./Srcs/env.c \
      ./Srcs/env_list.c \
      ./Srcs/env_list_extract.c \
      ./Srcs/env_list_utils.c \
      ./Srcs/env_tools.c \
      ./Srcs/error_mgs.c \
      ./Srcs/error_msgs_exit.c \
      ./Srcs/exe_cmd.c \
      ./Srcs/exe_cmd_handle_input_output.c \
      ./Srcs/exe_cmd_handle_input_output_tools.c \
      ./Srcs/exe_cmd_tools.c \
      ./Srcs/exec_unit.c \
      ./Srcs/exec_unit_malloc.c \
      ./Srcs/exec_unit_print.c \
      ./Srcs/execute_cmd.c \
      ./Srcs/execute_cmd_check.c \
      ./Srcs/execute_cmd_check_final_path.c \
      ./Srcs/execute_cmd_check_final_path_env.c \
      ./Srcs/execute_cmd_parentheses.c \
      ./Srcs/execute_cmd_tools.c \
      ./Srcs/exit.c \
      ./Srcs/exit_resize.c \
      ./Srcs/export.c \
      ./Srcs/export_session.c \
      ./Srcs/export_tools.c \
      ./Srcs/files_utils.c \
      ./Srcs/fill_shell_data.c \
      ./Srcs/find_path_cmd.c \
      ./Srcs/ft_getenv.c \
      ./Srcs/ft_get_pid.c \
      ./Srcs/ft_get_ppid.c \
      ./Srcs/ft_getuid.c \
      ./Srcs/ft_split_quotes_alt.c \
      ./Srcs/ft_split_quotes_alt_tools.c \
      ./Srcs/ft_subsplit.c \
      ./Srcs/git.c \
      ./Srcs/handle_exit_status_code.c \
      ./Srcs/handle_heredoc.c \
      ./Srcs/handle_heredoc_prompt.c \
      ./Srcs/handle_heredoc_prompt_printable.c \
      ./Srcs/handle_heredoc_prompt_read_and.c \
      ./Srcs/handle_heredoc_prompt_readline.c \
      ./Srcs/handle_heredoc_prompt_read_parenthese.c \
      ./Srcs/handle_heredoc_prompt_read_parenthese_tools.c \
      ./Srcs/handle_heredoc_prompt_reduce_bars.c \
      ./Srcs/handle_heredoc_prompt_tools.c \
      ./Srcs/handle_heredoc_readline_tools.c \
      ./Srcs/handle_heredoc_readline_write.c \
      ./Srcs/handle_heredoc_stdout.c \
      ./Srcs/handle_heredoc_tools.c \
      ./Srcs/history_add.c \
      ./Srcs/history.c \
      ./Srcs/history_load_get.c \
      ./Srcs/history_rewrite.c \
      ./Srcs/home_path.c \
      ./Srcs/init_shell.c \
      ./Srcs/invalid_args_and_system.c \
      ./Srcs/invalid_args_and_system_messages.c \
      ./Srcs/invalid_args_and_system_tools.c \
      ./Srcs/invalid_args.c \
      ./Srcs/invalid_args_parentheses.c \
      ./Srcs/invalid_args_parentheses_tools.c \
      ./Srcs/invalid_args_pipes.c \
      ./Srcs/invalid_args_redir.c \
      ./Srcs/invalid_args_redir_printers.c \
      ./Srcs/invalid_args_redir_printers_tools.c \
      ./Srcs/invalid_args_redir_tools.c \
      ./Srcs/invalid_args_specials_chars.c \
      ./Srcs/invalid_args_tools.c \
      ./Srcs/lang_expansion.c \
      ./Srcs/lang_expansion_lang_occurences.c \
      ./Srcs/live_code_chris.c \
      ./Srcs/malloc_tools.c \
      ./Srcs/malloc_tools_exit.c \
      ./Srcs/malloc_tools_struct.c \
      ./Srcs/memory.c \
      ./Srcs/minishell_buildin_tools.c \
      ./Srcs/minishell.c \
      ./Srcs/minishell_debug.c \
      ./Srcs/minishell_shell_execute_shell.c \
      ./Srcs/minishell_shell_prompt_init.c \
      ./Srcs/minishell_shell_prompt_tools.c\
      ./Srcs/minishell_shell_prompt.c \
      ./Srcs/minishell_signals.c \
      ./Srcs/open_input.c \
      ./Srcs/open_output.c \
      ./Srcs/parsing_bonus.c \
      ./Srcs/parsing_bonus_create_subs.c \
      ./Srcs/parsing_bonus_sanithize.c \
      ./Srcs/parsing_bonus_sanithize_tools.c \
      ./Srcs/parsing_bonus_split.c \
      ./Srcs/parsing_bonus_split_in_exec.c \
      ./Srcs/parsing_bonus_split_tools.c \
      ./Srcs/parsing_bonus_tokens.c \
      ./Srcs/parsing_bonus_tools.c \
      ./Srcs/parsing.c \
      ./Srcs/parsing_chars.c \
      ./Srcs/parsing_clean_system.c \
      ./Srcs/parsing_count_args.c \
      ./Srcs/parsing_count_len_words_1.c \
      ./Srcs/parsing_count_len_words_2.c \
      ./Srcs/parsing_count_tools.c \
      ./Srcs/parsing_here_doc_logic.c \
      ./Srcs/parsing_readline_quotes.c \
      ./Srcs/parsing_smart_quotes.c \
      ./Srcs/parsing_stack.c \
      ./Srcs/parsing_stack_parentheses.c \
      ./Srcs/parsing_tools_1.c \
      ./Srcs/parsing_tools_2.c \
      ./Srcs/parsing_variable_exist.c \
      ./Srcs/pipes_fds_child_setup.c \
      ./Srcs/pipes_tools.c \
      ./Srcs/pipes_tools_fds.c \
      ./Srcs/pipes_tools_pipefd.c \
      ./Srcs/pipex.c \
      ./Srcs/pipex_close_and_open.c \
      ./Srcs/pipex_create_process_tools.c \
      ./Srcs/pipex_create_process.c \
      ./Srcs/pipex_exist.c \
      ./Srcs/pipex_fill_all_fds.c \
      ./Srcs/pipex_fill_all_fds_doc.c \
      ./Srcs/pipex_write.c \
      ./Srcs/prompt.c \
      ./Srcs/pwd.c \
      ./Srcs/quotes_handling.c \
      ./Srcs/quotes_handling_mask.c \
      ./Srcs/rc_file.c \
      ./Srcs/scripts_count_lines.c \
      ./Srcs/scripts_exec.c \
      ./Srcs/scripts_utils.c \
      ./Srcs/send_text_in_pipe.c \
      ./Srcs/set.c \
      ./Srcs/shell_level.c \
      ./Srcs/signals.c \
      ./Srcs/signals_readline.c \
      ./Srcs/signals_shell.c \
      ./Srcs/sort_tools.c \
      ./Srcs/tokens.c \
      ./Srcs/trash.c \
      ./Srcs/unalias.c \
      ./Srcs/unset.c \
      ./Srcs/utils.c \
      ./Srcs/var_affectation.c \
      ./Srcs/var_check.c \
      ./Srcs/var_expansion.c \
      ./Srcs/var_expansion_expander.c \
      ./Srcs/var_expansion_quotes.c \
      ./Srcs/var_expansion_tools.c \
      ./Srcs/wildcard.c \
      ./Srcs/wildcard_dirs.c \
      ./Srcs/wild_dirs.c \
      ./Srcs/wild_format_utils.c \
      ./Srcs/wild_match.c \
      ./Srcs/wild_matcher.c \
      ./Srcs/wild_utils.c \

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I./Includes/ -I./Includes/libft
# DEBUG = -g -fsanitize=leak -fsanitize=address -I./Includes/ -I./Includes/libft
# CFLAGS = -Wall -Wextra -Werror -g -fsanitize=leak -fsanitize=address -I./Includes/ -I./Includes/libft
OBJ = $(SRC:.c=.o)

NAME = minishell
LIBFT_DIR = ./Includes/libft
LIBFT = $(LIBFT_DIR)/libft.a

GREEN = \033[32m
BLINK = \033[5m
RESET = \033[0m
ORANGE = \033[33m

%.o: %.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@
#	@$(CC) $(DEBUG) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
	@echo "Linking $(NAME)..."
	@$(CC) $(CFLAGS) $^ -o $@ -lreadline -lcurses
	@echo  "$(GREEN)$(BLINK)$(NAME) compiled successfully!$(RESET)"

$(LIBFT):
	@echo "Building libft..."
	@$(MAKE) -C $(LIBFT_DIR)

all: $(NAME)

clean:
	@echo "Cleaning object files..."
	@rm -rf $(OBJ)
	@echo "$(ORANGE)$(BLINK)Objects file cleaned.$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@echo "Cleaning $(NAME)..."
	@rm -rf $(NAME)
	@echo "$(ORANGE)$(BLINK)$(NAME) program cleaned.$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

debug: $(OBJ) $(LIBFT)
	@echo "Linking debug $(NAME)..."
	@$(CC) $(DEBUG) $^ -o $@ -lreadline -lcurses -g
	@echo  "$(GREEN)$(BLINK)$(NAME) compiled successfully!$(RESET)"

.PHONY: all clean fclean re debug
