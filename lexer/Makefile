SRCS=lexer.c input_parsing.c heredoc_find_delimeters.c lexer_utils.c _tests.c ../token/token_operations.c ../token/token_deletion.c
LIBFT=../libft/libft.a
NAME=lexer_test

$(NAME): $(SRCS)
	cc $(SRCS) $(LIBFT) -g -o $@ -fsanitize=address

clean:
	rm -f lexer_test

re: clean $(NAME)
