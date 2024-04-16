SRCS=expansion.c quotes_expansion.c variables_expansion.c utils.c _tests.c ../hash_table/ht1.c ../hash_table/ht2.c ../hash_table/ht3.c  ../hash_table/utils.c ../command_table/command_table.c ../lexer/lexer.c ../lexer/input_parsing.c ../token/token_deletion.c ../token/token_operations.c ../lexer/utils.c ../env/env.c
LIBFT=../libft/libft.a
NAME=expansion_test

$(NAME): $(SRCS)
	gcc $(SRCS) $(LIBFT) -g -o $@ -fsanitize=address

clean:
	rm -f $(NAME)

re: clean $(NAME)
