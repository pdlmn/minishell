int main(int argc, char **argv, char **envp)
{
	t_minishell	minishell;
	int		i;

	if (argc != 2)
		return (0);
	i = 0;
	minishell.envp = envp;
	minishell.lst = lexer(argv[1]);
	token_list_print(minishell.lst);
	ft_printf("\n\n\n\n");
	minishell.cmd_tab = command_table(minishell.lst);
	if (!minishell.cmd_tab)
		return (EXIT_FAILURE); // don't return yet deal with previous malloc fail and free if necesary
	while (minishell.cmd_tab && minishell.cmd_tab[i])
		print_arr(minishell.cmd_tab[i++]);
	minishell.last_status = execute(minishell);
	token_list_free(minishell.lst);
	ft_free_table(minishell.cmd_tab);
	return (minishell.last_status);
}
