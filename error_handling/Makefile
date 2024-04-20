SRCS=error_checking.c ../lexer/lexer.c ../lexer/input_parsing.c ../lexer/heredoc_find_delimeters.c ../lexer/lexer_utils.c _tests.c ../token/token_operations.c ../token/token_deletion.c
LIBFT=../libft/libft.a
NAME=error_checking_test

$(NAME): $(SRCS)
	gcc $(SRCS) $(LIBFT) -g -o $@ -fsanitize=address

clean:
	rm -f lexer_test

re: clean $(NAME)
