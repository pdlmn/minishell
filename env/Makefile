SRCS=env.c env_utils.c _tests.c ../hash_table/ht1.c ../hash_table/ht2.c ../hash_table/ht3.c  ../hash_table/ht_utils.c ../command_table/command_table.c ../lexer/lexer.c ../lexer/input_parsing.c ../lexer/lexer_utils.c ../token/token_deletion.c ../token/token_operations.c
LIBFT=../libft/libft.a
NAME=env_test

$(NAME): $(SRCS)
	gcc $(SRCS) $(LIBFT) -g -o $@ -fsanitize=address

clean:
	rm -f $(NAME)

re: clean $(NAME)
