SRCS=hash_table.c utils.c _tests.c
LIBFT=../libft/libft.a
NAME=hash_table_test

$(NAME): $(SRCS)
	gcc $(SRCS) $(LIBFT) -g -o hash_table_test

clean:
	rm -f hash_table_test

re: clean $(NAME)
