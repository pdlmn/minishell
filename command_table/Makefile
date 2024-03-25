SRCS=command_table.c ../lexer/lexer.c ../lexer/token.c ../lexer/utils.c
LIBFT=../libft/libft.a
NAME=command_table_test

$(NAME): $(SRCS) Makefile
	gcc $(SRCS) $(LIBFT) -g -o $(NAME)

test: $(NAME)
	valgrind ./$(NAME)
	rm $(NAME)

clean:
	rm $(NAME)

re: clean test
