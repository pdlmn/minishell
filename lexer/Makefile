SRCS=lexer.c _tests.c token_operations.c token_creation.c utils.c
LIBFT=../libft/libft.a
NAME=lexer_test

$(NAME): $(SRCS)
	gcc $(SRCS) $(LIBFT) -g -o lexer_test -fsanitize=address

clean:
	rm -f lexer_test

re: clean $(NAME)
