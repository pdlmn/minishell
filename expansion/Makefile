SRCS=expansion.c quotes_expansion.c variables_expansion.c expansion_utils.c split_unspaced.c _tests.c ../hash_table/ht1.c ../hash_table/ht2.c ../hash_table/ht3.c  ../hash_table/ht_utils.c ../command_table/command_table.c ../command_table/command_table_utils.c ../command_table/cmd_tab1.c ../command_table/cmd_tab2.c ../lexer/lexer.c ../lexer/input_parsing.c ../lexer/heredoc_find_delimeters.c ../token/token_deletion.c ../token/token_operations.c ../lexer/lexer_utils.c ../env/env.c ../env/env_utils.c
LIBFT=../libft/libft.a
NAME=expansion_test

$(NAME): $(SRCS)
	cc $(SRCS) $(LIBFT) -g -o $@ -fsanitize=address

clean:
	rm -f $(NAME)

re: clean $(NAME)
