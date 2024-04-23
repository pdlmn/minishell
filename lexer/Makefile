SRCS=lexer.c _tests.c ../token/token_operations.c ../token/token_deletion.c input_parsing.c lexer_utils.c
LIBFT=../libft/libft.a
NAME=lexer_test

$(NAME): $(SRCS)
	gcc $(SRCS) $(LIBFT) -g -o lexer_test -fsanitize=address

clean:
	rm -f lexer_test

re: clean $(NAME)
