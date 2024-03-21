SRCS=lexer.c _tests.c token.c utils.c
LIBFT=../libft/libft.a
NAME=lexer_test

$(NAME): $(SRCS)
	gcc $(SRCS) $(LIBFT) -g -o lexer_test

test: $(NAME)
	valgrind ./lexer_test
	rm $(NAME)

clean:
	rm lexer_test

re: clean test
