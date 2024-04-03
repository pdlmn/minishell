SRCS=expansion.c _tests.c ../hash_table/ht1.c ../hash_table/ht2.c ../hash_table/ht3.c  ../hash_table/utils.c ../command_table/command_table.c ../lexer/lexer.c ../lexer/token.c ../lexer/utils.c
LIBFT=../libft/libft.a
NAME=expansion_test

$(NAME): $(SRCS)
	gcc $(SRCS) $(LIBFT) -g -o $@ -fsanitize=address

clean:
	rm -f hash_table_test

re: clean $(NAME)
