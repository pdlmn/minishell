#comilation vars-----------------------------------
CC=cc
CFLAGS=-Wall -Wextra -Werror -g3 -fsanitize=address
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
		$(HEAD_DIR)env.h

SRCS=lexer.c \
	 input_parsing.c \
	 lexer_utils.c \
	 token_deletion.c \
	 token_operations.c \
	 ht1.c \
	 ht2.c \
	 ht3.c \
	 ht_utils.c \
	 expansion.c \
	 quotes_expansion.c \
	 variables_expansion.c \
	 expansion_utils.c \
     env.c \
     env_utils.c \
	 handle_signal.c \
	 command_table.c \
	 main.c
OBJS=$(SRCS:%.c=$(OBJS_DIR)%.o)
VPATH=lexer:token:hash_table:expansion:env:shell:command_table

#rules---------------------------------------------
all: $(NAME)

$(NAME): $(LIB) $(HEADER) $(OBJS)
	$(CC) $(CFLAGS) $(RLFLAGS) $(OBJS) $(LIB) -o $@

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

.PHONY: all clean fclean re libft