/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:34:14 by emuminov          #+#    #+#             */
/*   Updated: 2024/06/06 15:46:28 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <sys/stat.h>
#define PROMPT_COLOR "\x1B[33m"
#define ARROW_COLOR "\x1B[32m"
#define RESET_COLOR "\x1B[0m"
#define ARROW ARROW_COLOR "~> " RESET_COLOR
#define PROMPT PROMPT_COLOR "mishell " RESET_COLOR ARROW
#define RED "\033[0;31m"
#define SPACES " \t\r\v\n\f"

enum				e_token
{
	WORD,
	OPERATOR,
	SQUOTE,
	DQUOTE,
	TILDE,
	SIGIL,
	DIGIT,
	QMARK,
	DELIM,
	QDELIM,
	OTHER,
};

/*
 * IN_REDIR         = <
 * OUT_REDIR        = >
 * HEREDOC          = <<
 * OUT_REDIR_APPEND = >>
 * PIPE             = |
 * */
enum				e_operator
{
	NOT_OPERATOR,
	IN_REDIR,
	OUT_REDIR,
	HEREDOC,
	OUT_REDIR_APPEND,
	PIPE,
};

enum				e_quotes
{
	NOT_QUOTED,
	SQUOTED,
	DQUOTED,
	START_QUOTE,
	END_QUOTE,
};

enum e_err_code
{
	NO_ERRORS,
	NO_OPERAND,
	BAD_OPERAND,
	UNCLOSED_QUOTE,
};

enum e_access_flag
{
	SET,
	GET,
};

typedef struct s_token
{
	struct s_token	*next;
	struct s_token	*prev;
	char			*content;
	int				len;
	enum e_quotes	is_quoted;
	enum e_token	type;
	enum e_operator	op_type;
	int				space_after;
}					t_token;

typedef struct s_tlist
{
	t_token		*head;
	t_token		*tail;
}				t_tlist;

typedef struct	s_err_src
{
	t_token			*t;
	enum e_err_code	code;
}				t_err_src;

typedef struct s_ht_item
{
	char			*key;
	char			*value;
	int				is_deleted;
}					t_ht_item;

typedef struct s_ht_table
{
	int				base_size;
	int				size;
	int				count;
	t_ht_item		**items;
}					t_ht_table;

typedef struct	s_minishell
{
	t_tlist		lst;
	t_ht_table	*env;
	char		***cmd_tab;
	int			last_status;
	int			fd_in;
	int			fd_out;
	int			pid;
	int			is_delimiter_quoted;
}				t_minishell;

t_tlist				*lex_input(char *input, t_tlist *lst);
t_tlist				*lex_heredoc_input(char *input, t_tlist *lst,
		enum e_token delim_type);

enum e_operator		get_operator(char *s, enum e_quotes is_quoted);
enum e_token		get_type(char *s, enum e_quotes is_quoted,
						enum e_operator op);

void				token_list_append(t_tlist *lst, t_token *t);
void				token_list_free(t_tlist *lst);
void				token_list_print(t_tlist *lst);

t_token				*token_create(char *content, int len, int space_after,
		enum e_quotes is_quoted);
void				token_free(t_token *t);
t_token				*token_delete(t_tlist *lst, t_token *t);
t_token				*token_delete_and_free(t_tlist *lst, t_token *t);

void				print_error_message(t_err_src *err);
t_err_src			check_errors(t_tlist *lst);

t_tlist				*expand_tokens(t_minishell *sh, t_tlist *lst);
t_tlist				*expand_heredoc(t_minishell *sh, t_tlist *lst,
		enum e_token type);

void				ft_free_table(char ***tab);

t_ht_table			*ht_new(int base_size);
void				ht_free_table(t_ht_table *ht);
t_ht_item			*ht_set(t_ht_table *ht, const char *key, const char *value);
void				ht_delete(t_ht_table *ht, const char *key);
char				*ht_get(t_ht_table *ht, const char *key);
void				ht_print_buckets(t_ht_table *ht);
void				ht_print_table(t_ht_table *ht);

t_ht_table			*env_init(char **env, t_minishell *sh);
char				**env_ht_to_arr(t_ht_table *ht);

char				***command_table(t_minishell *sh);
void				command_table_print(char ***cmd_tab);
void				ft_free_table(char ***tab);
size_t				count_pipe(t_token *lst);

int					set_or_get_exit_status(enum e_access_flag flag,
		int new_status);

void  execute(t_minishell msh);


int	set_or_get_pid(enum e_access_flag flag, int new_pid);
void	exec_handle_signal(int signal);
void	parsing_handle_signal(int signal);
void	init_signals(struct sigaction	*sa_sigint);
void init_exec_signals();
