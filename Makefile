#comilation vars-----------------------------------
CC=cc
CFLAGS=-g3 -Wall -Wextra -Werror
RLFLAGS=-lreadline

#subject declarations------------------------------
NAME=minishell
OBJS_DIR=objs/
HEAD_DIR=include/
LIB_DIR=libft/
LIB=$(LIB_DIR)libft.a

#files from different branches---------------------
HEADERS=$(HEAD_DIR)minishell.h \
		$(HEAD_DIR)lexer.h \
		$(HEAD_DIR)hash_table.h \
		$(HEAD_DIR)expansion.h \
		$(HEAD_DIR)env.h \
		$(HEAD_DIR)execution.h \
		$(HEAD_DIR)command_table.h

SRCS=lexer.c \
	 input_parsing.c \
	 lexer_utils.c \
	 token_deletion.c \
	 token_operations.c \
	 error_checking.c \
	 ht1.c \
	 ht2.c \
	 ht3.c \
	 ht_utils.c \
	 expansion.c \
	 split_unspaced.c \
	 quotes_expansion.c \
	 variables_expansion.c \
	 heredoc_find_delimeters.c \
	 expansion_utils.c \
     env.c \
     env_utils.c \
	 signal_handlers.c \
	 init_signal_handlers.c \
	 command_table.c \
	 cmd_tab1.c \
	 cmd_tab2.c \
	 command_table_utils.c \
	 execution.c \
	 builtins1.c \
	 builtins2.c \
	 cd_builtin.c \
	 find_command_and_redir.c \
	 redir.c \
	 redir_utils.c \
	 exec_utils.c \
	 execution_utils.c \
	 execution_check.c \
	 utils.c \
	 interactive_mode.c \
	 noninteractive_mode.c \
	 main.c
OBJS=$(SRCS:%.c=$(OBJS_DIR)%.o)
VPATH=lexer:token:error_handling:hash_table:expansion:env:shell:command_table:execution

#rules---------------------------------------------
all: $(NAME)

$(NAME): $(LIB) $(HEADERS) $(OBJS)
	$(CC) $(CFLAGS) $(RLFLAGS) $(OBJS) $(LIB) -o $@ -lreadline

$(OBJS_DIR)%.o: %.c $(HEADERS)
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB): libft

libft:
	$(MAKE) -C $(LIB_DIR)

clean:
	$(MAKE) -C $(LIB_DIR) $@
	rm $(OBJS_DIR) -rf

fclean: clean
	$(MAKE) -C $(LIB_DIR) $@
	rm $(NAME) $(LIB) -f
	rm $(BONUS_NAME) $(LIB) -f

re: fclean
	$(MAKE) -C $(LIB_DIR) $@
	$(MAKE) all --no-print-directory

valgrind:
	$(MAKE) all
	valgrind --suppressions=valgrind_ignore_leaks --track-fds=yes --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --show-mismatched-frees=yes --read-var-info=yes ./$(NAME)

.PHONY: all clean fclean re libft valgrind
