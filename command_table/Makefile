SRCS=../lexer/lexer.c command_table.c ../token/token_operations.c ../token/token_deletion.c ../lexer/input_parsing.c ../lexer/lexer_utils.c
LIBFT=../libft/libft.a
NAME=lexer_test

$(NAME): $(SRCS)
	cc $(SRCS) $(LIBFT) -g -o lexer_test #-fsanitize=address

clean:
	rm -f lexer_test

re: clean $(NAME)
