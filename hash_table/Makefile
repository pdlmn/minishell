SRCS=ht1.c ht2.c ht3.c ht_utils.c _tests.c
LIBFT=../libft/libft.a
NAME=hash_table_test

$(NAME): $(SRCS)
	cc $(SRCS) $(LIBFT) -g -o hash_table_test -fsanitize=address

clean:
	rm -f hash_table_test

re: clean $(NAME)
